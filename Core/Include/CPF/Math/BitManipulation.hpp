//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math.hpp"

namespace CPF
{
	namespace Math
	{
		inline uint32_t SplitByOne32(uint32_t v)
		{
			uint32_t r = v;
			r = (r | r << 16) & 0x0000FFFF;
			r = (r | r << 8) & 0x00FF00FF;
			r = (r | r << 4) & 0x0F0F0F0F;
			r = (r | r << 2) & 0x33333333;
			r = (r | r << 1) & 0x55555555;
			return r;
		}

		inline uint64_t SplitByOne64(uint32_t v)
		{
			uint64_t r = v;
			r = (r | r << 16) & 0x0000FFFF0000FFFF;
			r = (r | r << 8) & 0x00FF00FF00FF00FF;
			r = (r | r << 4) & 0x0F0F0F0F0F0F0F0F;
			r = (r | r << 2) & 0x3333333333333333;
			r = (r | r << 1) & 0x5555555555555555;
			return r;
		}

		inline uint32_t SplitByTwo32(uint32_t v)
		{
			uint32_t r = v;
			r = r & 0x000003ff;
			r = (r | r << 16) & 0x30000ff;
			r = (r | r << 8) & 0x0300f00f;
			r = (r | r << 4) & 0x30c30c3;
			r = (r | r << 2) & 0x9249249;
			return r;
		}

		inline uint64_t SplitByTwo64(uint32_t v)
		{
			uint64_t x = v & 0x1fffff;
			x = (x | x << 32) & 0x1f00000000ffff;
			x = (x | x << 16) & 0x1f0000ff0000ff;
			x = (x | x << 8) & 0x100f00f00f00f00f;
			x = (x | x << 4) & 0x10c30c30c30c30c3;
			x = (x | x << 2) & 0x1249249249249249;
			return x;
		}

		//////////////////////////////////////////////////////////////////////////

		inline uint32_t ExtractEverySecondBit(uint32_t v)
		{
			uint32_t r = v & 0x55555555;
			r = (r | (r >> 1)) & 0x33333333;
			r = (r | (r >> 2)) & 0x0F0F0F0F;
			r = (r | (r >> 4)) & 0x00FF00FF;
			r = (r | (r >> 8)) & 0x0000FFFF;
			return r;
		}

		inline uint32_t ExtractEverySecondBit(uint64_t v)
		{
			uint64_t r = v & 0x5555555555555555;
			r = (r | (r >> 1)) & 0x3333333333333333;
			r = (r | (r >> 2)) & 0x0F0F0F0F0F0F0F0F;
			r = (r | (r >> 4)) & 0x00FF00FF00FF00FF;
			r = (r | (r >> 8)) & 0x0000FFFF0000FFFF;
			r = (r | (r >> 16)) & 0x00000000FFFFFFFF;
			return uint32_t(r);
		}

		inline uint32_t ExtractEveryThirdBit(uint32_t v)
		{
			uint32_t r = v & 0x9249249;
			r = (r ^ (r >> 2)) & 0x30c30c3;
			r = (r ^ (r >> 4)) & 0x0300f00f;
			r = (r ^ (r >> 8)) & 0x30000ff;
			r = (r ^ (r >> 16)) & 0x000003ff;
			return r;
		}

		inline uint32_t ExtractEveryThirdBit(uint64_t v)
		{
			uint64_t r = v & 0x1249249249249249;
			r = (r ^ (r >> 2)) & 0x10c30c30c30c30c3;
			r = (r ^ (r >> 4)) & 0x100f00f00f00f00f;
			r = (r ^ (r >> 8)) & 0x1f0000ff0000ff;
			r = (r ^ (r >> 16)) & 0xffff00000000ffff;
			r = (r ^ (r >> 32)) & 0x1fffff;
			return uint32_t(r);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename TYPE>
		bool IsPow2(TYPE v)
		{
			return !(v & (v - 1)) && v;
		}

		inline uint32_t NextPower2(uint32_t v)
		{
			uint32_t value = v;
			value |= value >> 16;
			value |= value >> 8;
			value |= value >> 4;
			value |= value >> 2;
			value |= value >> 1;
			return value + 1;
		}

		inline uint32_t PreviousPower2(uint32_t v)
		{
			uint32_t value = v - 1;
			value |= value >> 16;
			value |= value >> 8;
			value |= value >> 4;
			value |= value >> 2;
			value |= value >> 1;
			return((value + 1) >> 1);
		}

		inline uint32_t ReverseBits(uint32_t v)
		{
			uint32_t result = (((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1));
			result = (((result >> 2) & 0x33333333) | ((result & 0x33333333) << 2));
			result = (((result >> 4) & 0x0F0F0F0F) | ((result & 0x0F0F0F0F) << 4));
			result = (((result >> 8) & 0x00FF00FF) | ((result & 0x00FF00FF) << 8));
			result = (((result >> 16) & 0x0000FFFF) | ((result & 0x0000FFFF) << 16));
			return result;
		}

		inline uint64_t ReverseBits(uint64_t v)
		{
			uint64_t result = (((v >> 1) & 0x5555555555555555ull) | ((v & 0x5555555555555555ull) << 1));
			result = (((result >> 2) & 0x3333333333333333ull) | ((result & 0x3333333333333333ull) << 2));
			result = (((result >> 4) & 0x0F0F0F0F0F0F0F0Full) | ((result & 0x0F0F0F0F0F0F0F0Full) << 4));
			result = (((result >> 8) & 0x00FF00FF00FF00FFull) | ((result & 0x00FF00FF00FF00FFull) << 8));
			result = (((result >> 16) & 0x0000FFFF0000FFFFull) | ((result & 0x0000FFFF0000FFFFull) << 16));
			return ((result >> 32) | (result << 32));
		}

		inline uint32_t CountOnBits(uint32_t v)
		{
			uint32_t result = (v & 0x55555555) + ((v & 0xaaaaaaaa) >> 1);
			result = (result & 0x33333333) + ((result & 0xcccccccc) >> 2);
			result = (result & 0x0f0f0f0f) + ((result & 0xf0f0f0f0) >> 4);
			result = (result & 0x00ff00ff) + ((result & 0xff00ff00) >> 8);
			return((result & 0x0000ffff) + ((result & 0xffff0000) >> 16));
		}

		inline uint64_t CountOnBits(uint64_t v)
		{
			const uint32_t*	values = reinterpret_cast<const uint32_t*>(&v);
			return(CountOnBits(values[0]) + CountOnBits(values[1]));
		}

		template <typename TYPE>
		TYPE BitIndexToValue(TYPE index)
		{
			return 1 << index;
		}

		inline uint32_t BitValueToIndex(uint32_t value)
		{
			static const uint32_t	MultiplyDeBruijnBitPosition2[32] =
			{
				0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
				31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
			};
			return MultiplyDeBruijnBitPosition2[(value * 0x077CB531) >> 27];
		}

		template <typename TYPE>
		TYPE GetLSBValue(TYPE v)
		{
			return v == 0 ? 0 : (v & (~v - 1));
		}

		template <typename TYPE>
		TYPE GetLSBIndex(TYPE v)
		{
			return v == 0 ? 0 : BitValueToIndex(GetLSBValue(v));
		}

		template <typename TYPE>
		TYPE GetMSBValue(TYPE v)
		{
			if (v == 0)
				return 0;
			v |= (v >> 1);
			v |= (v >> 2);
			v |= (v >> 4);
			v |= (v >> 8);
			v |= (v >> 16);
			return(v & ~(v >> 1));
		}

		template <typename TYPE>
		TYPE GetMSBIndex(TYPE v)
		{
			return BitValueToIndex(GetMSBValue(v));
		}

		template <typename TYPE>
		TYPE ExtractBits(TYPE v, int lowIdx, int highIdx)
		{
			TYPE range = (highIdx - lowIdx) + 1;
			TYPE mask = ((1 << range) - 1) << lowIdx;
			return (v&mask) >> lowIdx;
		}

		template <typename TYPE>
		TYPE SetBits(TYPE initial, TYPE bits, int lowIdx, int highIdx)
		{
			TYPE range = (highIdx - lowIdx) + 1;
			TYPE mask = ((1 << range) - 1) << lowIdx;
			return (initial&~mask) | (bits << lowIdx);
		}

		template <typename TYPE, unsigned BITS>
		TYPE SignExtend(const TYPE x)
		{
			struct { TYPE x : BITS; } s;
			return s.x = x;
		}

		template <typename TYPE>
		bool IsEven(TYPE v)
		{
			return (v & 1) == 0;
		}

		template <typename TYPE>
		bool IsOdd(TYPE v)
		{
			return (v & 1) == 1;
		}

		template <typename TYPE>
		bool IsBitSet(TYPE v, int bitIndex)
		{
			return (v & (1 << bitIndex)) != 0;
		}

		template <typename TYPE>
		bool IsBitClear(TYPE v, int bitIndex)
		{
			return (v & (1 << bitIndex)) == 0;
		}

		template <typename TYPE>
		TYPE SetBit(TYPE v, int bitIndex)
		{
			return v | (1 << bitIndex);
		}

		template <typename TYPE>
		TYPE ClearBit(TYPE v, int bitIndex)
		{
			return v & ~(1 << bitIndex);
		}

		template <typename TYPE>
		TYPE ToggleBit(TYPE v, int bitIndex)
		{
			return v ^ (1 << bitIndex);
		}

		template <typename TYPE>
		TYPE ClearLSB(TYPE v)
		{
			return v & (v - 1);
		}

		template <typename TYPE>
		TYPE GetLSB(TYPE v)
		{
			return v & (-v);
		}

		template <typename TYPE>
		TYPE ExtendLSB(TYPE v)
		{
			return v | (v - 1);
		}

		template <typename TYPE>
		TYPE LowestZeroBit(TYPE v)
		{
			return ~v & (v + 1);
		}

		template <typename TYPE>
		TYPE SetLowestZeroBit(TYPE v)
		{
			return v | (v + 1);
		}
	}
}
