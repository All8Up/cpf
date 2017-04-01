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
			Pipeline();
			~Pipeline();

			COM::Result QueryInterface(COM::InterfaceID id, void** iface) override;
			System* CPF_STDCALL Install(System*) override;
			COM::Result CPF_STDCALL Remove(System*) override;
			COM::Result CPF_STDCALL Configure() override;
			COM::Result CPF_STDCALL GetSystem(SystemID id, System**) const override;
			COM::Result CPF_STDCALL GetSystem(const char* const, System**) const override;
			COM::Result CPF_STDCALL GetStage(SystemID systemID, StageID stageID, Stage**) override;
			void CPF_STDCALL Submit(Concurrency::Scheduler*) override;
			COM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) override;
			COM::Result CPF_STDCALL EnumerateSystems(void* context, bool(CPF_STDCALL *)(void*, SystemID, IntrusivePtr<System>)) override;

		private:
			bool _ConfigureSystems() const;

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<System>>;
			SystemMap mSystemMap;

			Concurrency::Scheduler::Queue mQueue;
#ifdef CPF_DEBUG
			bool mChanged;
#endif
			Vector<String> mQueueInfo;
		};


		/** @brief Class instance object for registry installation. */
		class PipelineClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new Pipeline();
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
