//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"

using namespace Cpf::Concurrency;

/**
 * @brief Constructor.
 */
Scheduler::Queue::Queue()
{}

Scheduler::Queue::Queue(size_t size)
	: mQueue(size)
{}

/**
 * @brief Move assignment.
 */
Scheduler::Queue& Scheduler::Queue::operator = (Queue&& rhs)
{
	mQueue = Move(rhs.mQueue);
	return *this;
}

/**
 * @brief Move constructor.
 * @param rhs The queue to move from.
 */
Scheduler::Queue::Queue(Queue&& rhs) noexcept
	: mQueue(Move(rhs.mQueue))
{
}


/** @brief Destructor. */
Scheduler::Queue::~Queue()
{}

/**
 * @brief Function call operator.
 * @param o The Opcode to insert.
 * @param p The Payload to insert.
 * @param c The opaque data for the payload.
 */
void Scheduler::Queue::operator ()(Opcode o, Payload p, void* c)
{
	mQueue.push_back({ o, p, c });
}

/**
 * @brief Execute the payload with the first thread to arrive.
 * @param func The payload to execute.
 * @param context The opaque data associated with the payload.
 */
void Scheduler::Queue::FirstOne(Payload func, void* context)
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
void Scheduler::Queue::FirstOneBarrier(Payload func, void* context)
{
	(*this)(Detail::Opcodes::FirstOneBarrier, func, context);
}

/**
* @brief Execute the payload with the last thread to arrive.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void Scheduler::Queue::LastOne(Payload func, void* context)
{
	(*this)(Detail::Opcodes::LastOne, func, context);
}

/**
* @brief Execute the payload with the last thread to arrive,
*  other threads will wait till the payload completes.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void Scheduler::Queue::LastOneBarrier(Payload func, void* context)
{
	(*this)(Detail::Opcodes::LastOneBarrier, func, context);
}

/**
* @brief Execute the payload with all threads.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void Scheduler::Queue::All(Payload func, void* context)
{
	(*this)(Detail::Opcodes::All, func, context);
}


/**
* @brief Execute the payload with all threads, no thread will pass through until all threads complete.
* @param func The payload to execute.
* @param context The opaque data associated with the payload.
*/
void Scheduler::Queue::AllBarrier(Payload func, void* context)
{
	(*this)(Detail::Opcodes::AllBarrier, func, context);
}


/** @brief Implements a barrier, no thread will pass until all have arrived. */
void Scheduler::Queue::Barrier()
{
	(*this)(Detail::Opcodes::Barrier, nullptr, nullptr);
}

/**
 * @brief Inserts a notification fence, the last thread to pass this point will execute the payload.
 * @param func The payload to execute.
 * @param context The opaque data associated with the payload.
 */
void Scheduler::Queue::Fence(Payload func, void* context)
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

void Scheduler::Queue::Discard()
{
	mQueue.clear();
}

#if CPF_SCHEDULER_DISASSEMBLER
#include <UnorderedMap.hpp>
#include <String.hpp>
Scheduler::Queue::DisVector Scheduler::Queue::Dissassemble() const
{
	using OpMap = UnorderedMap<OpcodeFunc_t, Op>;
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

const char* Scheduler::Queue::GetOpName(Op op)
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
Scheduler::Queue::QueueType::const_iterator Scheduler::Queue::begin() const
{
	return mQueue.cbegin();
}

/**
* @brief Returns an iterator to the end of the queue.
* @return The iterator.
*/
Scheduler::Queue::QueueType::const_iterator Scheduler::Queue::end() const
{
	return mQueue.cend();
}
