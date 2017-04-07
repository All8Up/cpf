//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/SampleDesc.hpp"
#include "Graphics/Format.hpp"

namespace Cpf
{
	namespace Graphics
	{
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

		struct ImageViewDesc
		{};

		struct DepthStencilViewDesc
		{};

		class iImage : public iRefCounted
		{
		public:
			virtual ~iImage() = 0;

			virtual const ImageDesc& GetDesc() const = 0;
		};
	}
}
