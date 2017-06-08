//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Concurrency/WorkBuffer.hpp"

using namespace Cpf;
using namespace Concurrency;

/**
 * @brief Constructor.
 */
WorkBuffer::WorkBuffer(iBase*)
{}

/** @brief Destructor. */
WorkBuffer::~WorkBuffer()
{}

/**
 * @brief Query for an interface.
 */
GOM::Result CPF_STDCALL WorkBuffer::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iWorkBuffer*>(this);
			break;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL WorkBuffer::Copy(iWorkBuffer* queue)
{
	WorkBuffer* q = static_cast<WorkBuffer*>(queue);
	mQueue = q->mQueue;
}

/**
 * @brief Function call operator.
 * @param o The Opcode to insert.
 * @param p The Payload to insert.
 * @param c The opaque data for the payload.
 */
void WorkBuffer::operator ()(Opcode o, WorkFunction p, void* c)
{
	mQueue.push_back({ o, p, c });
}

GOM::Result CPF_STDCALL WorkBuffer::Reserve(int32_t size)
{
	mQueue.resize(size);
	return GOM::kOK;
}

void CPF_STDCALL WorkBuffer::Reset()
{
	mQueue.clear();
}

/**
 * @brief Execute the payload with the first thread to arrive.
 * @param func The payload to execute.
 * @param context The opaque data associated with the payload.
 */
void CPF_STDCALL WorkBuffer::FirstOne(WorkFunction func, void* context)
{
	CPF_ASSERT(func != nullptr);
	(*this)(Detail::Opcodes::FirstOne, func, context);
}

/**
* @brief Execute the payload with the first thread to arrive,
*  other threads will wait till the payload completes.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void CPF_STDCALL WorkBuffer::FirstOneBarrier(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::FirstOneBarrier, func, context);
}

/**
* @brief Execute the payload with the last thread to arrive.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void CPF_STDCALL WorkBuffer::LastOne(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::LastOne, func, context);
}

/**
* @brief Execute the payload with the last thread to arrive,
*  other threads will wait till the payload completes.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void CPF_STDCALL WorkBuffer::LastOneBarrier(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::LastOneBarrier, func, context);
}

/**
* @brief Execute the payload with all threads.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void CPF_STDCALL WorkBuffer::All(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::All, func, context);
}


/**
* @brief Execute the payload with all threads, no thread will pass through until all threads complete.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void CPF_STDCALL WorkBuffer::AllBarrier(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::AllBarrier, func, context);
}


/** @brief Implements a barrier, no thread will pass until all have arrived. */
void CPF_STDCALL WorkBuffer::Barrier()
{
	(*this)(Detail::Opcodes::Barrier, nullptr, nullptr);
}

/**
 * @brief Inserts a notification fence, the last thread to pass this point will execute the payload.
 * @param func The payload to execute.
 * @param context The opaque data associated with the payload.
 */
void CPF_STDCALL WorkBuffer::Fence(WorkFunction func, void* context)
{
	(*this)(Detail::Opcodes::LastOne, func, context);
}

// TODO: Decide if these will remain.
#if 0
/**
 * @brief Set's a data register to a value.
 * @param index Zero-based index of the register to set.
 * @param value The value.
 */
void Scheduler::Queue::TLD(int index, int32_t value)
{
	CPF_ASSERT(index < Scheduler::kRegisterCount);
	intptr_t idxVal(index);
	intptr_t ival(value);
	mpScheduler->_Emit(Detail::Opcodes::TLD, Payload(idxVal), (void*)ival);
}


void Scheduler::Queue::TLA(int index, void* value)
{
	CPF_ASSERT(index < Scheduler::kRegisterCount);
	intptr_t idxVal(index);
	mpScheduler->_Emit(Detail::Opcodes::TLA, Payload(idxVal), value);
}

void Scheduler::Queue::SD(int index, int32_t value)
{
	CPF_ASSERT(index < Scheduler::kRegisterCount);
	intptr_t idxVal(index);
	intptr_t ival(value);
	mpScheduler->_Emit(Detail::Opcodes::SD, Payload(idxVal), (void*)ival);
}


void Scheduler::Queue::SA(int index, void* value)
{
	CPF_ASSERT(index < Scheduler::kRegisterCount);
	intptr_t idxVal(index);
	mpScheduler->_Emit(Detail::Opcodes::SA, Payload(idxVal), value);
}
#endif

#if CPF_SCHEDULER_DISASSEMBLER
#include <UnorderedMap.hpp>
#include <String.hpp>
WorkBuffer::DisVector WorkBuffer::Dissassemble() const
{
	using OpMap = UnorderedMap<Scheduler::OpcodeFunc_t, Op>;
	static OpMap sOpMap{
		{&Detail::Opcodes::FirstOne, Op::eFirstOne},
		{&Detail::Opcodes::FirstOneBarrier, Op::eFirstOneBarrier},
		{&Detail::Opcodes::LastOne, Op::eLastOne},
		{&Detail::Opcodes::LastOneBarrier, Op::eLastOneBarrier},
		{&Detail::Opcodes::All, Op::eAll},
		{&Detail::Opcodes::AllBarrier, Op::eAllBarrier},
		{&Detail::Opcodes::Barrier, Op::eBarrier}
	};

	DisVector result;
	for (auto ibegin = mQueue.begin(), iend=mQueue.end(); ibegin!=iend; ++ibegin)
	{
		const auto& instr = *ibegin;
		Op op = sOpMap[instr.mpHandler];
		result.push_back({ op, instr.mpFunction, instr.mpContext });
	}

	return result;
}

const char* WorkBuffer::GetOpName(Op op)
{
	static Vector<String> sNames{
		"FirstOne",
		"FirstOneBarrier",
		"LastOne",
		"LastOneBarrier",
		"All",
		"AllBarrier",
		"Barrier"
	};
	return sNames[int(op)].c_str();
}

#endif

/**
 * @brief Returns an iterator to the beginning of the queue.
 * @return The iterator.
 */
WorkBuffer::QueueType::const_iterator WorkBuffer::begin() const
{
	return mQueue.cbegin();
}

/**
* @brief Returns an iterator to the end of the queue.
* @return The iterator.
*/
WorkBuffer::QueueType::const_iterator WorkBuffer::end() const
{
	return mQueue.cend();
}
