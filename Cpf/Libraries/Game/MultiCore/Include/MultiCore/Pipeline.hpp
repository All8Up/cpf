//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A multicore processing pipeline. */
		class Pipeline : public tRefCounted<iRefCounted>
		{
		public:
			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<System>>;

			static bool Create(Pipeline**);

			System* Install(System*);
			bool Remove(System*);

			bool Configure();

			System* GetSystem(SystemID id) const;
			System* GetSystem(const String& name) const;
			const SystemMap& GetSystems() const { return mSystemMap; }
			template <typename TYPE>
			TYPE* GetSystem(const String& name) const;

			Stage* GetStage(SystemID systemID, StageID stageID);

			void operator ()(Concurrency::Scheduler&);

			const Vector<String>& GetQueueInfo() const { return mQueueInfo; }

		private:
			Pipeline();
			~Pipeline();

			bool _ConfigureSystems() const;

			SystemMap mSystemMap;

			Concurrency::Scheduler::Queue mQueue;
#ifdef CPF_DEBUG
			bool mChanged;
#endif
			Vector<String> mQueueInfo;
		};

		template <typename TYPE>
		TYPE* Pipeline::GetSystem(const String& name) const
		{
			return static_cast<TYPE*>(GetSystem(name));
		}
	}
}
