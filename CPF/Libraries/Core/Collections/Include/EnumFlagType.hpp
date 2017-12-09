//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	template <size_t SIZE>
	struct _SizedUInt;

	template <>
	struct _SizedUInt<1> { using Type = uint8_t; };
	template <>
	struct _SizedUInt<2> { using Type = uint16_t; };
	template <>
	struct _SizedUInt<4> { using Type = uint32_t; };
	template <>
	struct _SizedUInt<8> { using Type = uint64_t; };

	template <typename TYPE>
	struct SizedUInt
	{
		using Type = typename _SizedUInt<sizeof(TYPE)>::Type;
	};
}

#define CPF_ENUM_FLAG_TYPE(type) \
inline constexpr type operator | (type lhs, type rhs) { return type(((CPF::SizedUInt<type>::Type)lhs) | ((CPF::SizedUInt<type>::Type)rhs)); } \
inline type& operator |= (type& lhs, type rhs) { lhs = (lhs | rhs); return lhs; } \
inline constexpr type operator & (type lhs, type rhs) { return type(((CPF::SizedUInt<type>::Type)lhs) & ((CPF::SizedUInt<type>::Type)rhs)); } \
inline type& operator &= (type& lhs, type rhs) { lhs = (lhs & rhs); return lhs; } \
inline constexpr type operator ~ (type lhs) { return type(~(CPF::SizedUInt<type>::Type)lhs); } \
inline constexpr type operator ^ (type lhs, type rhs) { return type(((CPF::SizedUInt<type>::Type)lhs) ^ ((CPF::SizedUInt<type>::Type)rhs)); } \
inline type& operator ^= (type& lhs, type rhs) { lhs = (lhs ^ rhs); return lhs; } \
inline bool IsSet(const type& lhs, const type& rhs) { return (lhs & rhs) != type(0); } \
inline bool IsClear(const type& lhs, const type& rhs) { return (lhs & rhs) == type(0); }
