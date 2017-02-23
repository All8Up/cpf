//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Container.hpp"
#include "String.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;


		class EntityStage : public MultiCore::Stage
		{
		public:
			static constexpr auto kID = MultiCore::StageID("Object Stage"_crc64);

			using UpdateFunc = void(*)(MultiCore::System*, iEntity*);

			static bool Install();
			static bool Remove();

			void Emit(Concurrency::Scheduler::Queue&) override;

			// Interface.
			void AddUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f);
			void RemoveUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f);

		private:
			EntityStage(MultiCore::System* owner, const String& name);

			static MultiCore::Stage* _Creator(MultiCore::System*, const String& name);

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

			static void _Update(Concurrency::ThreadContext& tc, void* context);

			MultiCore::System* mpSystem;
			Caller mCaller;
		};
	}
}
