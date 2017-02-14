//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		/** @brief Execution queue for the scheduler. */
		class Scheduler::Queue
		{
		public:
			// Declaration types.
			using Opcode = Scheduler::OpcodeFunc_t;
			using Payload = Scheduler::PayloadFunc_t;
			using OpcodeEntry = Scheduler::Instruction;
			using QueueType = Vector<OpcodeEntry>;
			enum class SubmissionType : int
			{
				eNormal,
				eNoClear
			};

			// Construction/Destruction.
			Queue();
			Queue(Queue&& rhs) noexcept;
			~Queue();

			// 
			Queue& operator = (Queue&& rhs);

			// Scheduler instructions.
			void FirstOne(Payload func, void* context);
			void FirstOneBarrier(Payload func, void* context);
			void LastOne(Payload func, void* context);
			void LastOneBarrier(Payload func, void* context);
			void All(Payload func, void* context);
			void AllBarrier(Payload func, void* context);

			void Barrier();
			void Fence(Payload func, void* context);
			void Submit(Scheduler::Semaphore& semaphore);

			// Control.
			Queue& ActiveThreads(int count);
			void TLD(int index, int32_t value);
			void TLA(int index, void* value);
			void SD(int index, int32_t value);
			void SA(int index, void* value);

			// Submission.
			Queue& Submit(SubmissionType type=SubmissionType::eNormal);
			Queue& BlockingSubmit(SubmissionType type = SubmissionType::eNormal);

		private:
			//  The queue is only created by the scheduler.
			friend class Scheduler;
			Queue(Scheduler* scheduler);
			Queue(Scheduler* scheduler, size_t size);

			// Internal instruction issuer.
			void operator ()(Opcode, Payload func, void* context);

			// Scheduler helpers.
			QueueType::const_iterator begin() const;
			QueueType::const_iterator end() const;
			void Clear();

			// Not intended for others to use.
			Queue(Queue&) = delete;
			Queue& operator =(Queue&) = delete;

			// Implementation data.
			Scheduler* mpScheduler;
			QueueType mQueue;
			Platform::Threading::Semaphore mBarrier;
		};
	}
}
