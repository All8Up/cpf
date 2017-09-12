//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class Format : int32_t;

		struct DepthStencilValue
		{
			float mDepth;
			uint8_t mStencil;
		};

		struct ClearValue
		{
			Format mFormat;
			union
			{
				float mColor[4];
				DepthStencilValue mDepthStencil;
			};
		};
	}
}
