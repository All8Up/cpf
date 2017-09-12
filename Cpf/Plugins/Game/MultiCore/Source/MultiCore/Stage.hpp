//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "GOM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "MultiCore/iStage.hpp"

namespace CPF
{
	namespace MultiCore
	{
		class PipelineBuilder;

		class SingleUpdateStage : public tRefCounted<iSingleUpdateStage>
		{
		public:
			static constexpr StageID kID = Hash::Create<StageID_tag>("Single Update Stage"_hashString);

			SingleUpdateStage(iUnknown*);

			// iStage overrides.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;
			GOM::Result CPF_STDCALL Initialize(iSystem*, const char* const name) override;
			iSystem* CPF_STDCALL GetSystem() const override;
			StageID CPF_STDCALL GetID() const override;
			bool CPF_STDCALL IsEnabled() const override;
			void CPF_STDCALL SetEnabled(bool flag) override;
			GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			GOM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;
			BlockID CPF_STDCALL GetDefaultBlock() const { return kExecute; };
			BlockID CPF_STDCALL GetBeginBlock() const override { return GetDefaultBlock(); }
			BlockID CPF_STDCALL GetEndBlock() const override { return GetDefaultBlock(); }

			// iSingleUpdateStage overrides.
			void SetUpdate(Function<void(const Concurrency::WorkContext*, void*)> func, void* context, BlockOpcode opcode = BlockOpcode::eFirst);

		private:
			static void _Update(const Concurrency::WorkContext* tc, void* context);

			Function<void(const Concurrency::WorkContext*, void*)> mpUpdate;
			void* mpContext;
			BlockOpcode mOpcode;

			// Implementation data.
			iSystem* mpSystem;
			StageID mID;
			bool mEnabled;
		};
	}
}
