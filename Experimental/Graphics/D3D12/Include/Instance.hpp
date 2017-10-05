//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"

namespace CPF
{
	struct Instance
	{
		Math::Vector3f mTranslation;
		Math::Vector3f mScale;
		// TODO: Resurrect the Matrix33f non-simd class for this.
		Math::Vector3f mOrientation0;
		Math::Vector3f mOrientation1;
		Math::Vector3f mOrientation2;
	};
}
