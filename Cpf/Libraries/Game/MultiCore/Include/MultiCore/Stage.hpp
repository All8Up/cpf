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
		class QueueBuilder;

		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			// Standard blocks.
			static constexpr auto kBegin = BlockID("Begin"_crc64);
			static constexpr auto kExecute = BlockID("Execute"_crc64);
			static constexpr auto kEnd = BlockID("Execute"_crc64);

			// Factory.
			using Creator = Stage* (*)(System*, const char* name);

			template <typename TYPE>
			static TYPE* Create(System* owner, const char* name);
			static bool Install(StageID, Creator);
			static bool Remove(StageID);

			// Accessors.
			System* GetSystem() const;
			StageID GetID() const;

			//
			bool IsEnabled() const;
			void SetEnabled(bool flag);

			//
			virtual Instructions GetInstructions(SystemID sid) = 0;
			virtual const BlockID GetDefaultBlock() const = 0;
			virtual const BlockID GetBeginBlock() const { return GetDefaultBlock(); }
			virtual const BlockID GetEndBlock() const { return GetDefaultBlock(); }

		protected:
			// Construction/Destruction.
			Stage(System* system, const char* name);
			virtual ~Stage();

		private:
			static Stage* _Create(StageID type, System* owner, const char* name);

			// Implementation data.
			System* mpSystem;
			StageID mID;
			bool mEnabled;
		};

		//
		template <typename TYPE>
		TYPE* Stage::Create(System* owner, const char* name)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, owner, name));
		}


		// TODO: Move out to it's own location.
		class SingleUpdateStage : public Stage
		{
		public:
			static constexpr auto kID = "Single Update Stage"_hashString;

			static bool Install();
			static bool Remove();

			void SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, bool withBarrier = false, bool first = true);

			Instructions GetInstructions(SystemID sid) override;
			const BlockID GetDefaultBlock() const override { return kExecute; }

		private:
			SingleUpdateStage(System* owner, const char* name);

			static Stage* _Creator(System*, const char* name);
			static void _Update(Concurrency::ThreadContext& tc, void* context);

			bool mWithBarrier;
			bool mFirst;
			Function<void(Concurrency::ThreadContext&, void*)> mpUpdate;
			void* mpContext;
		};
	}
}
