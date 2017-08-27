//////////////////////////////////////////////////////////////////////////
#pragma once


#define LANEREF_1_SWIZZLE(t)		\
	Cpf::SIMD::LaneRef_1<t, 0> x;	\
	Cpf::SIMD::LaneRef_1<t, 1> y;	\
	Cpf::SIMD::LaneRef_1<t, 2> z;	\
	Cpf::SIMD::LaneRef_1<t, 3> w;

//
#define LANEREF_2_SWIZZLE_(t, s, v)		\
	Cpf::SIMD::LaneRef_2<t, s, 0> v##x;	\
	Cpf::SIMD::LaneRef_2<t, s, 1> v##y;	\
	Cpf::SIMD::LaneRef_2<t, s, 2> v##z;	\
	Cpf::SIMD::LaneRef_2<t, s, 3> v##w

#define LANEREF_2_SWIZZLE(type)		\
	LANEREF_2_SWIZZLE_(type, 0, x);	\
	LANEREF_2_SWIZZLE_(type, 1, y);	\
	LANEREF_2_SWIZZLE_(type, 2, z);	\
	LANEREF_2_SWIZZLE_(type, 3, w);

//
#define LANEREF_3_SWIZZLE_3(t, a, an, b, bn)	\
	Cpf::SIMD::LaneRef_3<t, a, b, 0> an##bn##x;	\
	Cpf::SIMD::LaneRef_3<t, a, b, 1> an##bn##y;	\
	Cpf::SIMD::LaneRef_3<t, a, b, 2> an##bn##z;	\
	Cpf::SIMD::LaneRef_3<t, a, b, 3> an##bn##w;

#define LANEREF_3_SWIZZLE_2(t, a, an)	\
	LANEREF_3_SWIZZLE_3(t, a, an, 0, x)	\
	LANEREF_3_SWIZZLE_3(t, a, an, 1, y)	\
	LANEREF_3_SWIZZLE_3(t, a, an, 2, z)	\
	LANEREF_3_SWIZZLE_3(t, a, an, 3, w)

#define LANEREF_3_SWIZZLE(t)		\
	LANEREF_3_SWIZZLE_2(t, 0, x)	\
	LANEREF_3_SWIZZLE_2(t, 1, y)	\
	LANEREF_3_SWIZZLE_2(t, 2, z)	\
	LANEREF_3_SWIZZLE_2(t, 3, w)

//
#define LANEREF_4_SWIZZLE_4(t, a, an, b, bn, c, cn)		\
	Cpf::SIMD::LaneRef_4<t, a, b, c, 0> an##bn##cn##x;	\
	Cpf::SIMD::LaneRef_4<t, a, b, c, 1> an##bn##cn##y;	\
	Cpf::SIMD::LaneRef_4<t, a, b, c, 2> an##bn##cn##z;	\
	Cpf::SIMD::LaneRef_4<t, a, b, c, 3> an##bn##cn##w;

#define LANEREF_4_SWIZZLE_3(t, a, an, b, bn)	\
	LANEREF_4_SWIZZLE_4(t, a, an, b, bn, 0, x)	\
	LANEREF_4_SWIZZLE_4(t, a, an, b, bn, 1, y)	\
	LANEREF_4_SWIZZLE_4(t, a, an, b, bn, 2, z)	\
	LANEREF_4_SWIZZLE_4(t, a, an, b, bn, 3, w)

#define LANEREF_4_SWIZZLE_2(t, a, an)	\
	LANEREF_4_SWIZZLE_3(t, a, an, 0, x)	\
	LANEREF_4_SWIZZLE_3(t, a, an, 1, y)	\
	LANEREF_4_SWIZZLE_3(t, a, an, 2, z)	\
	LANEREF_4_SWIZZLE_3(t, a, an, 3, w)

#define LANEREF_4_SWIZZLE(t)		\
	LANEREF_4_SWIZZLE_2(t, 0, x)	\
	LANEREF_4_SWIZZLE_2(t, 1, y)	\
	LANEREF_4_SWIZZLE_2(t, 2, z)	\
	LANEREF_4_SWIZZLE_2(t, 3, w)
