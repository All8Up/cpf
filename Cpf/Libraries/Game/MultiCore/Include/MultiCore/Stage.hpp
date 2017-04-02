//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "COM/iUnknown.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/Types.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class QueueBuilder;

		static constexpr COM::ClassID kStageClass = COM::ClassID("StageClass"_crc64);
		struct iStage : COM::iUnknown
		{
			// Standard blocks.
			static constexpr StageID kStageID = Hash::Create<StageID_tag>("Stage Update"_hashString);
			static constexpr BlockID kBegin = Hash::Create<BlockID_tag>("Begin"_hashString);
			static constexpr BlockID kExecute = Hash::Create<BlockID_tag>("Execute"_hashString);
			static constexpr BlockID kEnd = Hash::Create<BlockID_tag>("End"_hashString);

			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iStage"_crc64);

			virtual System* CPF_STDCALL GetSystem() const = 0;
			virtual StageID CPF_STDCALL GetID() const = 0;
			virtual bool CPF_STDCALL IsEnabled() const = 0;
			virtual void CPF_STDCALL SetEnabled(bool flag) = 0;
			virtual COM::Result CPF_STDCALL GetInstructions(SystemID, int32_t*, Instruction*) = 0;
			virtual COM::Result CPF_STDCALL GetDependencies(SystemID, int32_t*, BlockDependency*) = 0;
			virtual BlockID CPF_STDCALL GetDefaultBlock() const = 0;
			virtual BlockID CPF_STDCALL GetBeginBlock() const = 0;
			virtual BlockID CPF_STDCALL GetEndBlock() const = 0;
		};

		class Stage : public tRefCounted<iStage>
		{
		public:
			// Factory.
			using Creator = Stage* (*)(System*, const char* name);

			template <typename TYPE>
			static TYPE* Create(System* owner, const char* name);
			static bool Install(StageID, Creator);
			static bool Remove(StageID);

			//
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;
			System* CPF_STDCALL GetSystem() const override;
			StageID CPF_STDCALL GetID() const override;
			bool CPF_STDCALL IsEnabled() const override;
			void CPF_STDCALL SetEnabled(bool flag) override;
			COM::Result CPF_STDCALL GetInstructions(SystemID, int32_t*, Instruction*) override;
			COM::Result CPF_STDCALL GetDependencies(SystemID, int32_t*, BlockDependency*) override;
			virtual BlockID CPF_STDCALL GetBeginBlock() const override { return GetDefaultBlock(); }
			virtual BlockID CPF_STDCALL GetEndBlock() const override { return GetDefaultBlock(); }

		protected:
			// Construction/Destruction.
			Stage(System* system, const char* name);
			virtual ~Stage();

		private:
			static Stage* _Create(StageID type, System* owner, const char* name);

			// Implementation data.
			System* mpSystem;
			StageID mID;
			bool mEnabled;
		};

		//
		template <typename TYPE>
		TYPE* Stage::Create(System* owner, const char* name)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, owner, name));
		}


		// TODO: Move out to it's own location.
		class SingleUpdateStage : public Stage
		{
		public:
			static constexpr StageID kID = Hash::Create<StageID_tag>("Single Update Stage"_hashString);

			static bool Install();
			static bool Remove();

			void SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, BlockOpcode opcode = BlockOpcode::eFirst);

			COM::Result CPF_STDCALL GetInstructions(SystemID, int32_t*, Instruction*) override;
			BlockID GetDefaultBlock() const override { return kExecute; }

		private:
			SingleUpdateStage(System* owner, const char* name);

			static Stage* _Creator(System*, const char* name);
			static void _Update(Concurrency::ThreadContext& tc, void* context);

			Function<void(Concurrency::ThreadContext&, void*)> mpUpdate;
			void* mpContext;
			BlockOpcode mOpcode;
		};
	}
}
