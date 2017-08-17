//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Configuration.hpp>

namespace Cpf
{
	namespace IO
	{
		template <typename OK_TYPE, typename ERROR_TYPE>
		class Result
		{
		public:
			Result();
			Result(Result&&);
			Result(OK_TYPE ok);
			Result(ERROR_TYPE error);
			~Result();

			Result& operator = (Result&&);

			bool IsOK() const;
			bool IsError() const;

			OK_TYPE& OK();
			const OK_TYPE& OK() const;
			ERROR_TYPE& Error();
			const ERROR_TYPE& Error() const;

		private:
			Result(const Result&) = delete;
			Result& operator = (const Result&) = delete;

			union Data
			{
				Data() {}
				~Data() {}

				OK_TYPE mOK;
				ERROR_TYPE mError;
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

		template <typename OK_TYPE, typename ERROR_TYPE>
		Result<OK_TYPE, ERROR_TYPE>::Result()
			: mType(Type::eNotSet)
		{}

		template <typename OK_TYPE, typename ERROR_TYPE>
		Result<OK_TYPE, ERROR_TYPE>::Result(Result&& rhs)
			: mType(rhs.mType)
		{
			switch (mType)
			{
			case Type::eNotSet:
				break;
			case Type::eOK:
				new (&mData.mOK) OK_TYPE(std::move(rhs.mData.mOK));
				break;
			case Type::eError:
				new (&mData.mError) ERROR_TYPE(std::move(rhs.mData.mError));
				break;
			}
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		Result<OK_TYPE, ERROR_TYPE>::Result(OK_TYPE ok)
			: mType(Type::eOK)
		{
			new (&mData.mOK) OK_TYPE(std::move(ok));
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		Result<OK_TYPE, ERROR_TYPE>::Result(ERROR_TYPE error)
		{
			new (&mData.mError) ERROR_TYPE(std::move(error));
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		Result<OK_TYPE, ERROR_TYPE>::~Result()
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
		Result<OK_TYPE, ERROR_TYPE>& Result<OK_TYPE, ERROR_TYPE>::operator = (Result&& rhs)
		{
			CPF_ASSERT(mType == Type::eNotSet);
			mType = rhs.mType;
			switch (mType)
			{
			case Type::eNotSet:
				break;
			case Type::eOK:
				new (&mData.mOK) OK_TYPE(std::move(rhs.mData.mOK));
				break;
			case Type::eError:
				new (&mData.mError) OK_TYPE(std::move(rhs.mData.mError));
				break;
			}
			return *this;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		bool Result<OK_TYPE, ERROR_TYPE>::IsOK() const
		{
			return mType == Type::eOK;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		bool Result<OK_TYPE, ERROR_TYPE>::IsError() const
		{
			return mType == Type::eError;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		OK_TYPE& Result<OK_TYPE, ERROR_TYPE>::OK()
		{
			CPF_ASSERT(mType == Type::eOK);
			return mData.mOK;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		const OK_TYPE& Result<OK_TYPE, ERROR_TYPE>::OK() const
		{
			CPF_ASSERT(mType == Type::eOK);
			return mData.mOK;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		ERROR_TYPE& Result<OK_TYPE, ERROR_TYPE>::Error()
		{
			CPF_ASSERT(mType == Type::eError);
			return mData.mError;
		}

		template <typename OK_TYPE, typename ERROR_TYPE>
		const ERROR_TYPE& Result<OK_TYPE, ERROR_TYPE>::Error() const
		{
			CPF_ASSERT(mType == Type::eError);
			return mData.mError;
		}
	}
}
