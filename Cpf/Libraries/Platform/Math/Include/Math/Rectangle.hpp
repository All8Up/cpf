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
				: mRect(left, right, top, bottom)
			{}

			Element Left() const { return mRect.GetLane(0); }
			Element Right() const { return mRect.GetLane(1); }
			Element Top() const { return mRect.GetLane(2); }
			Element Bottom() const { return mRect.GetLane(3); }

			void Left(Element v) { mRect.SetLane(0, v); }
			void Right(Element v) { mRect.SetLane(1, v); }
			void Top(Element v) { mRect.SetLane(2, v); }
			void Bottom(Element v) { mRect.SetLane(3, v); }

		private:
			TYPE mRect;
		};
	}
}

#include "Math/Detail/Rectangle.inl"
#include "SIMD/Types.hpp"

namespace Cpf
{
	namespace Math
	{
		using Rectanglei = Rectangle<SIMD::I32x4>;
	}
}
