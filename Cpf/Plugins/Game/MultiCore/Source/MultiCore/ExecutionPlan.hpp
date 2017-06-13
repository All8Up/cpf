//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iExecutionPlan.hpp"
#include "Plugin/iClassInstance.hpp"
#include "UnorderedMap.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A multicore processing pipeline. */
		class ExecutionPlan : public tRefCounted<iExecutionPlan>
		{
		public:
			ExecutionPlan(iBase*);
			~ExecutionPlan();

			GOM::Result Cast(uint64_t id, void** iface) override;
			iSystem* CPF_STDCALL Install(iSystem*) override;
			GOM::Result CPF_STDCALL Remove(iSystem*) override;
			GOM::Result CPF_STDCALL Configure(Plugin::iRegistry* regy) override;
			GOM::Result CPF_STDCALL GetSystem(SystemID id, iSystem**) const override;
			GOM::Result CPF_STDCALL GetSystem(const char* const, iSystem**) const override;
			GOM::Result CPF_STDCALL GetStage(SystemID systemID, StageID stageID, iStage**) override;
			void CPF_STDCALL Submit(Concurrency::iScheduler*) override;
			GOM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) override;
			GOM::Result CPF_STDCALL GetSystems(int32_t* count, iSystem**) override;

		private:
			bool _ConfigureSystems();

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<iSystem>>;
			SystemMap mSystemMap;

			IntrusivePtr<Concurrency::iWorkBuffer> mpQueue;
#ifdef CPF_DEBUG
			bool mChanged;
#endif
			Vector<String> mQueueInfo;
		};
	}
}
