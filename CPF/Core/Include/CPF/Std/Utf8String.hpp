//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Move.hpp"
#include "CPF/Std/String.hpp"
#include "utf8.h"

namespace CPF
{
	namespace STD
	{
		class Utf8String
		{
		public:
			class const_iterator;
			class const_reverse_iterator;

			Utf8String() : mString() {}
			Utf8String(const_iterator first, const_iterator last);
			Utf8String(const String::value_type* str) : mString(str) {}
			Utf8String(const String& rhs) : mString(rhs) {}
			Utf8String(const WString& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }
			Utf8String(String&& rhs) : mString(STD::Move(rhs)) {}
			Utf8String(WString&& rhs) { utf8::utf16to8(rhs.begin(), rhs.end(), std::back_inserter(mString)); }

			bool operator ==(const Utf8String& rhs) const { return mString == rhs.mString; }
			bool operator !=(const Utf8String& rhs) const { return mString != rhs.mString; }

			Utf8String& operator = (const Utf8String& rhs) { mString = rhs.mString; return *this; }

			Utf8String& operator +=(uint32_t c);
			Utf8String& operator +=(const Utf8String& rhs);
			
			const_iterator begin() const;
			const_reverse_iterator rbegin() const;

			uint32_t back() const
			{
				const char* end = mString.data() + mString.length();
				utf8::previous(end, mString.data() - 1);
				uint32_t result[1];
				utf8::utf8to32(end, mString.data() + mString.length(), result);
				return result[0];
			}
			uint32_t front() const
			{
				uint32_t result[1];
				utf8::utf8to32(mString.data(), mString.data() + 1, result);
				return result[0];
			}

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
		class Utf8String::const_iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = uint32_t;
			using difference_type = size_t;
			using pointer = uint32_t*;
			using reference = uint32_t&;

			const_iterator() : mpCurrent(nullptr), mpBegin(nullptr), mpEnd(nullptr) {}
			const_iterator(const const_iterator& rhs) = default;
			const_iterator(const_iterator&& rhs) = default;
			~const_iterator() = default;
			
			const String::value_type* base() const { return mpCurrent; }
			
			const_iterator& operator = (const const_iterator& rhs) = default;
			const_iterator& operator = (const_iterator&& rhs) noexcept { mpCurrent = rhs.mpCurrent; mpBegin = rhs.mpBegin; mpEnd = rhs.mpEnd; return *this; }
			
			bool operator ==(const const_iterator& rhs) const { return mpCurrent == rhs.mpCurrent; }
			bool operator !=(const const_iterator& rhs) const { return mpCurrent != rhs.mpCurrent; }

			bool operator <(const const_iterator& rhs) const { return mpCurrent < rhs.mpCurrent; }
			bool operator >(const const_iterator& rhs) const { return mpCurrent > rhs.mpCurrent; }

			uint32_t operator *() const
			{
				uint32_t result[1];
				utf8::utf8to32(mpCurrent, mpCurrent+1, result);
				return result[0];
			}
			
			const_iterator& operator ++() { utf8::next(mpCurrent, mpEnd); return *this; }
			const_iterator operator++(int) { const_iterator result(*this); utf8::next(mpCurrent, mpEnd); return result; }
			const_iterator& operator --() { utf8::previous(mpCurrent, mpBegin - 1); return *this; }
			const_iterator operator --(int) { const_iterator result(*this); utf8::previous(mpCurrent, mpBegin - 1); return result; }
			
			const_iterator operator -(size_t delta) const
			{
				const_iterator result = *this;
				while (delta != 0)
				{
					utf8::previous(result.mpCurrent, result.mpBegin - 1);
					--delta;
				}
				return result;
			}
			const_iterator operator +(size_t delta) const
			{
				const_iterator result = *this;
				utf8::advance(result.mpCurrent, delta, result.mpEnd);
				return result;
			}
			
		protected:
			friend class Utf8String;
			
			const_iterator(const String::value_type* it, const String::value_type* start, const String::value_type* end)
				: mpCurrent(it)
				, mpBegin(start)
				, mpEnd(end)
			{
			}
			
			const String::value_type* mpCurrent;
			const String::value_type* mpBegin;
			const String::value_type* mpEnd;
		};

		//////////////////////////////////////////////////////////////////////////
		class Utf8String::const_reverse_iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = uint32_t;
			using difference_type = size_t;
			using pointer = uint32_t*;
			using reference = uint32_t&;

			const_reverse_iterator() : mpCurrent(nullptr), mpBegin(nullptr), mpEnd(nullptr) {}
			const_reverse_iterator(const const_reverse_iterator& rhs) = default;
			const_reverse_iterator(const_reverse_iterator&& rhs) = default;
			~const_reverse_iterator() = default;

			const_iterator base() const { return { mpCurrent, mpEnd, mpBegin }; }

			const_reverse_iterator& operator = (const const_reverse_iterator& rhs) = default;
			const_reverse_iterator& operator = (const_reverse_iterator&& rhs) noexcept { mpCurrent = rhs.mpCurrent; mpBegin = rhs.mpBegin; mpEnd = rhs.mpEnd; return *this; }

			bool operator ==(const const_reverse_iterator& rhs) const { return mpCurrent == rhs.mpCurrent; }
			bool operator !=(const const_reverse_iterator& rhs) const { return mpCurrent != rhs.mpCurrent; }

			bool operator <(const const_reverse_iterator& rhs) const { return mpCurrent > rhs.mpCurrent; }
			bool operator >(const const_reverse_iterator& rhs) const { return mpCurrent < rhs.mpCurrent; }

			uint32_t operator *() const
			{
				uint32_t result[1];
				utf8::utf8to32(mpCurrent, mpCurrent + 1, result);
				return result[0];
			}

			const_reverse_iterator& operator ++() { if (mpCurrent - 1 != mpEnd) utf8::previous(mpCurrent, mpEnd); else mpCurrent = mpEnd; return *this; }
			const_reverse_iterator operator++(int) { const_reverse_iterator result(*this); ++(*this); return result; }
			const_reverse_iterator& operator --() { if (mpCurrent != mpEnd) utf8::next(mpCurrent, mpBegin - 1); else mpCurrent = mpCurrent + 1; return *this; }
			const_reverse_iterator operator --(int) { const_reverse_iterator result(*this); --(*this); return result; }

			const_reverse_iterator operator +(size_t delta) const
			{
				const_reverse_iterator result = *this;
				while(delta--)
					utf8::previous(result.mpCurrent, result.mpBegin - 1);
				return result;
			}

		protected:
			friend class Utf8String;

			const_reverse_iterator(const String::value_type* it, const String::value_type* start, const String::value_type* end)
				: mpCurrent(it)
				, mpBegin(start)
				, mpEnd(end)
			{
			}

			const String::value_type* mpCurrent;
			const String::value_type* mpBegin;
			const String::value_type* mpEnd;
		};

		//////////////////////////////////////////////////////////////////////////
		inline Utf8String::Utf8String(Utf8String::const_iterator first, Utf8String::const_iterator last)
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
			return const_reverse_iterator{
				mString.data() + mString.length() - 1,
				mString.data() + mString.length() - 1,
				mString.data() - 1
			};
		}

		inline Utf8String::const_reverse_iterator Utf8String::rend() const
		{
			return const_reverse_iterator{
				mString.data() - 1,
				mString.data() + mString.length() - 1,
				mString.data() - 1
			};
		}

		inline Utf8String& Utf8String::operator +=(uint32_t c)
		{
			uint8_t composeBuffer[1];
			const auto endBuffer = utf8::append(c, composeBuffer);
			mString.append(composeBuffer, endBuffer);
			return *this;
		}

		inline Utf8String& Utf8String::operator +=(const Utf8String& rhs)
		{
			mString = mString + rhs.mString;
			return *this;
		}
		
		inline Utf8String operator +(const Utf8String& lhs, uint32_t c)
		{
			uint8_t composeBuffer[1];
			const auto endBuffer = utf8::append(c, composeBuffer);
			Utf8String result = lhs;
			result.data().append(composeBuffer, endBuffer);
			return result;
		}
		
		inline Utf8String operator +(const Utf8String& lhs, const Utf8String& rhs)
		{
			Utf8String result = lhs;
			result.data() += rhs.data();
			return result;
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

		inline size_t Utf8String::size() const
		{
			return mString.size();
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
