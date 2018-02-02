//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/Std/Functional.hpp"
#include "CPF/Std/UnorderedMap.hpp"
#include "CPF/Outcome.hpp"

namespace CPF
{
	namespace Patterns
	{
		enum class FactoryError : int
		{
			eNone = 0,
			eNotFound,
			eCreationFailure,
			eInitFailure
		};

		template <typename KEYTYPE, typename OBJTYPE>
		class Factory
		{
		public:
			using Error = FactoryError;

			struct Entry
			{
				using CreateType = Function<OBJTYPE* ()>;
				using InitType = Function<bool(OBJTYPE&)>;

				Entry(CreateType&& create) : mCreate(Move(create)) {}
				Entry(CreateType&& create, InitType&& init) : mCreate(Move(create)), mInit(Move(init)) {}

				CreateType mCreate;
				InitType mInit;
			};

			Factory();
			~Factory();

			Outcome<OBJTYPE*, Error> Create(const KEYTYPE& key) const;

			bool Exists(const KEYTYPE& key) const;

			Error Install(const KEYTYPE& key, const Entry& entry);
			bool Remove(const KEYTYPE& key);

		private:
			Factory(Factory&&) = delete;
			Factory(const Factory&) = delete;
			Factory& operator = (Factory&&) = delete;
			Factory& operator = (const Factory&&) = delete;

			using EntryMap = UnorderedMap<KEYTYPE, Entry>;
			EntryMap mEntries;
		};

		template <typename KEYTYPE, typename OBJTYPE>
		Factory<KEYTYPE, OBJTYPE>::Factory()
		{}

		template <typename KEYTYPE, typename OBJTYPE>
		Factory<KEYTYPE, OBJTYPE>::~Factory()
		{}

		template <typename KEYTYPE, typename OBJTYPE>
		Outcome<OBJTYPE*, FactoryError> Factory<KEYTYPE, OBJTYPE>::Create(const KEYTYPE& key) const
		{
			auto it = mEntries.find(key);
			if (it != mEntries.end())
			{
				OBJTYPE* result = nullptr;
				if (it->second.mCreate)
					result = it->second.mCreate();
				if (result != nullptr)
				{
					if (it->second.mInit)
					{
						if (!it->second.mInit(*result))
						{
							delete result;
							return Outcome<OBJTYPE*, FactoryError>::Error(Error::eInitFailure);
						}
					}
					return Outcome<OBJTYPE*, FactoryError>::OK(result);
				}
				return Outcome<OBJTYPE*, FactoryError>::Error(Error::eCreationFailure);
			}
			return Outcome<OBJTYPE*, FactoryError>::Error(Error::eNotFound);
		}

		template <typename KEYTYPE, typename OBJTYPE>
		bool Factory<KEYTYPE, OBJTYPE>::Exists(const KEYTYPE& key) const
		{
			if (mEntries.find(key) != mEntries.end())
				return true;
			return false;
		}

		template <typename KEYTYPE, typename OBJTYPE>
		FactoryError Factory<KEYTYPE, OBJTYPE>::Install(const KEYTYPE& key, const Entry& entry)
		{
			auto it = mEntries.find(key);
			if (it != mEntries.end())
				return FactoryError::eNotFound;
			mEntries.emplace(key, entry);
			return FactoryError::eNone;
		}

		template <typename KEYTYPE, typename OBJTYPE>
		bool Factory<KEYTYPE, OBJTYPE>::Remove(const KEYTYPE& key)
		{
			auto it = mEntries.find(key);
			if (it != mEntries.end())
			{
				mEntries.erase(it);
				return true;
			}
			return false;
		}
	}
}
