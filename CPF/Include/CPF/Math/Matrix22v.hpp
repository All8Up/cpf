//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Vector2v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		struct Matrix22
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Row = Vector2v<TYPE>;
			using Element = typename Vector2v<TYPE>::LaneType;

			//////////////////////////////////////////////////////////////////////////
			Matrix22();
			Matrix22(Element v0);
			Matrix22(Row r0, Row r1);
			Matrix22(
				Element _00, Element _01,
				Element _10, Element _11
			);

			//////////////////////////////////////////////////////////////////////////
			Matrix22<TYPE>& CPF_VECTORCALL operator = (const Matrix22<TYPE>& rhs);

			//////////////////////////////////////////////////////////////////////////
			Row& CPF_VECTORCALL operator [](int idx);

			//////////////////////////////////////////////////////////////////////////
			static Matrix22<TYPE> CPF_VECTORCALL Identity();
			static Matrix22<TYPE> CPF_VECTORCALL Rotation(Element radians);
			static Matrix22<TYPE> CPF_VECTORCALL Scale(Element x, Element y);

			//////////////////////////////////////////////////////////////////////////
			Row mRows[2];
		};
	}
}

#include "CPF/Math/Detail/Matrix22v.inl"
