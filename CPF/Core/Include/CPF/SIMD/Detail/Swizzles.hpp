//////////////////////////////////////////////////////////////////////////
#pragma once

// Single lane result types on dual lane data.
#define REFx1_TYPEx2(t, a, b)					\
	CPF::SIMD::LaneRef_1<t, 0> a;				\
	CPF::SIMD::LaneRef_1<t, 1> b;

// Single lane result types on tri lane data.
#define REFx1_TYPEx3(t, a, b, c)				\
	REFx1_TYPEx2(t, a, b)						\
	CPF::SIMD::LaneRef_1<t, 2> c;

// Single lane result types on quad lane data.
#define REFx1_TYPEx4(t, a, b, c, d)				\
	REFx1_TYPEx3(t, a, b, c)					\
	CPF::SIMD::LaneRef_1<t, 3> d;

// Dual lane result types on dual lane data.
#define REFx2_TYPEx2_(t, l, ln, a, b)			\
	CPF::SIMD::LaneRef_2<t, l, 0> ln##a;		\
	CPF::SIMD::LaneRef_2<t, l, 1> ln##b;

#define REFx2_TYPEx2(t, a, b)					\
	REFx2_TYPEx2_(t, 0, a, a, b)				\
	REFx2_TYPEx2_(t, 1, b, a, b)


// Dual lane result types on tri lane data.
#define REFx2_TYPEx3_(t, l, ln, a, b, c)		\
	REFx2_TYPEx2_(t, l, ln, a, b)				\
	CPF::SIMD::LaneRef_2<t, l, 2> ln##c;

#define REFx2_TYPEx3(t, a, b, c)				\
	REFx2_TYPEx3_(t, 0, a, a, b, c)				\
	REFx2_TYPEx3_(t, 1, b, a, b, c)				\
	REFx2_TYPEx3_(t, 2, c, a, b, c)

//
#define LANEREF_2_SWIZZLE_(t, s, v)		\
	CPF::SIMD::LaneRef_2<t, s, 0> v##x;	\
	CPF::SIMD::LaneRef_2<t, s, 1> v##y;	\
	CPF::SIMD::LaneRef_2<t, s, 2> v##z;	\
	CPF::SIMD::LaneRef_2<t, s, 3> v##w

#define LANEREF_2_SWIZZLE(type)		\
	LANEREF_2_SWIZZLE_(type, 0, x);	\
	LANEREF_2_SWIZZLE_(type, 1, y);	\
	LANEREF_2_SWIZZLE_(type, 2, z);	\
	LANEREF_2_SWIZZLE_(type, 3, w);

//
#define LANEREF_3_SWIZZLE_3(t, a, an, b, bn)	\
	CPF::SIMD::LaneRef_3<t, a, b, 0> an##bn##x;	\
	CPF::SIMD::LaneRef_3<t, a, b, 1> an##bn##y;	\
	CPF::SIMD::LaneRef_3<t, a, b, 2> an##bn##z;	\
	CPF::SIMD::LaneRef_3<t, a, b, 3> an##bn##w;

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
	CPF::SIMD::LaneRef_4<t, a, b, c, 0> an##bn##cn##x;	\
	CPF::SIMD::LaneRef_4<t, a, b, c, 1> an##bn##cn##y;	\
	CPF::SIMD::LaneRef_4<t, a, b, c, 2> an##bn##cn##z;	\
	CPF::SIMD::LaneRef_4<t, a, b, c, 3> an##bn##cn##w;

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
