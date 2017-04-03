//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "MultiCore/Export.hpp"
#include "MultiCore/Types.hpp"
#include "Plugin/iRegistry.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class StageList : public tRefCounted<iStageList>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			COM::Result CPF_STDCALL AddStage(iStage* stage) override;
			COM::Result CPF_STDCALL RemoveStage(StageID id) override;

			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(iPipeline* owner, int32_t*, BlockDependency*) override;

		private:
			StageVector mStages;
			BlockDependencies mDependencies;
		};

		class StageListClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new StageList;
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
