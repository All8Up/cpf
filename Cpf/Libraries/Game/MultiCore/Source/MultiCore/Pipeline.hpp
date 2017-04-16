//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iPipeline.hpp"
#include "Plugin/iClassInstance.hpp"
#include "UnorderedMap.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A multicore processing pipeline. */
		class Pipeline : public tRefCounted<iPipeline>
		{
		public:
			Pipeline(iUnknown*);
			~Pipeline();

			COM::Result QueryInterface(COM::InterfaceID id, void** iface) override;
			iSystem* CPF_STDCALL Install(iSystem*) override;
			COM::Result CPF_STDCALL Remove(iSystem*) override;
			COM::Result CPF_STDCALL Configure() override;
			COM::Result CPF_STDCALL GetSystem(SystemID id, iSystem**) const override;
			COM::Result CPF_STDCALL GetSystem(const char* const, iSystem**) const override;
			COM::Result CPF_STDCALL GetStage(SystemID systemID, StageID stageID, iStage**) override;
			void CPF_STDCALL Submit(Concurrency::Scheduler*) override;
			COM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) override;
			COM::Result CPF_STDCALL GetSystems(int32_t* count, iSystem**) override;

		private:
			bool _ConfigureSystems();

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<iSystem>>;
			SystemMap mSystemMap;

			Concurrency::Scheduler::Queue mQueue;
#ifdef CPF_DEBUG
			bool mChanged;
#endif
			Vector<String> mQueueInfo;
		};
	}
}
