//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Types.hpp"
#include "MultiCore/Stage.hpp"

namespace Cpf
{
	namespace GO
	{
		// GO::Stage adds the concept of game 'systems' to the mix.
		class Stage : public MultiCore::Stage
		{
		public:
			using FuncType_t = void(*)(System*, Object*);

			Stage(MultiCore::Service* service, System* system, MultiCore::StageID id)
				: MultiCore::Stage(service, id)
				, mpSystem(system)
			{}

			void AddUpdate(System* s, Object* o, FuncType_t f)
			{
				mWork.Acquire();
				mWork.Add({ s, o, f });
				mWork.Release();
			}
			void RemoveUpdate(System* s, Object* o, FuncType_t f)
			{
				mWork.Acquire();
				mWork.Remove({ s, o, f });
				mWork.Release();
			}

			void Submit(Concurrency::Scheduler::Queue& q) override
			{
				q.All(&Stage::_Update, this);
			}

			System* GetSystem() const { return mpSystem; }
			virtual bool ResolveDependencies(GO::Service*, GO::System*) { return true; }

		private:
			System* mpSystem;
			using UpdateTuple_t = Tuple<System*, Object*, FuncType_t>;
			MultiCore::VectorContainer<UpdateTuple_t> mWork;
			struct Caller
			{
				void Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work)
				{
					(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
				}
			} mCaller;

			static void _Update(Concurrency::ThreadContext& tc, void* context)
			{
				Stage& self = *reinterpret_cast<Stage*>(context);
				MultiCore::EqualPartitions<MultiCore::VectorContainer<UpdateTuple_t>, Caller>::Execute(self.mWork, tc, &self.mCaller);
			}
		};
	}
}
