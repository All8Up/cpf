//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "COM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iRegistry.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class QueueBuilder;

		static constexpr COM::ClassID kStageClass = COM::ClassID("StageClass"_crc64);
		struct iStage : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iStage"_crc64);

			// Standard blocks.
			static constexpr StageID kStageID = Hash::Create<StageID_tag>("Stage Update"_hashString);
			static constexpr BlockID kBegin = Hash::Create<BlockID_tag>("Begin"_hashString);
			static constexpr BlockID kExecute = Hash::Create<BlockID_tag>("Execute"_hashString);
			static constexpr BlockID kEnd = Hash::Create<BlockID_tag>("End"_hashString);

			virtual COM::Result CPF_STDCALL Initialize(iSystem*, const char* const name) = 0;
			virtual iSystem* CPF_STDCALL GetSystem() const = 0;
			virtual StageID CPF_STDCALL GetID() const = 0;
			virtual bool CPF_STDCALL IsEnabled() const = 0;
			virtual void CPF_STDCALL SetEnabled(bool flag) = 0;
			virtual COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) = 0;
			virtual BlockID CPF_STDCALL GetDefaultBlock() const = 0;
			virtual BlockID CPF_STDCALL GetBeginBlock() const = 0;
			virtual BlockID CPF_STDCALL GetEndBlock() const = 0;
		};


		// TODO: Move out to it's own location.
		static constexpr COM::ClassID kSingleUpdateStageCID = COM::ClassID("SingleUpdateStageClass"_crc64);

		struct iSingleUpdateStage : iStage
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iSingleUpdateStage"_crc64);

			virtual void CPF_STDCALL SetUpdate(Function<void(const Concurrency::WorkContext*, void*)> func, void* context, BlockOpcode opcode = BlockOpcode::eFirst) = 0;
		};
	}
}
