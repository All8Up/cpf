//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/Descriptors/SampleDesc.hpp"
#include "Graphics/Format.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct ImageFlags
		{
			enum : uint32_t
			{
				eNone = 0,
				eAllowDepthStencil = 1 << 0
			};
		};

		struct ImageDesc
		{
			int32_t mWidth;
			int32_t mHeight;
			int32_t mDepth;
			int32_t mMipLevels;
			Format mFormat;
			SampleDesc mSamples;
			uint32_t mFlags;
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
