//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/Std/Functional.hpp"
#include "CPF/Std/UnorderedMap.hpp"

namespace CPF
{
	namespace Patterns
	{
		template <typename KEYTYPE, typename OBJTYPE>
		class Factory
		{
		public:
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

			bool Create(const KEYTYPE& key, OBJTYPE** outObj) const;

			bool Exists(const KEYTYPE& key) const;

			bool Install(const KEYTYPE& key, const Entry& entry);
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
		bool Factory<KEYTYPE, OBJTYPE>::Create(const KEYTYPE& key, OBJTYPE** outObj) const
		{
			if (outObj)
			{
				*outObj = nullptr;
				auto it = mEntries.find(key);
				if (it != mEntries.end())
				{
					if (it->second.mCreate)
						*outObj = it->second.mCreate();
					if (*outObj != nullptr)
					{
						if (it->second.mInit)
						{
							if (!it->second.mInit(**outObj))
							{
								delete *outObj;
								*outObj = nullptr;
								return false;
							}
						}

						return true;
					}
				}
			}
			return false;
		}

		template <typename KEYTYPE, typename OBJTYPE>
		bool Factory<KEYTYPE, OBJTYPE>::Exists(const KEYTYPE& key) const
		{
			if (mEntries.find(key) != mEntries.end())
				return true;
			return false;
		}

		template <typename KEYTYPE, typename OBJTYPE>
		bool Factory<KEYTYPE, OBJTYPE>::Install(const KEYTYPE& key, const Entry& entry)
		{
			auto it = mEntries.find(key);
			if (it != mEntries.end())
				return false;
			mEntries.emplace(key, entry);
			return true;
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
