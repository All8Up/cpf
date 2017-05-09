//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Concurrency/Scheduler.hpp"

#define CPF_SCHEDULER_DISASSEMBLER 1

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief Execution queue for the scheduler. */
		class WorkBuffer : public tRefCounted<iWorkBuffer>
		{
			// Construction/Destruction.
			WorkBuffer(iUnknown*);
			~WorkBuffer();
			template <typename TYPE>
			friend struct Plugin::tClassInstance;

		public:
			// Declaration types.
			using Opcode = Scheduler::OpcodeFunc_t;
			using OpcodeEntry = Scheduler::Instruction;
			using QueueType = Vector<OpcodeEntry>;

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			// 
			COM::Result CPF_STDCALL Reserve(int32_t size) override;
			void CPF_STDCALL Copy(iWorkBuffer*) override;

			void CPF_STDCALL Reset() override;

			// Scheduler instructions.
			void CPF_STDCALL FirstOne(WorkFunction func, void* context) override;
			void CPF_STDCALL FirstOneBarrier(WorkFunction func, void* context) override;
			void CPF_STDCALL LastOne(WorkFunction func, void* context) override;
			void CPF_STDCALL LastOneBarrier(WorkFunction func, void* context) override;
			void CPF_STDCALL All(WorkFunction func, void* context) override;
			void CPF_STDCALL AllBarrier(WorkFunction func, void* context) override;

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
