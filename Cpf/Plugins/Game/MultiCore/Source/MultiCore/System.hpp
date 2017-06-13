//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "MultiCore/Types.hpp"
#include "RefCounted.hpp"
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class StageList : public iStageList
		{
		public:
			StageList(iBase* outer) : mpOuter(outer), mRefCount(0) {}

			int32_t CPF_STDCALL AddRef() override;
			int32_t CPF_STDCALL Release() override;
			GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			GOM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			GOM::Result CPF_STDCALL AddStage(iStage* stage) override;
			GOM::Result CPF_STDCALL RemoveStage(StageID id) override;

			GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			GOM::Result CPF_STDCALL GetDependencies(iExecutionPlan* owner, int32_t*, BlockDependency*) override;

		private:
			iBase* mpOuter;
			int32_t mRefCount;
			StageVector mStages;
			BlockDependencies mDependencies;
		};
	}
}
