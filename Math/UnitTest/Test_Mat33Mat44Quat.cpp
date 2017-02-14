//////////////////////////////////////////////////////////////////////////
#include "Math/Matrix33v.hpp"
#include "Math/Matrix44v.hpp"
#include "Math/Quaternionv.hpp"
#include "Math/Constants.hpp"
#include <gtest/gtest.h>

using namespace Cpf;
using namespace Math;

bool ExpectNear(const Matrix33fv& lhs, const Matrix33fv& rhs)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float diff = fabs(lhs[i][j] - rhs[i][j]);
			if (diff > 0.01f)
				return false;
		}
	}
	return true;
}

bool ExpectNear(const Matrix33fv& lhs, const Matrix44fv& rhs)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float diff = fabs(lhs[i][j] - rhs[i][j]);
			if (diff > 0.01f)
				return false;
		}
	}
	return true;
}

TEST(Math, Mat33ToQuat)
{
	Matrix33fv identity(Vector3fv::XAxis(), Vector3fv::YAxis(), Vector3fv::ZAxis());
	Quaternionfv qi(identity);
	EXPECT_NEAR(qi.x, 0.0f, 0.01f);
	EXPECT_NEAR(qi.y, 0.0f, 0.01f);
	EXPECT_NEAR(qi.z, 0.0f, 0.01f);
	EXPECT_NEAR(qi.w, 1.0f, 0.01f);
}

TEST(Math, QuatAxisAngleX)
{
	//////////////////////////////////////////////////////////////////////////
	Quaternionfv q = Quaternionfv::AxisAngle(Vector3fv::XAxis(), 90.0f * kDegToRad);
	Matrix33fv ma3 = Matrix33fv::AxisAngle(Vector3fv::XAxis(), 90.0f * kDegToRad);
	Matrix44fv ma4 = Matrix44fv::AxisAngle(Vector3fv::XAxis(), 90.0f * kDegToRad);
	Matrix33fv m3 = Matrix33fv::RotateX(90.0f * kDegToRad);
	Matrix44fv m4 = Matrix44fv::RotateX(90.0f * kDegToRad);
	Matrix33fv mq3(q);
	Matrix44fv mq4(q);

	EXPECT_TRUE(ExpectNear(ma3, ma4));
	EXPECT_TRUE(ExpectNear(m3, m4));
	EXPECT_TRUE(ExpectNear(ma3, m3));
	EXPECT_TRUE(ExpectNear(m3, mq3));
	EXPECT_TRUE(ExpectNear(m3, mq4));

	Vector3fv qrx = Vector3fv::ZAxis() * q;
	EXPECT_NEAR(qrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(qrx.y, -1.0f, 0.1f);
	EXPECT_NEAR(qrx.z, 0.0f, 0.1f);

	Vector3fv mrx = Vector3fv::ZAxis() * ma3;
	EXPECT_NEAR(mrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mrx.y, -1.0f, 0.1f);
	EXPECT_NEAR(mrx.z, 0.0f, 0.1f);

	Vector3fv mxrx = Vector3fv::ZAxis() * m3;
	EXPECT_NEAR(mxrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mxrx.y, -1.0f, 0.1f);
	EXPECT_NEAR(mxrx.z, 0.0f, 0.1f);

	Vector3fv mqrx = Vector3fv::ZAxis() * mq3;
	EXPECT_NEAR(mqrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mqrx.y, -1.0f, 0.1f);
	EXPECT_NEAR(mqrx.z, 0.0f, 0.1f);

	Vector4fv mx4v = Vector4fv::ZAxis() * m4;
	EXPECT_NEAR(mx4v.x, 0.0f, 0.1f);
	EXPECT_NEAR(mx4v.y, -1.0f, 0.1f);
	EXPECT_NEAR(mx4v.z, 0.0f, 0.1f);
}

TEST(Math, QuatAxisAngleY)
{
	//////////////////////////////////////////////////////////////////////////
	Quaternionfv q = Quaternionfv::AxisAngle(Vector3fv::YAxis(), 90.0f * kDegToRad);
	Matrix33fv ma3 = Matrix33fv::AxisAngle(Vector3fv::YAxis(), 90.0f * kDegToRad);
	Matrix44fv ma4 = Matrix44fv::AxisAngle(Vector3fv::YAxis(), 90.0f * kDegToRad);
	Matrix33fv m3 = Matrix33fv::RotateY(90.0f * kDegToRad);
	Matrix44fv m4 = Matrix44fv::RotateY(90.0f * kDegToRad);
	Matrix33fv mq3(q);
	Matrix44fv mq4(q);

	EXPECT_TRUE(ExpectNear(ma3, ma4));
	EXPECT_TRUE(ExpectNear(m3, m4));
	EXPECT_TRUE(ExpectNear(ma3, m3));
	EXPECT_TRUE(ExpectNear(m3, mq3));
	EXPECT_TRUE(ExpectNear(m3, mq4));

	Vector3fv qrx = Vector3fv::XAxis() * q;
	EXPECT_NEAR(qrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(qrx.y, 0.0f, 0.1f);
	EXPECT_NEAR(qrx.z, -1.0f, 0.1f);

	Vector3fv mrx = Vector3fv::XAxis() * ma3;
	EXPECT_NEAR(mrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mrx.y, 0.0f, 0.1f);
	EXPECT_NEAR(mrx.z, -1.0f, 0.1f);

	Vector3fv mxrx = Vector3fv::XAxis() * m3;
	EXPECT_NEAR(mxrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mxrx.y, 0.0f, 0.1f);
	EXPECT_NEAR(mxrx.z, -1.0f, 0.1f);

	Vector3fv mqrx = Vector3fv::XAxis() * mq3;
	EXPECT_NEAR(mqrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mqrx.y, 0.0f, 0.1f);
	EXPECT_NEAR(mqrx.z, -1.0f, 0.1f);

	Vector4fv mx4v = Vector4fv::XAxis() * m4;
	EXPECT_NEAR(mx4v.x, 0.0f, 0.1f);
	EXPECT_NEAR(mx4v.y, 0.0f, 0.1f);
	EXPECT_NEAR(mx4v.z, -1.0f, 0.1f);
}

TEST(Math, QuatAxisAngleZ)
{
	//////////////////////////////////////////////////////////////////////////
	Quaternionfv q = Quaternionfv::AxisAngle(Vector3fv::ZAxis(), 90.0f * kDegToRad);
	Matrix33fv ma3 = Matrix33fv::AxisAngle(Vector3fv::ZAxis(), 90.0f * kDegToRad);
	Matrix44fv ma4 = Matrix44fv::AxisAngle(Vector3fv::ZAxis(), 90.0f * kDegToRad);
	Matrix33fv m3 = Matrix33fv::RotateZ(90.0f * kDegToRad);
	Matrix44fv m4 = Matrix44fv::RotateZ(90.0f * kDegToRad);
	Matrix33fv mq3(q);
	Matrix44fv mq4(q);

	EXPECT_TRUE(ExpectNear(ma3, ma4));
	EXPECT_TRUE(ExpectNear(m3, m4));
	EXPECT_TRUE(ExpectNear(ma3, m3));
	EXPECT_TRUE(ExpectNear(m3, mq3));
	EXPECT_TRUE(ExpectNear(m3, mq4));

	Vector3fv qrx = Vector3fv::XAxis() * q;
	EXPECT_NEAR(qrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(qrx.y, 1.0f, 0.1f);
	EXPECT_NEAR(qrx.z, 0.0f, 0.1f);

	Vector3fv mrx = Vector3fv::XAxis() * ma3;
	EXPECT_NEAR(mrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mrx.y, 1.0f, 0.1f);
	EXPECT_NEAR(mrx.z, 0.0f, 0.1f);

	Vector3fv mxrx = Vector3fv::XAxis() * m3;
	EXPECT_NEAR(mxrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mxrx.y, 1.0f, 0.1f);
	EXPECT_NEAR(mxrx.z, 0.0f, 0.1f);

	Vector3fv mqrx = Vector3fv::XAxis() * mq3;
	EXPECT_NEAR(mqrx.x, 0.0f, 0.1f);
	EXPECT_NEAR(mqrx.y, 1.0f, 0.1f);
	EXPECT_NEAR(mqrx.z, 0.0f, 0.1f);

	Vector4fv mx4v = Vector4fv::XAxis() * m4;
	EXPECT_NEAR(mx4v.x, 0.0f, 0.1f);
	EXPECT_NEAR(mx4v.y, 1.0f, 0.1f);
	EXPECT_NEAR(mx4v.z, 0.0f, 0.1f);
}

TEST(Math, Mat33ToQuatToMat33)
{
	Matrix33fv rotateX = Matrix33fv::RotateX(90.0f * kDegToRad);
	Quaternionfv qrx(rotateX);
	Matrix33fv rotX(qrx);
	EXPECT_TRUE(ExpectNear(rotateX, rotX));

	Matrix33fv rotateY = Matrix33fv::RotateY(90.0f * kDegToRad);
	Quaternionfv qry(rotateY);
	Matrix33fv rotY(qry);
	EXPECT_TRUE(ExpectNear(rotateY, rotY));

	Matrix33fv rotateZ = Matrix33fv::RotateZ(90.0f * kDegToRad);
	Quaternionfv qrz(rotateZ);
	Matrix33fv rotZ(qrz);
	EXPECT_TRUE(ExpectNear(rotateZ, rotZ));
}

TEST(Math, AxisAngleRotations)
{
	for (int z = 0; z < 360; z+=10)
	{
		float za = z * kDegToRad;
		Vector3fv zv(sin(za), cos(za), 0.0f);
		for (int p = 0; p < 360; p+=10)
		{
			float pa = p * kDegToRad;
			Vector3fv v = zv * sin(pa);
			v.z = cos(pa);
			v = Normalize(v);

			for (int a = 0; a < 360; a+=10)
			{
				float aa = a * kDegToRad;
				auto qr = Quaternionfv::AxisAngle(v, aa);
				auto m3 = Matrix33fv::AxisAngle(v, aa);
				auto m4 = Matrix44fv::AxisAngle(v, aa);
				Matrix33fv m3q(qr);
				Matrix44fv m4q(qr);

				EXPECT_TRUE(ExpectNear(m3, m4));
				EXPECT_TRUE(ExpectNear(m3q, m4));
				EXPECT_TRUE(ExpectNear(m3q, m4q));
			}
		}
	}
}
