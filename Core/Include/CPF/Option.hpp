//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	template <typename OK_TYPE, typename ERROR_TYPE = void>
	class Option
	{
	public:
		Option();
		Option(Option&&);
		~Option();

		static Option OK(const OK_TYPE&);
		static Option OK(OK_TYPE&&);
		static Option Error(const ERROR_TYPE&);
		static Option Error(ERROR_TYPE&&);

		Option& operator = (Option&&);

		bool IsOK() const;
		bool IsError() const;

		OK_TYPE& GetOK();
		const OK_TYPE& GetOK() const;
		bool CheckOK(OK_TYPE& ok);
		bool CheckOK(OK_TYPE* ok);

		ERROR_TYPE& GetError();
		const ERROR_TYPE& GetError() const;
		bool CheckError(ERROR_TYPE& error);

	private:
		Option(const Option&) = delete;
		Option& operator = (const Option&) = delete;

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
	Option<OK_TYPE, ERROR_TYPE>::Option()
		: mType(Type::eNotSet)
	{}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Option<OK_TYPE, ERROR_TYPE>::Option(Option&& rhs)
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
	Option<OK_TYPE, ERROR_TYPE>::~Option()
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
	Option<OK_TYPE, ERROR_TYPE> Option<OK_TYPE, ERROR_TYPE>::OK(const OK_TYPE& ok)
	{
		Option result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(ok);
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Option<OK_TYPE, ERROR_TYPE> Option<OK_TYPE, ERROR_TYPE>::OK(OK_TYPE&& ok)
	{
		Option result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(Move(ok));
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Option<OK_TYPE, ERROR_TYPE> Option<OK_TYPE, ERROR_TYPE>::Error(const ERROR_TYPE& error)
	{
		Option result;
		result.mType = Type::eError;
		new (&result.mData.mError) ERROR_TYPE(error);
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Option<OK_TYPE, ERROR_TYPE> Option<OK_TYPE, ERROR_TYPE>::Error(ERROR_TYPE&& error)
	{
		Option result;
		result.mType = Type::eError;
		new (&result.mData.mError) ERROR_TYPE(Move(error));
		return result;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	Option<OK_TYPE, ERROR_TYPE>& Option<OK_TYPE, ERROR_TYPE>::operator = (Option&& rhs)
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
	bool Option<OK_TYPE, ERROR_TYPE>::IsOK() const
	{
		return mType == Type::eOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Option<OK_TYPE, ERROR_TYPE>::IsError() const
	{
		return mType == Type::eError;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	OK_TYPE& Option<OK_TYPE, ERROR_TYPE>::GetOK()
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Option<OK_TYPE, ERROR_TYPE>::CheckOK(OK_TYPE& ok)
	{
		if (mType == Type::eOK)
		{
			ok = Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Option<OK_TYPE, ERROR_TYPE>::CheckOK(OK_TYPE* ok)
	{
		if (mType == Type::eOK)
		{
			*ok = Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	const OK_TYPE& Option<OK_TYPE, ERROR_TYPE>::GetOK() const
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	ERROR_TYPE& Option<OK_TYPE, ERROR_TYPE>::GetError()
	{
		CPF_ASSERT(mType == Type::eError);
		return mData.mError;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	bool Option<OK_TYPE, ERROR_TYPE>::CheckError(ERROR_TYPE& error)
	{
		if (mType == Type::mError)
		{
			error = Move(mData.mError);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE, typename ERROR_TYPE>
	const ERROR_TYPE& Option<OK_TYPE, ERROR_TYPE>::GetError() const
	{
		CPF_ASSERT(mType == Type::eError);
		return mData.mError;
	}

	//////////////////////////////////////////////////////////////////////////
	template <typename OK_TYPE>
	class Option<OK_TYPE, void>
	{
	public:
		Option();
		Option(Option&&);
		~Option();

		static Option OK(OK_TYPE&&);
		static Option Error();

		Option& operator = (Option&&);

		bool IsOK() const;
		bool IsError() const;

		OK_TYPE& GetOK();
		const OK_TYPE& GetOK() const;
		bool CheckOK(OK_TYPE& ok);

	private:
		Option(const Option&) = delete;
		Option& operator = (const Option&) = delete;

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
	Option<OK_TYPE, void>::Option()
		: mType(Type::eNotSet)
	{}

	template <typename OK_TYPE>
	Option<OK_TYPE, void>::Option(Option&& rhs)
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
	Option<OK_TYPE, void>::~Option()
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
	Option<OK_TYPE, void> Option<OK_TYPE, void>::OK(OK_TYPE&& ok)
	{
		Option result;
		result.mType = Type::eOK;
		new (&result.mData.mOK) OK_TYPE(Move(ok));
		return result;
	}

	template <typename OK_TYPE>
	Option<OK_TYPE, void> Option<OK_TYPE, void>::Error()
	{
		Option result;
		result.mType = Type::eError;
		return result;
	}

	template <typename OK_TYPE>
	Option<OK_TYPE, void>& Option<OK_TYPE, void>::operator = (Option&& rhs)
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
	bool Option<OK_TYPE, void>::IsOK() const
	{
		return mType == Type::eOK;
	}

	template <typename OK_TYPE>
	bool Option<OK_TYPE, void>::IsError() const
	{
		return mType == Type::eError;
	}

	template <typename OK_TYPE>
	OK_TYPE& Option<OK_TYPE, void>::GetOK()
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}

	template <typename OK_TYPE>
	bool Option<OK_TYPE, void>::CheckOK(OK_TYPE& ok)
	{
		if (mType == Type::eOK)
		{
			ok = Move(mData.mOK);
			return true;
		}
		return false;
	}

	template <typename OK_TYPE>
	const OK_TYPE& Option<OK_TYPE, void>::GetOK() const
	{
		CPF_ASSERT(mType == Type::eOK);
		return mData.mOK;
	}
}
