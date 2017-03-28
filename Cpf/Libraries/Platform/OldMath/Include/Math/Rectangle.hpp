//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"


namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		class Rectangle
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			Rectangle();
			Rectangle(TYPE left, TYPE right, TYPE top, TYPE bottom);

			//////////////////////////////////////////////////////////////////////////
			TYPE Left() const;
			void Left(TYPE);
			TYPE Right() const;
			void Right(TYPE);
			TYPE Top() const;
			void Top(TYPE);
			TYPE Bottom() const;
			void Bottom(TYPE);

			TYPE Width() const;
			TYPE Height() const;

			operator bool() const;

			static Rectangle<TYPE> Invalid();

		private:
			//////////////////////////////////////////////////////////////////////////
			TYPE mLeft;
			TYPE mRight;
			TYPE mTop;
			TYPE mBottom;
		};

		//////////////////////////////////////////////////////////////////////////
		using Rectanglei = Rectangle<int>;

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		inline Rectangle<TYPE>::Rectangle()
			: mLeft(0)
			, mRight(0)
			, mTop(0)
			, mBottom(0)
		{}

		template<typename TYPE>
		inline Rectangle<TYPE>::Rectangle(TYPE left, TYPE right, TYPE top, TYPE bottom)
			: mLeft(left)
			, mRight(right)
			, mTop(top)
			, mBottom(bottom)
		{}

		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Left() const
		{
			return mLeft;
		}

		template<typename TYPE>
		inline void Rectangle<TYPE>::Left(TYPE value)
		{
			mLeft = value;
		}

		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Right() const
		{
			return mRight;
		}

		template<typename TYPE>
		inline void Rectangle<TYPE>::Right(TYPE value)
		{
			mRight = value;
		}

		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Top() const
		{
			return mTop;
		}

		template<typename TYPE>
		inline void Rectangle<TYPE>::Top(TYPE value)
		{
			mTop = value;
		}

		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Bottom() const
		{
			return mBottom;
		}

		template<typename TYPE>
		inline void Rectangle<TYPE>::Bottom(TYPE value)
		{
			mBottom = value;
		}

		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Width() const
		{
			return mRight - mLeft;
		}


		template<typename TYPE>
		inline TYPE Rectangle<TYPE>::Height() const
		{
			return mBottom - mTop;
		}


		template<typename TYPE>
		inline Rectangle<TYPE>::operator bool () const
		{
			return mBottom >= mTop || mRight >= mLeft;
		}

		template<typename TYPE>
		inline Rectangle<TYPE> Rectangle<TYPE>::Invalid()
		{
			return Rectangle<TYPE>(TYPE(100000), TYPE(-100000), TYPE(100000), TYPE(-100000));
		}
	}
}
