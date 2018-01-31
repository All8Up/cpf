//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Move.hpp"
#include "CPF/Std/String.hpp"
#include "utf8.h"

namespace CPF
{
	namespace Std
	{
	
		class Utf8String
		{
		public:
			class const_iterator;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			Utf8String() : mString() {}
			Utf8String(const_iterator first, const_iterator last);
			Utf8String(const String::value_type* str) : mString(str) {}
			Utf8String(const String& rhs) : mString(rhs) {}
			Utf8String(const WString& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }
			Utf8String(String&& rhs) : mString(Move(rhs)) {}
			Utf8String(WString&& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }

			bool operator ==(const Utf8String& rhs) const { return mString == rhs.mString; }
			bool operator !=(const Utf8String& rhs) const { return mString != rhs.mString; }

			Utf8String& operator = (const Utf8String& rhs) { mString = rhs.mString; return *this; }

			Utf8String& operator +=(uint32_t c);
			Utf8String& operator +=(const Utf8String& rhs);
			
			const_iterator begin() const;
			const_reverse_iterator rbegin() const;

			const_iterator end() const;
			const_reverse_iterator rend() const;

			uint32_t at(size_t pos) const
			{
				auto ibegin = mString.begin();
				const auto iend = mString.end();
				utf8::advance(ibegin, pos, iend);
				uint32_t result[4];
				utf8::utf8to32(ibegin, ibegin+1, result);
				return result[0];
			}

			void erase(const_iterator start, const_iterator end);

			void clear() { mString.clear(); }
			bool empty() const { return mString.empty(); }
			size_t size() const;
			size_t length() const;
			void resize(size_t size) { mString.resize(size); }
			
			String& data();
			const String& data() const;
			
		private:
			String mString;
		};
		
		//////////////////////////////////////////////////////////////////////////
		// There should be no non-const iteration.
		class Utf8String::const_iterator : public String::const_iterator
		{
		public:
			const_iterator() : mCurrent(nullptr, nullptr, nullptr), mEnd(nullptr, nullptr, nullptr) {}
			const_iterator(const const_iterator& rhs) : mCurrent(rhs.mCurrent), mEnd(rhs.mEnd) {}
			const_iterator(const_iterator&& rhs) : mCurrent(Move(rhs.mCurrent)), mEnd(Move(rhs.mEnd)) {}
			
			const String::value_type* base() const { return mCurrent.base(); }
			
			const_iterator& operator = (const const_iterator& rhs) { mCurrent = rhs.mCurrent; mEnd = rhs.mEnd; return *this; }
			const_iterator& operator = (const_iterator&& rhs) noexcept { mCurrent = Move(rhs.mCurrent); mEnd = Move(rhs.mEnd); return *this; }
			
			bool operator ==(const const_iterator& rhs) const { return mCurrent == rhs.mCurrent; }
			bool operator !=(const const_iterator& rhs) const { return mCurrent != rhs.mCurrent; }

			bool operator <(const const_iterator& rhs) const { return mCurrent.base() < rhs.mCurrent.base(); }
			
			uint32_t operator *() const { return *mCurrent; }
			
			const_iterator& operator ++() { ++mCurrent; return *this; }
			const_iterator operator++(int) { const_iterator result(*this); ++mCurrent; return result; }
			const_iterator& operator --() { --mCurrent; return *this; }
			const_iterator operator --(int) { const_iterator result(*this); --mCurrent; return result; }
			
			const_iterator operator +(size_t delta) const
			{
				auto result = mCurrent;
				while (delta--)
					++result;
				return { result.base(), mCurrent.base(), mEnd.base() };
			}
			
		protected:
			friend class Utf8String;
			
			const_iterator(const String::value_type* it, const String::value_type* start, const String::value_type* end)
				: mCurrent(it, start, end)
				, mEnd(end, start, end)
			{
			}
			
			utf8::iterator<const String::value_type*> mCurrent;
			utf8::iterator<const String::value_type*> mEnd;
		};

		//////////////////////////////////////////////////////////////////////////
		inline Utf8String::Utf8String(const_iterator first, const_iterator last)
			: mString(first.base(), last.base())
		{}

		inline Utf8String::const_iterator Utf8String::begin() const
		{
			return const_iterator{ mString.data(), mString.data(), mString.data()+mString.length() };
		}
		
		inline Utf8String::const_iterator Utf8String::end() const
		{
			return const_iterator{ mString.data() + mString.length(), mString.data(), mString.data()+mString.length() };
		}

		inline Utf8String::const_reverse_iterator Utf8String::rbegin() const
		{
			return const_reverse_iterator{ { mString.data() + mString.length(), mString.data(), mString.data() + mString.length() } };
		}

		inline Utf8String::const_reverse_iterator Utf8String::rend() const
		{
			return const_reverse_iterator{ { mString.data(), mString.data(), mString.data() + mString.length() } };
		}

		inline Utf8String& Utf8String::operator +=(uint32_t c)
		{
			uint8_t composeBuffer[5];
			const auto endBuffer = utf8::append(c, composeBuffer);
			mString.append(composeBuffer, endBuffer);
			return *this;
		}

		inline Utf8String& Utf8String::operator +=(const Utf8String& rhs)
		{
			mString = mString + rhs.mString;
			return *this;
		}
		
		inline Utf8String operator + (char c, const Utf8String& rhs)
		{
			String result;
			result.push_back(c);
			result += rhs.data();
			return Utf8String(result);
		}
		
		inline void Utf8String::erase(const_iterator start, const_iterator end)
		{
			auto b = start.base() - mString.data();
			auto e = end.base() - mString.data();
			mString.erase(mString.begin() + b, mString.begin() + e);
		}

		inline size_t Utf8String::length() const
		{
			return utf8::distance(begin(), end());
		}

		inline String& Utf8String::data()
		{
			return mString;
		}

		inline const String& Utf8String::data() const
		{
			return mString;
		}


		//////////////////////////////////////////////////////////////////////////
		inline bool ConvertUtf8To16(const Utf8String& inString, WString& outString)
		{
			try
			{
				auto ibegin = inString.begin();
				auto iend = inString.end();
				utf8::utf8to16(ibegin, iend, std::back_inserter(outString));
			}
			catch (...)
			{
				return false;
			}
			return true;
		}
	}
}
