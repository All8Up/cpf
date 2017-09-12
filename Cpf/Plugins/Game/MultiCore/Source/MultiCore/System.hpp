//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "RefCounted.hpp"
#include "MultiCore/iSystem.hpp"

namespace CPF
{
	namespace MultiCore
	{
		class StageList : public iStageList
		{
		public:
			StageList(iUnknown* outer) : mpOuter(outer), mRefCount(0) {}

			int32_t CPF_STDCALL AddRef() override;
			int32_t CPF_STDCALL Release() override;
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			GOM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			GOM::Result CPF_STDCALL AddStage(iStage* stage) override;
			GOM::Result CPF_STDCALL RemoveStage(StageID id) override;

			GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			GOM::Result CPF_STDCALL GetDependencies(iExecutionPlan* owner, int32_t*, BlockDependency*) override;

		private:
			iUnknown* mpOuter;
			int32_t mRefCount;
			StageVector mStages;
			BlockDependencies mDependencies;
		};
	}
}
