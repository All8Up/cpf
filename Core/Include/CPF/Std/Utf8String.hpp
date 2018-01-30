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
			Utf8String(const String::value_type* str) : mString(str) {}
			Utf8String(const String& rhs) : mString(rhs) {}
			Utf8String(const WString& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }
			Utf8String(String&& rhs) : mString(Move(rhs)) {}
			Utf8String(WString&& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }

			bool operator ==(const Utf8String& rhs) const { return mString == rhs.mString; }
			bool operator !=(const Utf8String& rhs) const { return mString != rhs.mString; }

			Utf8String& operator = (const Utf8String& rhs) { mString = rhs.mString; return *this; }

			Utf8String& operator +=(const Utf8String& rhs);
			
			const_iterator begin() const;
			const_reverse_iterator rbegin() const;

			const_iterator end() const;
			const_reverse_iterator rend() const;

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
			const_iterator() : mCurrent(nullptr, nullptr, nullptr) {}
			const_iterator(const const_iterator& rhs) : mCurrent(rhs.mCurrent) {}
			const_iterator(const_iterator&& rhs) : mCurrent(Move(rhs.mCurrent)) {}
			
			const_iterator& operator = (const const_iterator& rhs) { mCurrent = rhs.mCurrent; return *this; }
			const_iterator& operator = (const_iterator&& rhs) { mCurrent = Move(rhs.mCurrent); return *this; }
			
			bool operator ==(const const_iterator& rhs) const { return mCurrent == rhs.mCurrent; }
			bool operator !=(const const_iterator& rhs) const { return mCurrent != rhs.mCurrent; }

			bool operator <(const const_iterator& rhs) const { return mCurrent.base() < rhs.mCurrent.base(); }
			
			uint32_t operator *() const { return *mCurrent; }
			
			const_iterator& operator ++() { ++mCurrent; return *this; }
			const_iterator operator++(int) { const_iterator result(*this); ++mCurrent; return result; }
			const_iterator& operator --() { --mCurrent; return *this; }
			const_iterator operator --(int) { const_iterator result(*this); --mCurrent; return result; }
			
		protected:
			friend class Utf8String;
			
			const_iterator(const String::value_type* it, const String::value_type* start, const String::value_type* end)
				: mCurrent(it, start, end)
			{
			}
			
			utf8::iterator<const String::value_type*> mCurrent;
		};

		//////////////////////////////////////////////////////////////////////////
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
