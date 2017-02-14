//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"

using namespace Cpf::Concurrency;

/**
 * @brief Constructor.
 */
Scheduler::Queue::Queue()
	: mpScheduler(nullptr)
{}

/**
 * @brief Constructor.
 * @param scheduler The scheduler the queue is associated with.
 */
Scheduler::Queue::Queue(Scheduler* scheduler)
	: mpScheduler(scheduler)
{}

/**
 * @brief Constructor.
 * @param scheduler The scheduler the queue is associated with.
 * @param size The size.
 */
Scheduler::Queue::Queue(Scheduler* scheduler, size_t size)
	: mpScheduler(scheduler)
{
	mQueue.reserve(size);
}

/**
 * @brief Move assignment.
 */
Scheduler::Queue& Scheduler::Queue::operator = (Queue&& rhs)
{
	mpScheduler = rhs.mpScheduler;
	rhs.mpScheduler = nullptr;
	return *this;
}

/**
 * @brief Move constructor.
 * @param rhs The queue to move from.
 */
Scheduler::Queue::Queue(Queue&& rhs) noexcept
	: mpScheduler(rhs.mpScheduler)
	, mQueue(Move(rhs.mQueue))
{
	rhs.mpScheduler = nullptr;
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

void Scheduler::Queue::Submit(Semaphore& semaphore)
{
	LastOneBarrier([](ThreadContext&, void* context)
	{
		reinterpret_cast<Scheduler::Semaphore*>(context)->Release();
	}, &semaphore);
}

Scheduler::Queue& Scheduler::Queue::ActiveThreads(int count)
{
	CPF_ASSERT(count > 0);
	CPF_ASSERT(count <= mpScheduler->mThreadCount);

	// Make sure anything that is outstanding completes.
	mpScheduler->_Emit(Detail::Opcodes::LastOneBarrier, [](ThreadContext&, void* context) {
		reinterpret_cast<Platform::Threading::Semaphore*>(context)->Release();
	}, &mBarrier);
	mBarrier.Acquire();

	// Issue the change.
	intptr_t intCount = intptr_t(count);
	mpScheduler->_Emit(Detail::Opcodes::ActiveThreads, nullptr, reinterpret_cast<void *>(intCount));

	return *this;
}

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

/**
 * @brief Submit the instruction queue to the scheduler.
 * @param type If the submission should clear this queue or not.
 */
Scheduler::Queue& Scheduler::Queue::Submit(SubmissionType type)
{
	(*mpScheduler)(*this);
	if (type==SubmissionType::eNormal)
		Clear();

	return *this;
}

/**
 * @brief Submit the queue and block until it completes.
 * @param type If the submission should clear this queue or not.
 */
Scheduler::Queue& Scheduler::Queue::BlockingSubmit(SubmissionType type)
{
	(*mpScheduler)(*this);
	mpScheduler->_Emit(Detail::Opcodes::LastOneBarrier, [](ThreadContext&, void* context)
	{
		reinterpret_cast<Platform::Threading::Semaphore*>(context)->Release();
	}, &mBarrier);
	if (type == SubmissionType::eNormal)
		Clear();
	mBarrier.Acquire();

	return *this;
}

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


/** @brief Clears the content of this queue. */
void Scheduler::Queue::Clear()
{
	mQueue.clear();
}
