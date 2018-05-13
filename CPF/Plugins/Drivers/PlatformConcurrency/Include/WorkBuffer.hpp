//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "Scheduler.hpp"
#include "CPF/GOM/tUnknown.hpp"

#define CPF_SCHEDULER_DISASSEMBLER 1

namespace CPF
{
	namespace Platform
	{
		/** @brief Execution queue for the scheduler. */
		class WorkBuffer : public GOM::tUnknown<iWorkBuffer>
		{
		public:
			// Construction/Destruction.
			WorkBuffer();
			~WorkBuffer();

			// Declaration types.
			using Opcode = Scheduler::OpcodeFunc_t;
			using OpcodeEntry = Scheduler::Instruction;
			using QueueType = STD::Vector<OpcodeEntry>;

			// 
			GOM::Result CPF_STDCALL Reserve(int32_t size) override;
			void CPF_STDCALL Copy(iWorkBuffer*) override;

			void CPF_STDCALL Reset() override;

			// Scheduler instructions.
			void CPF_STDCALL FirstOne(WorkFunction func, void* context) override;
			void CPF_STDCALL FirstOneBarrier(WorkFunction func, void* context) override;
			void CPF_STDCALL LastOne(WorkFunction func, void* context) override;
			void CPF_STDCALL LastOneBarrier(WorkFunction func, void* context) override;
			void CPF_STDCALL All(WorkFunction func, void* context) override;
			void CPF_STDCALL AllBarrier(WorkFunction func, void* context) override;

			void CPF_STDCALL LastOneSleep(WorkFunction func, void* context) override;

			// TODO: Add the following
			// 
			// <N unique threads will execute the work function.>
			// void CPF_STDCALL FirstN(int32_t n, WorkFunction func, void* context) override;
			// void CPF_STDCALL FirstNBarrier(int32_t n, WorkFunction func, void* context) override;
			// void CPF_STDCALL LastN(int32_t n, WorkFunction func, void* context) override;
			// void CPF_STDCALL LastNBarrier(int32_t n, WorkFunction func, void* context) override;
			// 
			// <Execute the work function n times, potentially from the same thread or any mix>
			// void CPF_STDCALL RepeatN(int32_t n, WorkFunction func, void* context) override;
			// void CPF_STDCALL RepeatNBarrier(int32_t n, WorkFunction func, void* context) override;
			// 
			// <Branching, only backwards, non-nested supported.  I.e. one label is paired
			// to a branch instruction, when the branch fails the label and any instructions
			// between it and the branch are considered consumed and no longer valid targets.>
			// LabelID CPF_STDCALL Label();
			// void CPF_STDCALL BranchIfZero(LabelID, DataRef);
			// void CPF_STDCALL BranchIfNotZero(LabelID, DataRef);

			void CPF_STDCALL Barrier() override;
			void CPF_STDCALL Fence(WorkFunction func, void* context) override;

			// TODO: Data sharing api.
			// <Thread local data, basically a scheduler specific TLS system>
			// DataRef MakeThreadLocal();
			// void* GetThreadLocal(DataRef);
			// void SetThreadLocal(DataRef, void*);
			// 
			// <Shared data system, the data is changed at certain points in the instruction stream
			// rather than immediately.>
			// DataRef MakeThreadShared();
			// void* GetThreadShared(DataRef);
			// void SetThreadShared(DataRef, void*);

#if CPF_SCHEDULER_DISASSEMBLER
			enum class Op : int32_t
			{
				eFirstOne = 0,
				eFirstOneBarrier,
				eLastOne,
				eLastOneBarrier,
				eAll,
				eAllBarrier,
				eBarrier,
				eLastOneSleep
			};
			struct Dissassem
			{
				Op mOp;
				WorkFunction mpPayload;
				void* mpContext;
			};
			using DisVector = STD::Vector<Dissassem>;
			DisVector Dissassemble() const;
			static const char* GetOpName(Op op);
#endif

		private:
			friend class Scheduler;

			// Internal instruction issuer.
			void operator ()(Opcode, WorkFunction func, void* context);

			// Scheduler helpers.
			QueueType::const_iterator begin() const;
			QueueType::const_iterator end() const;

			// Not intended for others to use.
			WorkBuffer(WorkBuffer&) = delete;
			WorkBuffer& operator =(WorkBuffer&) = delete;

			// Implementation data.
			CPF_DLL_SAFE_BEGIN;
			QueueType mQueue;
			Threading::Semaphore mBarrier;
			CPF_DLL_SAFE_END;
		};
	}
}
