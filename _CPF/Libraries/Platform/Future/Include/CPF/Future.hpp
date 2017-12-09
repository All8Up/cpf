//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Mutex.hpp"
#include "Threading/ConditionVariable.hpp"
#include "Threading/ScopedLock.hpp"
#include "RefCounted.hpp"
#include "Move.hpp"

namespace CPF
{
	template <typename TYPE>
	class FutureState : public tRefCounted<iRefCounted>
	{
	public:
		~FutureState()
		{}
		void SetResult(TYPE&& value)
		{
			Threading::ScopedLock<Threading::Mutex> lock(mLock);
			mValue = Move(value);
			mState = State::eValue;
			mCondition.ReleaseAll();
		}
		void SetException(std::exception_ptr&& value)
		{
			Threading::ScopedLock<Threading::Mutex> lock(mLock);
			mException = Move(value);
			mState = State::eException;
			mCondition.ReleaseAll();
		}

		void Wait()
		{
			Threading::ScopedLock<Threading::Mutex> lock(mLock);
			mCondition.Acquire(mLock, [this]() -> bool {
				return mState != State::eNone;
			});
		}
		TYPE&& Get()
		{
			Threading::ScopedLock<Threading::Mutex> lock(mLock);
			mCondition.Acquire(mLock, [this]() -> bool {
				return mState != State::eNone;
			});

			if (mState == State::eTaken)
				throw std::exception();
			if (mState == State::eException)
				std::rethrow_exception(mException);
			mState = State::eTaken;

			return Move(mValue);
		}

	private:
		enum class State
		{
			eNone,
			eValue,
			eException,
			eTaken
		};

		Threading::Mutex mLock;
		Threading::ConditionVariable mCondition;
		State mState;
		TYPE mValue;
		std::exception_ptr mException;
	};


	//////////////////////////////////////////////////////////////////////////
	template <typename TYPE>
	class Future;
	template <typename TYPE>
	class Future<TYPE&>;
	template <>
	class Future<void>;

	template <typename TYPE>
	class Future
	{
	public:
		Future() {}
		Future(const Future&) = delete;
		Future& operator =(const Future&) = delete;
		Future(Future&& rhs) noexcept : mpState(Move(rhs.mpState)) {}
		Future& operator =(Future&& rhs) noexcept { mpState = rhs.mpState; rhs.mpState = nullptr; return *this; }
		~Future()
		{}

		bool IsValid() const noexcept { return mpState!=nullptr; }

		TYPE&& Get() { return mpState->Get(); }

		void Wait() const { mpState->Wait(); }

	private:
		template<typename PTYPE>
		friend class Promise;

		Future(FutureState<TYPE>* pstate)
		: mpState(pstate)
		{
			mpState->AddRef();
		}

		IntrusivePtr<FutureState<TYPE>> mpState;
	};

	template <typename TYPE>
	class Future<TYPE&>
	{
		
	};

	template <>
	class Future<void>
	{
	public:
		Future() {}
		Future(const Future&) = delete;
		Future& operator =(const Future&) = delete;
		Future(Future&&) noexcept {}
		Future& operator =(Future&&) noexcept { return *this; }

		void Get() {}
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename TYPE>
	class Promise;
	template <typename TYPE>
	class Promise<TYPE&>;
	template <>
	class Promise<void>;

	template <typename TYPE>
	class Promise
	{
	public:
		Promise()
			: mpFutureState(new FutureState<TYPE>())
			, mFuture(mpFutureState)
		{
		}
		Promise(const Promise&) = delete;
		Promise& operator =(const Promise&) = delete;
		Promise(Promise&& rhs) noexcept
			: mpFutureState(Move(rhs.mpFutureState))
			, mFuture(Move(rhs.mFuture))
		{}
		Promise& operator =(Promise&& rhs) noexcept
		{
			mpFutureState = Move(rhs.mpFutureState);
			mFuture = Move(rhs.mFuture);
			return *this;
		}
		~Promise()
		{
			if (mpFutureState)
				mpFutureState->SetException(std::make_exception_ptr<std::exception>(std::exception()));
		}

		Future<TYPE> GetFuture() { return Move(mFuture); }

		void SetResult(TYPE&& value) { if (mpFutureState) mpFutureState->SetResult(Move(value)); else throw std::exception(); mpFutureState.Adopt(nullptr); }
		void SetException(std::exception_ptr&& ptr) { if (mpFutureState) mpFutureState->SetException(Move(ptr)); else throw std::exception(); mpFutureState.Adopt(nullptr); }

	private:
		IntrusivePtr<FutureState<TYPE>> mpFutureState;
		Future<TYPE> mFuture;
	};

	template <typename TYPE>
	class Promise<TYPE&>
	{

	};

	template <>
	class Promise<void>
	{
	public:
		Promise() {}
		Promise(const Promise&) = delete;
		Promise& operator =(const Promise&) = delete;
		Promise(Promise&&) noexcept {}
		Promise& operator =(Promise&&) noexcept { return *this; }

		Future<void> GetFuture() { return Move(mFuture); }

	private:
		Future<void> mFuture;
	};
}
