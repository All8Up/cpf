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
			new (&mData.mOK) OK_TYPE(Move(rhs.mData.mOK));
			break;
		case Type::eError:
			new (&mData.mError) ERROR_TYPE(Move(rhs.mData.mError));
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
		new (&result.mData.mOK) OK_TYPE(Move(ok));
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
		new (&result.mData.mError) ERROR_TYPE(Move(error));
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
			new (&mData.mOK) OK_TYPE(Move(rhs.mData.mOK));
			break;
		case Type::eError:
			new (&mData.mError) OK_TYPE(Move(rhs.mData.mError));
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
			ok = Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Outcome<OK_TYPE, ERROR_TYPE>::CheckOK(OK_TYPE* ok) const
	{
		if (mType == Type::eOK)
		{
			*ok = Move(mData.mOK);
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
			error = Move(mData.mError);
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

	//////////////////////////////////////////////////////////////////////////
	template <typename OK_TYPE>
	class Outcome<OK_TYPE, void>
	{
	public:
		Outcome();
		Outcome(Outcome&&);
		~Outcome();

		static Outcome OK(OK_TYPE&&);
		static Outcome Error();

		Outcome& operator = (Outcome&&);

		bool IsOK() const;
		bool IsError() const;

		OK_TYPE& GetOK();
		const OK_TYPE& GetOK() const;
		bool CheckOK(OK_TYPE& ok);

	private:
		Outcome(const Outcome&) = delete;
		Outcome& operator = (const Outcome&) = delete;

		union Data
		{
			Data() {}
			~Data() {}

			OK_TYPE mOK;
		};
		enum class Type : int32_t
		{
			eNotSet,
			eOK,
			eError
		};

		Data mData;
		Type mType;
	};
	
	//////////////////////////////////////////////////////////////////////////

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void>::Outcome()
		: mType(Type::eNotSet)
	{}

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void>::Outcome(Outcome&& rhs)
		: mType(rhs.mType)
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			new (&mData.mOK) OK_TYPE(Move(rhs.mData.mOK));
			break;
		}
	}

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void>::~Outcome()
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			mData.mOK.~OK_TYPE();
			break;
		}
	}

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void> Outcome<OK_TYPE, void>::OK(OK_TYPE&& ok)
	{
		Outcome result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(Move(ok));
		return result;
	}

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void> Outcome<OK_TYPE, void>::Error()
	{
		Outcome result;
		result.mType = Type::eError;
		return result;
	}

	template <typename OK_TYPE>
	Outcome<OK_TYPE, void>& Outcome<OK_TYPE, void>::operator = (Outcome&& rhs)
	{
		CPF_ASSERT(mType == Type::eNotSet);
		mType = rhs.mType;
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eOK:
			new (&mData.mOK) OK_TYPE(Move(rhs.mData.mOK));
			break;
		}
		return *this;
	}

	template <typename OK_TYPE>
	bool Outcome<OK_TYPE, void>::IsOK() const
	{
		return mType == Type::eOK;
	}

	template <typename OK_TYPE>
	bool Outcome<OK_TYPE, void>::IsError() const
	{
		return mType == Type::eError;
	}

	template <typename OK_TYPE>
	OK_TYPE& Outcome<OK_TYPE, void>::GetOK()
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE>
	bool Outcome<OK_TYPE, void>::CheckOK(OK_TYPE& ok)
	{
		if (mType == Type::eOK)
		{
			ok = Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE>
	const OK_TYPE& Outcome<OK_TYPE, void>::GetOK() const
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}
}
