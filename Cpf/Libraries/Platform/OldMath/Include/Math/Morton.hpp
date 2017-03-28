//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Bits.hpp"

namespace Cpf
{
	namespace Math
	{
		using Morton32 = uint32_t;
		using Morton64 = uint64_t;

		Morton32 Morton32Encode(int32_t x, int32_t y);
		Morton32 Morton32Encode(int32_t x, int32_t y, int32_t z);
		Morton64 Morton64Encode(int32_t x, int32_t y);
		Morton64 Morton64Encode(int32_t x, int32_t y, int32_t z);

		void MortonDecode(const Morton32 v, int32_t& x, int32_t& y);
		void MortonDecode(const Morton32 v, int32_t& x, int32_t& y, int32_t& z);
		void MortonDecode(const Morton64 v, int32_t& x, int32_t& y);
		void MortonDecode(const Morton64 v, int32_t& x, int32_t& y, int32_t& z);


		inline Morton32 Morton32Encode(int32_t x, int32_t y)
		{
			Morton32 result = SplitByOne32(uint32_t(x));
			result |= SplitByOne32(uint32_t(y)) << 1;
			return result;
		}

		inline Morton32 Morton32Encode(int32_t x, int32_t y, int32_t z)
		{
			Morton32 result = SplitByTwo32(uint32_t(x));
			result |= SplitByTwo32(uint32_t(y)) << 1;
			result |= SplitByTwo32(uint32_t(z)) << 2;
			return result;
		}

		inline Morton64 Morton64Encode(int32_t x, int32_t y)
		{
			Morton64 result = SplitByOne64(uint32_t(x));
			result |= SplitByOne64(uint32_t(y)) << 1;
			return result;
		}

		inline Morton64 Morton64Encode(int32_t x, int32_t y, int32_t z)
		{
			Morton64 result = SplitByTwo64(uint32_t(x));
			result |= SplitByTwo64(uint32_t(y)) << 1;
			result |= SplitByTwo64(uint32_t(z)) << 2;
			return result;
		}

		template<typename TYPE>
		Morton32 Morton32Encode(const Vector2<TYPE>& v) { return Morton32Encode(v.x, v.y); }
		template<typename TYPE>
		Morton64 Morton64Encode(const Vector2<TYPE>& v) { return Morton64Encode(v.x, v.y); }
		template<typename TYPE>
		Morton32 Morton32Encode(const Vector3<TYPE>& v) { return Morton32Encode(v.x, v.y, v.z); }
		template<typename TYPE>
		Morton64 Morton64Encode(const Vector3<TYPE>& v) { return Morton64Encode(v.x, v.y, v.z); }

		//////////////////////////////////////////////////////////////////////////
		inline void MortonDecode(const Morton32 v, int32_t& x, int32_t& y)
		{
			x = SignExtend<int32_t, 16>(ExtractEverySecondBit(v));
			y = SignExtend<int32_t, 16>(ExtractEverySecondBit(v >> 1));
		}

		inline void MortonDecode(const Morton32 v, int32_t& x, int32_t& y, int32_t& z)
		{
			x = SignExtend<int32_t, 10>(ExtractEveryThirdBit(v));
			y = SignExtend<int32_t, 10>(ExtractEveryThirdBit(v >> 1));
			z = SignExtend<int32_t, 10>(ExtractEveryThirdBit(v >> 2));
		}

		inline void MortonDecode(const Morton64 v, int32_t& x, int32_t& y)
		{
			x = SignExtend<int32_t, 32>(ExtractEverySecondBit(v));
			y = SignExtend<int32_t, 32>(ExtractEverySecondBit(v >> 1));
		}

		inline void MortonDecode(const Morton64 v, int32_t& x, int32_t& y, int32_t& z)
		{
			x = SignExtend<int32_t, 21>(ExtractEveryThirdBit(v));
			y = SignExtend<int32_t, 21>(ExtractEveryThirdBit(v >> 1));
			z = SignExtend<int32_t, 21>(ExtractEveryThirdBit(v >> 2));
		}

		template<typename TYPE>
		void MortonDecode(const Morton32 v, Vector2<TYPE>& o) { MortonDecode(v, o.x, o.y); }
		template<typename TYPE>
		void MortonDecode(const Morton64 v, Vector2<TYPE>& o) { MortonDecode(v, o.x, o.y); }
		template<typename TYPE>
		void MortonDecode(const Morton32 v, Vector3<TYPE>& o) { MortonDecode(v, o.x, o.y, o.z); }
		template<typename TYPE>
		void MortonDecode(const Morton64 v, Vector3<TYPE>& o) { MortonDecode(v, o.x, o.y, o.z); }
	}
}
