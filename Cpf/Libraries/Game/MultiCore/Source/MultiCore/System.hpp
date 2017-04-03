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

		// TODO: This can go away..
		class System : public tRefCounted<iSystem>
		{
		public:
			// iUnknown
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

			// iSystem
			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name) override;
			SystemID CPF_STDCALL GetID() const override;
			COM::Result CPF_STDCALL Configure(iPipeline*) override { return COM::kOK; }

			// iStageList
			COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(iPipeline* owner, int32_t*, BlockDependency*) override;

			COM::Result CPF_STDCALL AddStage(iStage*) override;
			COM::Result CPF_STDCALL RemoveStage(StageID) override;

		protected:
			// Implementation interface.
			System();
			virtual ~System();

		private:
			// Implementation data.
			SystemID mID;
			IntrusivePtr<iStageList> mpStages;
		};
	}
}
