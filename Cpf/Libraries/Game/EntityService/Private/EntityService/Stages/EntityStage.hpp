//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "Tuple.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/Container.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace EntityService
	{
		class EntityStage : public tRefCounted<iEntityStage>
		{
		public:
			static constexpr MultiCore::StageID kID = Hash::Create<MultiCore::StageID_tag>("Object Stage"_hashString);

			EntityStage();

			// iUnknown overrides.
			COM::Result QueryInterface(COM::InterfaceID, void**) override;

			// iStage overrides.
			COM::Result CPF_STDCALL Initialize(MultiCore::iSystem*, const char* const name) override;
			MultiCore::iSystem* CPF_STDCALL GetSystem() const override;
			MultiCore::StageID CPF_STDCALL GetID() const override;
			bool CPF_STDCALL IsEnabled() const override;
			void CPF_STDCALL SetEnabled(bool flag) override;
			COM::Result CPF_STDCALL GetInstructions(MultiCore::SystemID sid, int32_t*, MultiCore::Instruction*) override;
			COM::Result CPF_STDCALL GetDependencies(MultiCore::SystemID sid, int32_t*, MultiCore::BlockDependency*) override;
			MultiCore::BlockID GetDefaultBlock() const override { return kExecute; }
			MultiCore::BlockID CPF_STDCALL GetBeginBlock() const override { return GetDefaultBlock(); }
			MultiCore::BlockID CPF_STDCALL GetEndBlock() const override { return GetDefaultBlock(); }

			// iEntityStage overrides.
			void AddUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f);
			void RemoveUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f);

		private:
			// Implementation definitions.
			using UpdateTuple_t = Tuple<MultiCore::iSystem*, iEntity*, UpdateFunc>;
			struct Compare
			{
				bool operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const;
			};
			MultiCore::SortedVectorContainer<UpdateTuple_t, Compare> mWork;
			struct Caller
			{
				void Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work);
			};

			static void _Begin(Concurrency::ThreadContext& tc, void* context);
			static void _Update(Concurrency::ThreadContext& tc, void* context);
			static void _End(Concurrency::ThreadContext& tc, void* context);

			MultiCore::iSystem* mpSystem;
			Caller mCaller;

			MultiCore::StageID mID;
			bool mEnabled;
		};


		class EntityStageClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new EntityStage();
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
