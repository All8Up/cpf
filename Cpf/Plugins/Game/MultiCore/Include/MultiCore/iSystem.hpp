//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "CPF/Plugin/iRegistry.hpp"

namespace CPF
{
	namespace MultiCore
	{
		static constexpr GOM::ClassID kStageListCID = GOM::ClassID("StageListClass"_crc64);

		struct iStageList : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iStageList"_crc64);

			virtual GOM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const = 0;
			virtual GOM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const = 0;
			virtual GOM::Result CPF_STDCALL AddStage(iStage* stage) = 0;
			virtual GOM::Result CPF_STDCALL RemoveStage(StageID id) = 0;

			virtual GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual void CPF_STDCALL AddDependency(BlockDependency dep) = 0;
			virtual GOM::Result CPF_STDCALL GetDependencies(iExecutionPlan* owner, int32_t*, BlockDependency*) = 0;

			/* New refined interface.
			virtual GOM::Result CPF_STDCALL GetNamed(const char* name, StageID*) = 0;
			virtual StageID CPF_STDCALL GetPrologue() = 0;
			virtual StageID CPF_STDCALL GetBody() = 0;
			virtual StageID CPF_STDCALL GetEpilogue() = 0;

			virtual iStage* CPF_STDCALL GetStage(StageID) = 0;

			virtual size_t CPF_STDCALL GetStages(size_t* count, iStage**) = 0;
			virtual GOM::Result CPF_STDCALL GetDependencies(size_t* count, BlockDependency* array) = 0;
			 */
		};

		struct iSystem : iStageList
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iSystem"_crc64);
			// Empty base class for system descriptors.
			struct Desc
			{};

			virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) = 0;
			virtual SystemID CPF_STDCALL GetID() const = 0;
			virtual GOM::Result CPF_STDCALL Configure(iExecutionPlan*) = 0;
		};
	}
}
