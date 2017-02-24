//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "RefCounted.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/Types.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			// Factory.
			using Creator = Stage* (*)(System*, const String& name);

			template <typename TYPE>
			static TYPE* Create(System* owner, const String& name);
			static bool Install(StageID, Creator);
			static bool Remove(StageID);

			// Interface definitions.
			using Dependency = Pair<SystemID, StageID>;
			using Dependencies = Vector<Dependency>;

			// Accessors.
			System* GetSystem() const;
			StageID GetID() const;
			const String& GetName() const;

			const Dependencies& GetDependencies() const;
			void SetDependencies(Dependencies&& deps) { mDependencies = Move(deps); }

			//
			bool IsEnabled() const;
			void SetEnabled(bool flag);

			// Submission to the scheduler queue.
			virtual void Emit(Concurrency::Scheduler::Queue*) = 0;

		protected:
			// Construction/Destruction.
			Stage(System* system, const String& name);
			virtual ~Stage();

		private:
			static Stage* _Create(StageID type, System* owner, const String& name);

			// Implementation data.
			System* mpSystem;
			String mName;
			StageID mID;
			Dependencies mDependencies;
			bool mEnabled;
		};

		//
		template <typename TYPE>
		TYPE* Stage::Create(System* owner, const String& name)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, owner, name));
		}


		// TODO: Move out to it's own location.
		class SingleUpdateStage : public Stage
		{
		public:
			static constexpr auto kID = StageID("Single Update Stage"_crc64);

			static bool Install();
			static bool Remove();

			void Emit(Concurrency::Scheduler::Queue*) override;

			void SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, bool withBarrier = false, bool first = true);

		private:
			SingleUpdateStage(System* owner, const String& name);

			static Stage* _Creator(System*, const String& name);
			static void _Update(Concurrency::ThreadContext& tc, void* context);

			bool mWithBarrier;
			bool mFirst;
			Function<void(Concurrency::ThreadContext&, void*)> mpUpdate;
			void* mpContext;
		};
	}
}
