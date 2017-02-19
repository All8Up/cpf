//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "GO/Types.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Container.hpp"

namespace Cpf
{
	namespace GO
	{
		// A GO specific stage adds the concepts of game systems which support
		// game components to the multicore handling.  The components get a pointer
		// a systems so it is possible to setup the pipeline with unique interdependencies
		// at a finer grain than intended in the general purpose multicore handling.
		class Stage : public MultiCore::Stage
		{
		public:
			// Interface definitions.
			using FuncType_t = void(*)(System*, Object*);

			// Construction.
			Stage(MultiCore::Service* service, System* system, MultiCore::StageID id);

			// Interface.
			void AddUpdate(System* s, Object* o, FuncType_t f);
			void RemoveUpdate(System* s, Object* o, FuncType_t f);

			void Submit(Concurrency::Scheduler::Queue& q) override;
			System* GetSystem() const;
			virtual bool ResolveDependencies(Service*, System*);

		private:
			// Implementation definitions.
			using UpdateTuple_t = Tuple<System*, Object*, FuncType_t>;
			MultiCore::VectorContainer<UpdateTuple_t> mWork;
			struct Caller
			{
				void Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work);
			};

			static void _Update(Concurrency::ThreadContext& tc, void* context);

			System* mpSystem;
			Caller mCaller;
		};
	}
}
