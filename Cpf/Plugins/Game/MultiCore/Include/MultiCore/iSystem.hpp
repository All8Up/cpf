//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "MultiCore/Export.hpp"
#include "MultiCore/Types.hpp"
#include "Plugin/iRegistry.hpp"
#include "RefCounted.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		static constexpr GOM::ClassID kStageListCID = GOM::ClassID("StageListClass"_crc64);

		struct iStageList : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iStageList"_crc64);

			virtual GOM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const = 0;
			virtual GOM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const = 0;
			virtual GOM::Result CPF_STDCALL AddStage(iStage* stage) = 0;
			virtual GOM::Result CPF_STDCALL RemoveStage(StageID id) = 0;

			virtual GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual void CPF_STDCALL AddDependency(BlockDependency dep) = 0;
			virtual GOM::Result CPF_STDCALL GetDependencies(iPipeline* owner, int32_t*, BlockDependency*) = 0;
		};

		struct iSystem : iStageList
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iSystem"_crc64);
			// Empty base class for system descriptors.
			struct Desc
			{};

			virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) = 0;
			virtual SystemID CPF_STDCALL GetID() const = 0;
			virtual GOM::Result CPF_STDCALL Configure(iPipeline*) = 0;
		};
	}
}
