//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Matrix22<TYPE>::Matrix22()
		{}

		template <typename TYPE>
		Matrix22<TYPE>::Matrix22(Element v0)
			: mRows {Row(v0), Row(v0)}
		{}

		template <typename TYPE>
		Matrix22<TYPE>::Matrix22(Row r0, Row r1)
			: mRows{r0, r1}
		{}

		template <typename TYPE>
		Matrix22<TYPE>::Matrix22(
			Element _00, Element _01,
			Element _10, Element _11
		)
			: mRows{ Row{ _00, _01 }, Row{_10, _11} }
		{}

		template <typename TYPE>
		typename Matrix22<TYPE>::Row& Matrix22<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		bool CPF_VECTORCALL Near(const Matrix22<TYPE> lhs, const Matrix22<TYPE> rhs, typename Matrix22<TYPE>::Element tolerance)
		{
			return Near(lhs.mRows[0], rhs.mRows[0], tolerance) &&
				Near(lhs.mRows[1], rhs.mRows[1], tolerance);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix22<TYPE> Matrix22<TYPE>::Identity()
		{
			return Matrix22<TYPE>(
				Element(1), Element(0),
				Element(0), Element(1)
				);
		}

		template <typename TYPE>
		Matrix22<TYPE> Matrix22<TYPE>::Rotation(Element radians)
		{
			return Matrix22<TYPE>(
				Element(std::cos(radians)), Element(-std::sin(radians)),
				Element(std::sin(radians)), Element(std::cos(radians))
				);
		}

		template <typename TYPE>
		Matrix22<TYPE> Matrix22<TYPE>::Scale(Element x, Element y)
		{
			return Matrix22<TYPE>(
				Element(x), Element(0),
				Element(0), Element(y)
				);
		}
	}
}
