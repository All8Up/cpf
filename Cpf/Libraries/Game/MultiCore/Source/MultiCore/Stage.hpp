//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "COM/iUnknown.hpp"
#include "MultiCore/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "MultiCore/iStage.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class QueueBuilder;

		class SingleUpdateStage : public tRefCounted<iSingleUpdateStage>
		{
		public:
			static constexpr StageID kID = Hash::Create<StageID_tag>("Single Update Stage"_hashString);

			SingleUpdateStage();

			// iStage overrides.
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;
			COM::Result CPF_STDCALL Initialize(iSystem*, const char* const name) override;
			iSystem* CPF_STDCALL GetSystem() const override;
			StageID CPF_STDCALL GetID() const override;
			bool CPF_STDCALL IsEnabled() const override;
			void CPF_STDCALL SetEnabled(bool flag) override;
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;
			BlockID CPF_STDCALL GetDefaultBlock() const { return kExecute; };
			BlockID CPF_STDCALL GetBeginBlock() const override { return GetDefaultBlock(); }
			BlockID CPF_STDCALL GetEndBlock() const override { return GetDefaultBlock(); }

			// iSingleUpdateStage overrides.
			void SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, BlockOpcode opcode = BlockOpcode::eFirst);

		private:
			static void _Update(Concurrency::ThreadContext& tc, void* context);

			Function<void(Concurrency::ThreadContext&, void*)> mpUpdate;
			void* mpContext;
			BlockOpcode mOpcode;

			// Implementation data.
			iSystem* mpSystem;
			StageID mID;
			bool mEnabled;
		};

		class SingleUpdateStageClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new SingleUpdateStage();
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
