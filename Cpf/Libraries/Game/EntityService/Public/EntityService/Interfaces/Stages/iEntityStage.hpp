//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/Container.hpp"
#include "EntityService/Interfaces/iStage.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;

		struct iEntityStage : MultiCore::iStage
		{
			using UpdateFunc = void(*)(MultiCore::iSystem*, iEntity*);

			// Interface.
			virtual void AddUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
			virtual void RemoveUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
		};

		class EntityStage
			: tRefCounted<iEntityStage>
		{
		public:
			static constexpr MultiCore::StageID kID = Hash::Create<MultiCore::StageID_tag>("Object Stage"_hashString);

			using UpdateFunc = void(*)(MultiCore::iSystem*, iEntity*);

			static bool Install();
			static bool Remove();

			COM::Result QueryInterface(COM::InterfaceID, void**) { return COM::kNotImplemented; }

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
			EntityStage(MultiCore::iSystem* owner, const char* name);

			static MultiCore::iStage* _Creator(Plugin::iRegistry*, MultiCore::iSystem*, const char* name);

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
	}
}
