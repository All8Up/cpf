//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "GOM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iRegistry.hpp"

namespace CPF
{
	namespace MultiCore
	{
		class PipelineBuilder;

		static constexpr GOM::ClassID kStageClass = GOM::ClassID("StageClass"_crc64);
		struct iStage : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iStage"_crc64);

			// Standard blocks.
			static constexpr StageID kStageID = Hash::Create<StageID_tag>("Stage Update"_hashString);
			static constexpr StageID kBegin = Hash::Create<StageID_tag>("Begin"_hashString);
			static constexpr StageID kExecute = Hash::Create<StageID_tag>("Execute"_hashString);
			static constexpr StageID kEnd = Hash::Create<StageID_tag>("End"_hashString);

			virtual GOM::Result CPF_STDCALL Initialize(iSystem*, const char* const name) = 0;
			virtual iSystem* CPF_STDCALL GetSystem() const = 0;
			virtual StageID CPF_STDCALL GetID() const = 0;
			virtual bool CPF_STDCALL IsEnabled() const = 0;
			virtual void CPF_STDCALL SetEnabled(bool flag) = 0;
			virtual GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual GOM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) = 0;
			virtual StageID CPF_STDCALL GetDefaultBlock() const = 0;
			virtual StageID CPF_STDCALL GetBeginBlock() const = 0;
			virtual StageID CPF_STDCALL GetEndBlock() const = 0;
		};


		// TODO: Move out to it's own location.
		static constexpr GOM::ClassID kSingleUpdateStageCID = GOM::ClassID("SingleUpdateStageClass"_crc64);

		struct iSingleUpdateStage : iStage
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iSingleUpdateStage"_crc64);

			virtual void CPF_STDCALL SetUpdate(Concurrency::WorkFunction func, void* context, BlockOpcode opcode = BlockOpcode::eFirst) = 0;
		};
	}
}
