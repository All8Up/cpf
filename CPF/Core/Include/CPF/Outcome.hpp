//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	template <typename OK_TYPE, typename ERROR_TYPE = void>
	class Outcome
	{
	public:
		Outcome();
		Outcome(Outcome&&);
		~Outcome();

		static Outcome OK(const OK_TYPE&);
		static Outcome OK(OK_TYPE&&);
		static Outcome Error(const ERROR_TYPE&);
		static Outcome Error(ERROR_TYPE&&);

		Outcome& operator = (Outcome&&);

		bool IsOK() const;
		bool IsError() const;

		OK_TYPE& GetOK();
		const OK_TYPE& GetOK() const;
		bool CheckOK(OK_TYPE& ok) const;
		bool CheckOK(OK_TYPE* ok) const;

		OK_TYPE TryOK() const { if (mType == Type::eOK) return mData.mOK; return nullptr; }

		ERROR_TYPE& GetError();
		const ERROR_TYPE& GetError() const;
		bool CheckError(ERROR_TYPE& error) const;

	private:
		Outcome(const Outcome&) = delete;
		Outcome& operator = (const Outcome&) = delete;

		enum class Type : int32_t
		{
			eNotSet,
			eOK,
			eError
		};
		union Data
		{
			Data() {}
			~Data() {}

			OK_TYPE mOK;
			ERROR_TYPE mError;
		};

		Type mType;
		Data mData;
	};

	//////////////////////////////////////////////////////////////////////////

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE>::Outcome()
		: mType(Type::eNotSet)
	{}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE>::Outcome(Outcome&& rhs)
		: mType(rhs.mType)
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			new (&mData.mOK) OK_TYPE(STD::Move(rhs.mData.mOK));
			break;
		case Type::eError:
			new (&mData.mError) ERROR_TYPE(STD::Move(rhs.mData.mError));
			break;
		}
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE>::~Outcome()
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			mData.mOK.~OK_TYPE();
			break;
		case Type::eError:
			mData.mError.~ERROR_TYPE();
			break;
		}
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE> Outcome<OK_TYPE, ERROR_TYPE>::OK(const OK_TYPE& ok)
	{
		Outcome result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(ok);
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE> Outcome<OK_TYPE, ERROR_TYPE>::OK(OK_TYPE&& ok)
	{
		Outcome result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(STD::Move(ok));
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE> Outcome<OK_TYPE, ERROR_TYPE>::Error(const ERROR_TYPE& error)
	{
		Outcome result;
		result.mType = Type::eError;
		new (&result.mData.mError) ERROR_TYPE(error);
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE> Outcome<OK_TYPE, ERROR_TYPE>::Error(ERROR_TYPE&& error)
	{
		Outcome result;
		result.mType = Type::eError;
		new (&result.mData.mError) ERROR_TYPE(STD::Move(error));
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Outcome<OK_TYPE, ERROR_TYPE>& Outcome<OK_TYPE, ERROR_TYPE>::operator = (Outcome&& rhs)
	{
		CPF_ASSERT(mType == Type::eNotSet);
		mType = rhs.mType;
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			new (&mData.mOK) OK_TYPE(STD::Move(rhs.mData.mOK));
			break;
		case Type::eError:
			new (&mData.mError) OK_TYPE(STD::Move(rhs.mData.mError));
			break;
		}
		return *this;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::IsOK() const
	{
		return mType == Type::eOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::IsError() const
	{
		return mType == Type::eError;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	OK_TYPE& Outcome<OK_TYPE, ERROR_TYPE>::GetOK()
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::CheckOK(OK_TYPE& ok) const
	{
		if (mType == Type::eOK)
		{
			ok = STD::Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::CheckOK(OK_TYPE* ok) const
	{
		if (mType == Type::eOK)
		{
			*ok = STD::Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	const OK_TYPE& Outcome<OK_TYPE, ERROR_TYPE>::GetOK() const
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	ERROR_TYPE& Outcome<OK_TYPE, ERROR_TYPE>::GetError()
	{
		CPF_ASSERT(mType == Type::eError);
		return mData.mError;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::CheckError(ERROR_TYPE& error) const
	{
		if (mType == Type::mError)
		{
			error = STD::Move(mData.mError);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	const ERROR_TYPE& Outcome<OK_TYPE, ERROR_TYPE>::GetError() const
	{
		CPF_ASSERT(mType == Type::eError);
		return mData.mError;
	}
}
