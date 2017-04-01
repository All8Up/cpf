//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Container.hpp"
#include "EntityService/Interfaces/iStage.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;

		struct iEntityStage : iStage
		{
			using UpdateFunc = void(*)(MultiCore::System*, iEntity*);

			// Interface.
			virtual void AddUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f) = 0;
			virtual void RemoveUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f) = 0;
		};

		class EntityStage
			: public MultiCore::Stage
			, tRefCounted<iEntityStage>
		{
		public:
			static constexpr MultiCore::StageID kID = Hash::Create<MultiCore::StageID_tag>("Object Stage"_hashString);

			using UpdateFunc = void(*)(MultiCore::System*, iEntity*);

			static bool Install();
			static bool Remove();

			COM::Result QueryInterface(COM::InterfaceID, void**) { return COM::kUnimplemented; }

			// Interface.
			void AddUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f);
			void RemoveUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f);

			MultiCore::BlockDependencies GetDependencies(MultiCore::SystemID sid) const override;
			MultiCore::Instructions GetInstructions(MultiCore::SystemID sid) override;
			const MultiCore::BlockID GetDefaultBlock() const override { return kExecute; }

		private:
			EntityStage(MultiCore::System* owner, const char* name);

			static MultiCore::Stage* _Creator(MultiCore::System*, const char* name);

			// Implementation definitions.
			using UpdateTuple_t = Tuple<MultiCore::System*, iEntity*, UpdateFunc>;
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

			MultiCore::System* mpSystem;
			Caller mCaller;
		};
	}
}
