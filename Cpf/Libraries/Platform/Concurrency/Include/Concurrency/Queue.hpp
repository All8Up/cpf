//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Concurrency/Scheduler.hpp"

#define CPF_SCHEDULER_DISASSEMBLER 1

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
			Queue(size_t size);
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

			// Control.
			// TODO: Decide if these will actually remain.
#if 0
			void TLD(int index, int32_t value);
			void TLA(int index, void* value);
			void SD(int index, int32_t value);
			void SA(int index, void* value);
#endif

			//
			void Discard();

#if CPF_SCHEDULER_DISASSEMBLER
			enum class Op : int32_t
			{
				eFirstOne = 0,
				eFirstOneBarrier,
				eLastOne,
				eLastOneBarrier,
				eAll,
				eAllBarrier,
				eBarrier
			};
			struct Dissassem
			{
				Op mOp;
				PayloadFunc_t mpPayload;
				void* mpContext;
			};
			using DisVector = Vector<Dissassem>;
			DisVector Dissassemble() const;
			static const char* GetOpName(Op op);
#endif

		private:
			friend class Scheduler;

			// Internal instruction issuer.
			void operator ()(Opcode, Payload func, void* context);

			// Scheduler helpers.
			QueueType::const_iterator begin() const;
			QueueType::const_iterator end() const;

			// Not intended for others to use.
			Queue(Queue&) = delete;
			Queue& operator =(Queue&) = delete;

			// Implementation data.
			QueueType mQueue;
			Platform::Threading::Semaphore mBarrier;
		};
	}
}
