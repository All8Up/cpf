//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/SampleDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class Format : int32_t;
		enum class SwapEffect : int32_t;

		struct SwapChainDesc
		{
			Format mFormat;
			SwapEffect mSwapEffect;
			SampleDesc mMultiSample;
			int32_t mBackBufferCount;
			bool mAllowFullscreen;
		};
	}
}
