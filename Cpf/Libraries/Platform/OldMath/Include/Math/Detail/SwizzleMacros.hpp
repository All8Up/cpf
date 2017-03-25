//////////////////////////////////////////////////////////////////////////
// NOTE: Don't change to pragma once, this is included with different
// macros defined.
#ifndef CPF_MATH_DETAIL_SWIZZLEMACROS_HPP
#define CPF_MATH_DETAIL_SWIZZLEMACROS_HPP

#ifndef SWIZZLE_PREFIX
#	define SWIZZLE_PREFIX
#endif
#ifndef SWIZZLE_NAME
#	define SWIZZLE_NAME(a) a
#endif

#ifdef SWIZZLE2_XY
#undef SWIZZLE2_XY
#endif
#define SWIZZLE2_XY(TYPE)						\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 0, 0> SWIZZLE_NAME(xx);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 0, 1> SWIZZLE_NAME(xy);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 1, 0> SWIZZLE_NAME(yx);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 1, 1> SWIZZLE_NAME(yy);

#ifdef SWIZZLE2_XYZ
#undef SWIZZLE2_XYZ
#endif
#define SWIZZLE2_XYZ(TYPE)						\
	SWIZZLE2_XY(TYPE)							\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 0, 2> SWIZZLE_NAME(xz);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 1, 2> SWIZZLE_NAME(yz);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 2, 0> SWIZZLE_NAME(zx);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 2, 1> SWIZZLE_NAME(zy);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 2, 2> SWIZZLE_NAME(zz);

#ifdef SWIZZLE2_XYZW
#undef SWIZZLE2_XYZW
#endif
#define SWIZZLE2_XYZW(TYPE)						\
	SWIZZLE2_XYZ(TYPE);							\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 1, 3> SWIZZLE_NAME(yw);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 2, 3> SWIZZLE_NAME(zw);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 0, 3> SWIZZLE_NAME(xw);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 3, 0> SWIZZLE_NAME(wx);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 3, 1> SWIZZLE_NAME(wy);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 3, 2> SWIZZLE_NAME(wz);			\
	SWIZZLE_PREFIX Cpf::Math::Swizzle2<TYPE, 3, 3> SWIZZLE_NAME(ww);

#ifdef SWIZZLE3_XY
#undef SWIZZLE3_XY
#endif
#define SWIZZLE3_XY(TYPE)						\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 0, 0> SWIZZLE_NAME(xxx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 0, 1> SWIZZLE_NAME(xxy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 1, 0> SWIZZLE_NAME(xyx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 1, 1> SWIZZLE_NAME(xyy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 0, 0> SWIZZLE_NAME(yxx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 0, 1> SWIZZLE_NAME(yxy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 1, 0> SWIZZLE_NAME(yyx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 1, 1> SWIZZLE_NAME(yyy);

#ifdef SWIZZLE3_XYZ
#undef SWIZZLE3_XYZ
#endif
#define SWIZZLE3_XYZ(TYPE)						\
	SWIZZLE3_XY(TYPE);							\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 0, 2> SWIZZLE_NAME(xxz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 1, 2> SWIZZLE_NAME(xyz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 2, 0> SWIZZLE_NAME(xzx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 2, 1> SWIZZLE_NAME(xzy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 2, 2> SWIZZLE_NAME(xzz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 0, 2> SWIZZLE_NAME(yxz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 1, 2> SWIZZLE_NAME(yyz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 2, 0> SWIZZLE_NAME(yzx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 2, 1> SWIZZLE_NAME(yzy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 2, 2> SWIZZLE_NAME(yzz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 0, 0> SWIZZLE_NAME(zxx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 0, 1> SWIZZLE_NAME(zxy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 0, 2> SWIZZLE_NAME(zxz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 1, 0> SWIZZLE_NAME(zyx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 1, 1> SWIZZLE_NAME(zyy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 1, 2> SWIZZLE_NAME(zyz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 2, 0> SWIZZLE_NAME(zzx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 2, 1> SWIZZLE_NAME(zzy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 2, 2> SWIZZLE_NAME(zzz);

#ifdef SWIZZLE3_XYZW
#undef SWIZZLE3_XYZW
#endif
#define SWIZZLE3_XYZW(TYPE)						\
	SWIZZLE3_XYZ(TYPE);							\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 0, 3> SWIZZLE_NAME(xxw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 1, 3> SWIZZLE_NAME(xyw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 2, 3> SWIZZLE_NAME(xzw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 3, 0> SWIZZLE_NAME(xwx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 3, 1> SWIZZLE_NAME(xwy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 3, 2> SWIZZLE_NAME(xwz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 0, 3, 3> SWIZZLE_NAME(xww);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 0, 3> SWIZZLE_NAME(yxw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 1, 3> SWIZZLE_NAME(yyw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 2, 3> SWIZZLE_NAME(yzw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 3, 0> SWIZZLE_NAME(ywx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 3, 1> SWIZZLE_NAME(ywy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 3, 2> SWIZZLE_NAME(ywz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 1, 3, 3> SWIZZLE_NAME(yww);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 0, 3> SWIZZLE_NAME(zxw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 1, 3> SWIZZLE_NAME(zyw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 2, 3> SWIZZLE_NAME(zzw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 3, 0> SWIZZLE_NAME(zwx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 3, 1> SWIZZLE_NAME(zwy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 3, 2> SWIZZLE_NAME(zwz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 2, 3, 3> SWIZZLE_NAME(zww);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 0, 0> SWIZZLE_NAME(wxx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 0, 1> SWIZZLE_NAME(wxy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 0, 2> SWIZZLE_NAME(wxz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 0, 3> SWIZZLE_NAME(wxw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 1, 0> SWIZZLE_NAME(wyx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 1, 1> SWIZZLE_NAME(wyy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 1, 2> SWIZZLE_NAME(wyz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 1, 3> SWIZZLE_NAME(wyw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 2, 0> SWIZZLE_NAME(wzx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 2, 1> SWIZZLE_NAME(wzy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 2, 2> SWIZZLE_NAME(wzz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 2, 3> SWIZZLE_NAME(wzw);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 3, 0> SWIZZLE_NAME(wwx);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 3, 1> SWIZZLE_NAME(wwy);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 3, 2> SWIZZLE_NAME(wwz);		\
	SWIZZLE_PREFIX Cpf::Math::Swizzle3<TYPE, 3, 3, 3> SWIZZLE_NAME(www);

#ifdef SWIZZLE4_0
#undef SWIZZLE4_0
#endif
#define SWIZZLE4_0(TYPE, PREDS, P0, P1, P2)				\
	SWIZZLE_PREFIX Cpf::Math::Swizzle4<TYPE, P0, P1, P2, 0> SWIZZLE_NAME(PREDS##x);

#ifdef SWIZZLE4_1
#undef SWIZZLE4_1
#endif
#define SWIZZLE4_1(TYPE, PREDS, P0, P1, P2)				\
	SWIZZLE4_0(TYPE, PREDS, P0, P1, P2);				\
	SWIZZLE_PREFIX Cpf::Math::Swizzle4<TYPE, P0, P1, P2, 1> SWIZZLE_NAME(PREDS##y);

#ifdef SWIZZLE4_2
#undef SWIZZLE4_2
#endif
#define SWIZZLE4_2(TYPE, PREDS, P0, P1, P2)				\
	SWIZZLE4_1(TYPE, PREDS, P0, P1, P2);				\
	SWIZZLE_PREFIX Cpf::Math::Swizzle4<TYPE, P0, P1, P2, 2> SWIZZLE_NAME(PREDS##z);

#ifdef SWIZZLE4_3
#undef SWIZZLE4_3
#endif
#define SWIZZLE4_3(TYPE, PREDS, P0, P1, P2)				\
	SWIZZLE4_2(TYPE, PREDS, P0, P1, P2);				\
	SWIZZLE_PREFIX Cpf::Math::Swizzle4<TYPE, P0, P1, P2, 3> SWIZZLE_NAME(PREDS##w);

#ifdef SWIZZLE4_XY
#undef SWIZZLE4_XY
#endif
#define SWIZZLE4_XY(TYPE)							\
	SWIZZLE4_1(TYPE, xxx, 0, 0, 0);					\
	SWIZZLE4_1(TYPE, xxy, 0, 0, 1);					\
	SWIZZLE4_1(TYPE, xyx, 0, 1, 0);					\
	SWIZZLE4_1(TYPE, xyy, 0, 1, 1);					\
	SWIZZLE4_1(TYPE, yxx, 1, 0, 0);					\
	SWIZZLE4_1(TYPE, yxy, 1, 0, 1);					\
	SWIZZLE4_1(TYPE, yyx, 1, 1, 0);					\
	SWIZZLE4_1(TYPE, yyy, 1, 1, 1);					\

#ifdef SWIZZLE4_XYZ
#undef SWIZZLE4_XYZ
#endif
#define SWIZZLE4_XYZ(TYPE)							\
	SWIZZLE4_XY(TYPE);								\
	SWIZZLE4_2(TYPE, xxz, 0, 0, 2);					\
	SWIZZLE4_2(TYPE, xzx, 0, 2, 0);					\
	SWIZZLE4_2(TYPE, xzy, 0, 2, 1);					\
	SWIZZLE4_2(TYPE, xzz, 0, 2, 2);					\
	SWIZZLE4_2(TYPE, zxx, 2, 0, 0);					\
	SWIZZLE4_2(TYPE, zxy, 2, 0, 1);					\
	SWIZZLE4_2(TYPE, zxz, 2, 0, 2);					\
	SWIZZLE4_2(TYPE, zyx, 2, 1, 0);					\
	SWIZZLE4_2(TYPE, zyy, 2, 1, 1);					\
	SWIZZLE4_2(TYPE, zyz, 2, 1, 2);					\
	SWIZZLE4_2(TYPE, zzx, 2, 2, 0);					\
	SWIZZLE4_2(TYPE, zzy, 2, 2, 1);					\
	SWIZZLE4_2(TYPE, zzz, 2, 2, 2);					\

#ifdef SWIZZLE4_XYZW
#undef SWIZZLE4_XYZW
#endif
#define SWIZZLE4_XYZW(TYPE)							\
	SWIZZLE4_XYZ(TYPE);								\
	SWIZZLE4_3(TYPE, xxw, 0, 0, 3);					\
	SWIZZLE4_3(TYPE, xwx, 0, 3, 0);					\
	SWIZZLE4_3(TYPE, xwy, 0, 3, 1);					\
	SWIZZLE4_3(TYPE, xwz, 0, 3, 2);					\
	SWIZZLE4_3(TYPE, xww, 0, 3, 3);					\
	SWIZZLE4_3(TYPE, ywx, 1, 3, 0);					\
	SWIZZLE4_3(TYPE, ywy, 1, 3, 1);					\
	SWIZZLE4_3(TYPE, ywz, 1, 3, 2);					\
	SWIZZLE4_3(TYPE, yww, 1, 3, 3);					\
	SWIZZLE4_3(TYPE, zwx, 2, 3, 0);					\
	SWIZZLE4_3(TYPE, zwy, 2, 3, 1);					\
	SWIZZLE4_3(TYPE, zwz, 2, 3, 2);					\
	SWIZZLE4_3(TYPE, zww, 2, 3, 3);					\
	SWIZZLE4_3(TYPE, wxx, 3, 0, 0);					\
	SWIZZLE4_3(TYPE, wxy, 3, 0, 1);					\
	SWIZZLE4_3(TYPE, wxz, 3, 0, 2);					\
	SWIZZLE4_3(TYPE, wxw, 3, 0, 3);					\
	SWIZZLE4_3(TYPE, wyx, 3, 1, 0);					\
	SWIZZLE4_3(TYPE, wyy, 3, 1, 1);					\
	SWIZZLE4_3(TYPE, wyz, 3, 1, 2);					\
	SWIZZLE4_3(TYPE, wyw, 3, 1, 3);					\
	SWIZZLE4_3(TYPE, wzx, 3, 2, 0);					\
	SWIZZLE4_3(TYPE, wzy, 3, 2, 1);					\
	SWIZZLE4_3(TYPE, wzz, 3, 2, 2);					\
	SWIZZLE4_3(TYPE, wzw, 3, 2, 3);					\
	SWIZZLE4_3(TYPE, wwx, 3, 3, 0);					\
	SWIZZLE4_3(TYPE, wwy, 3, 3, 1);					\
	SWIZZLE4_3(TYPE, wwz, 3, 3, 2);					\
	SWIZZLE4_3(TYPE, www, 3, 3, 3);


#endif // CPF_MATH_DETAIL_SWIZZLEMACROS_HPP
