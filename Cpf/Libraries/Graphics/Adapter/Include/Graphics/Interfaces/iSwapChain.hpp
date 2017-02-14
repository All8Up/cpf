//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/Format.hpp"
#include "iImage.hpp"
#include "iImageView.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class SwapEffect
		{
			eDiscard,
			eSequential,
			eFlipSequential,
			eFlipDiscard
		};

		struct SwapChainDesc
		{
			Format mFormat;
			SwapEffect mSwapEffect;
			SampleDesc mMultiSample;
			int32_t mBackBufferCount;
			bool mAllowFullscreen;
		};

		class iSwapChain : public iRefCounted
		{
		public:
			virtual ~iSwapChain() = 0;

			virtual void Present() = 0;
			virtual void Resize(int32_t x, int32_t y) = 0;
			virtual int32_t GetCurrentIndex() = 0;
			virtual iImage* GetImage(int32_t index) = 0;
			virtual iImageView* GetImageView(int32_t index) = 0;
		};
	}
}
