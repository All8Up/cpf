//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "Tuple.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/Container.hpp"
#include "MultiCore/Partitioning.hpp"
#include "Plugin/iClassInstance.hpp"

namespace CPF
{
	namespace EntityService
	{
		class EntityStage : public tRefCounted<iEntityStage>
		{
		public:
			EntityStage(iUnknown*);

			// iBase overrides.
			GOM::Result QueryInterface(uint64_t, void**) override;

			// iStage overrides.
			GOM::Result CPF_STDCALL Initialize(MultiCore::iSystem*, const char* const name) override;
			MultiCore::iSystem* CPF_STDCALL GetSystem() const override;
			MultiCore::StageID CPF_STDCALL GetID() const override;
			bool CPF_STDCALL IsEnabled() const override;
			void CPF_STDCALL SetEnabled(bool flag) override;
			GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
			GOM::Result CPF_STDCALL GetDependencies(int32_t*, MultiCore::BlockDependency*) override;
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

			struct Caller;
			using Partition = MultiCore::Partitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>;
			struct Caller
			{
				Partition::Context mContext;
				void Execute(const Concurrency::WorkContext*, const UpdateTuple_t& work);
			};

			static void _Begin(const Concurrency::WorkContext* tc, void* context);
			static void _Update(const Concurrency::WorkContext* tc, void* context);
			static void _End(const Concurrency::WorkContext* tc, void* context);

			MultiCore::iSystem* mpSystem;
			Caller mCaller;

			MultiCore::StageID mID;
			bool mEnabled;
		};
	}
}
