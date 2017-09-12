//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class FilterMode : int32_t;
		enum class WrapMode : int32_t;
		
		struct SamplerDesc
		{
			FilterMode mMinFilter;
			FilterMode mMagFilter;
			FilterMode mMipFilter;
			WrapMode mUWrap;
			WrapMode mVWrap;
			WrapMode mWWrap;
			float mLodMin;
			float mLodMax;
			float mLodBias;
		};
	}
}
