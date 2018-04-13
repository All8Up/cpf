//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"


namespace CPF
{
	namespace Concurrency
	{
		class Team;

		namespace Dispatch
		{
			namespace Immediate
			{
				template<typename WorkType, typename WorkContext>
				class Vector
				{
				public:
					Vector();
					~Vector();

					void Insert(WorkType*, WorkContext*);

				private:
					friend class Team;
					struct WorkPair
					{
						WorkType mpFunction;
						WorkContext* mpContext;
					};

					void Emit(Scheduler*);
					static void _Initialize(Scheduler::ThreadContext&, void*);
					static void _Execute(Scheduler::ThreadContext&, void*);

					STD::Vector<WorkPair> mWork;
				};
			}

			namespace Retained
			{
				class Vector
				{
				public:
				};
			}
		}
	}
}
