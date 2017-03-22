//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector2v.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		class Rectangle
		{
		public:
			using Element = typename TYPE::Element;

			Rectangle() {}
			Rectangle(Element left, Element right, Element top, Element bottom)
				: mLeft(left)
				, mTop(top)
				, mRight(right)
				, mBottom(bottom) {}

			Element Top() const { return mTop; }
			Element Left() const { return mLeft; }
			Element Bottom() const { return mBottom; }
			Element Right() const { return mRight; }

			void Top(Element v) { mTop = v; }
			void Left(Element v) { mLeft = v; }
			void Bottom(Element v) { mBottom = v; }
			void Right(Element v) { mRight = v; }

		private:
			Element mLeft;
			Element mRight;
			Element mTop;
			Element mBottom;
		};
	}
}

#include "Math/Detail/Rectangle.inl"
#include "SIMD/Types.hpp"

namespace Cpf
{
	namespace Math
	{
		using Rectanglei = Rectangle<SIMD::I32x4_2>;
	}
}
