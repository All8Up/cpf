//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/SampleDesc.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class Format : int32_t;
		enum class ImageFlags : int32_t;

		struct ImageDesc
		{
			int32_t mWidth;
			int32_t mHeight;
			int32_t mDepth;
			int32_t mMipLevels;
			Format mFormat;
			SampleDesc mSamples;
			ImageFlags mFlags;
		};
	}
}
