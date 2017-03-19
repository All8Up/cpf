//////////////////////////////////////////////////////////////////////////
#pragma once
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"
#include "SIMD/Vector3v.hpp"
#include "SIMD/Vector4v.hpp"

// Test code gen.
TEST(SimdX, IntersectRayBox)
{
	using namespace Cpf;
	using namespace Math;
	using namespace SIMD;

	Vector3v<F32x4_3> rayOrg(0.0f, 0.0f, 0.0f);
	Vector3v<F32x4_3> invDir(0.0f, 0.0f, 1.0f);
	Vector3v<F32x4_3> bbmin(5.0f, 5.0f, 1.0f);
	Vector3v<F32x4_3> bbmax(6.0f, 5.0f, 2.0f);
	float hitT = 0.0f;

	Vector3v<F32x4_3> d0 = (bbmin - rayOrg) * invDir;
	Vector3v<F32x4_3> d1 = (bbmax - rayOrg) * invDir;

	Vector3v<F32x4_3> v0 = Min(d0, d1);
	Vector3v<F32x4_3> v1 = Max(d0, d1);

	float tmin = HMax(v0);
	float tmax = HMin(v1);

	hitT = tmin;
	bool hit = (tmax >= 0) && (tmax >= tmin) && (tmin <= hitT);
	EXPECT_FALSE(hit);
}
