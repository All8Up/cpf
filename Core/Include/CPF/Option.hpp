//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	template <typename SOME_TYPE>
	class Option
	{
	public:
		Option();
		Option(Option&&) noexcept;
		~Option();

		static Option Some(const SOME_TYPE&);
		static Option Some(SOME_TYPE&&);
		static Option None();

		Option& operator = (Option&&) noexcept;

		bool IsSome() const;
		bool IsNone() const;

		SOME_TYPE& GetSome();
		const SOME_TYPE& GetSome() const;
		bool CheckSome(SOME_TYPE& ok) const;
		bool CheckSome(SOME_TYPE* ok) const;

	private:
		Option(const Option&) = delete;
		Option& operator = (const Option&) = delete;

		enum class Type : int32_t
		{
			eNotSet,
			eSome,
			eNone
		};
		Type mType;
		SOME_TYPE mSome;
	};

	//////////////////////////////////////////////////////////////////////////

	template <typename SOME_TYPE>
	Option<SOME_TYPE>::Option()
		: mType(Type::eNotSet)
	{}

	template <typename SOME_TYPE>
	Option<SOME_TYPE>::Option(Option&& rhs) noexcept
		: mType(rhs.mType)
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eSome:
			mSome = Move(rhs.mSome);
			break;
		case Type::eNone:
			break;
		}
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE>::~Option()
	{
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE> Option<SOME_TYPE>::Some(const SOME_TYPE& some)
	{
		Option result;
		result.mType = Type::eSome;
		result.mSome = Move(some);
		return result;
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE> Option<SOME_TYPE>::Some(SOME_TYPE&& some)
	{
		Option result;
		result.mType = Type::eSome;
		result.mSome = some;
		return result;
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE> Option<SOME_TYPE>::None()
	{
		Option result;
		result.mType = Type::eNone;
		return result;
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE>& Option<SOME_TYPE>::operator = (Option&& rhs) noexcept
	{
		mType = rhs.mType;
		mType = Move(rhs.mSome);
		rhs.mType = Type::eNotSet;
		return *this;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE>::IsSome() const
	{
		return mType == Type::eSome;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE>::IsNone() const
	{
		return mType == Type::eNone;
	}

	template <typename SOME_TYPE>
	SOME_TYPE& Option<SOME_TYPE>::GetSome()
	{
		CPF_ASSERT(mType == Type::eSome);
		return mSome;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE>::CheckSome(SOME_TYPE& some) const
	{
		if (mType == Type::eSome)
		{
			some = Move(mSome);
			return true;
		}
		return false;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE>::CheckSome(SOME_TYPE* some) const
	{
		if (mType == Type::eSome)
		{
			*some = Move(mSome);
			return true;
		}
		return false;
	}

	template <typename SOME_TYPE>
	const SOME_TYPE& Option<SOME_TYPE>::GetSome() const
	{
		CPF_ASSERT(mType == Type::eSome);
		return mSome;
	}

	//////////////////////////////////////////////////////////////////////////
	template <typename SOME_TYPE>
	class Option<SOME_TYPE&>
	{
	public:
		// Invalid variation.
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename SOME_TYPE>
	class Option<SOME_TYPE*>
	{
	public:
		Option();
		Option(Option&&) noexcept;
		~Option();

		static Option Some(SOME_TYPE*);
		static Option None();

		Option& operator = (Option&&) noexcept;

		bool IsSome() const;
		bool IsNone() const;

		SOME_TYPE* GetSome();
		bool CheckSome(SOME_TYPE** ok);

	private:
		Option(const Option&) = delete;
		Option& operator = (const Option&) = delete;

		enum class Type : int32_t
		{
			eNotSet,
			eSome,
			eNone
		};
		Type mType;
		SOME_TYPE* mSome;
	};

	template <typename SOME_TYPE>
	Option<SOME_TYPE*>::Option()
		: mType(Type::eNotSet)
	{}

	template <typename SOME_TYPE>
	Option<SOME_TYPE*>::Option(Option&& rhs) noexcept
		: mType(rhs.mType)
	{
		switch (mType)
		{
		case Type::eNotSet:
			break;
		case Type::eSome:
			mSome = Move(rhs.mSome);
			break;
		case Type::eNone:
			break;
		}
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE*>::~Option()
	{
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE*> Option<SOME_TYPE*>::Some(SOME_TYPE* some)
	{
		Option result;
		result.mType = Type::eSome;
		result.mSome = Move(some);
		return result;
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE*> Option<SOME_TYPE*>::None()
	{
		Option result;
		result.mType = Type::eNone;
		return result;
	}

	template <typename SOME_TYPE>
	Option<SOME_TYPE*>& Option<SOME_TYPE*>::operator = (Option&& rhs) noexcept
	{
		mType = rhs.mType;
		mType = Move(rhs.mSome);
		rhs.mType = Type::eNotSet;
		return *this;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE*>::IsSome() const
	{
		return mType == Type::eSome;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE*>::IsNone() const
	{
		return mType == Type::eNone;
	}

	template <typename SOME_TYPE>
	SOME_TYPE* Option<SOME_TYPE*>::GetSome()
	{
		CPF_ASSERT(mType == Type::eSome);
		return mSome;
	}

	template <typename SOME_TYPE>
	bool Option<SOME_TYPE*>::CheckSome(SOME_TYPE** some)
	{
		if (mType == Type::eSome)
		{
			*some = Move(mSome);
			return true;
		}
		return false;
	}
}
