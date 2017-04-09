//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/SampleDesc.hpp"

namespace Cpf
{
	namespace Graphics
	{
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
