//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Concurrency/Scheduler.hpp"

#define CPF_SCHEDULER_DISASSEMBLER 1

namespace CPF
{
	namespace Concurrency
	{
		/** @brief Execution queue for the scheduler. */
		class WorkBuffer : public tRefCounted<iWorkBuffer>
		{
			// Construction/Destruction.
			WorkBuffer(Plugin::iRegistry*, iUnknown*);
			~WorkBuffer();
			template <typename TYPE>
			friend struct Plugin::tClassInstance;

		public:
			// Declaration types.
			using Opcode = Scheduler::OpcodeFunc_t;
			using OpcodeEntry = Scheduler::Instruction;
			using QueueType = Vector<OpcodeEntry>;

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

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

			// Control.
			// TODO: Decide if these will actually remain.
			// TODO: What would be better is something similar to thread local storage
			// so that different systems can register them individually instead of using
			// these common shared items.
#if 0
			void TLD(int index, int32_t value);
			void TLA(int index, void* value);
			void SD(int index, int32_t value);
			void SA(int index, void* value);
#endif
			// TODO: Data sharing api.
			// <Thread local data, basically a scheduler specific TLS system>
			// template <typename TYPE>
			// DataRef MakeThreadLocal();
			// template <typename TYPE>
			// TYPE& GetThreadLocal(DataRef);
			// template <typename TYPE>
			// void SetThreadLocal(DataRef, TYPE&);
			// 
			// <Shared data system, the data is changed at certain points in the instruction stream
			// rather than immediately.>
			// template <typename TYPE>
			// DataRef MakeThreadShared();
			// template <typename TYPE>
			// TYPE& GetThreadShared(DataRef);
			// template <typename TYPE>
			// void SetThreadShared(DataRef, TYPE&);

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
				WorkFunction mpPayload;
				void* mpContext;
			};
			using DisVector = Vector<Dissassem>;
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
