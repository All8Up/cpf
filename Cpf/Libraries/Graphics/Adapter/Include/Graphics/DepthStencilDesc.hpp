//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "Graphics/DepthWriteMask.hpp"
#include "Graphics/ComparisonFunc.hpp"
#include "Graphics/StencilOp.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct DepthStencilStateDesc
		{
			bool mDepthTest;
			DepthWriteMask mDepthWriteMask;
			ComparisonFunc mComparisonFunc;
			bool mStencilEnable;
			uint8_t mStencilReadMask;
			uint8_t mStencilWriteMask;
			StencilOp mFrontFace;
			StencilOp mBackFace;
		};

		template <>
		DepthStencilStateDesc Defaults()
		{
			return DepthStencilStateDesc{
				false,
				DepthWriteMask::eAll,
				ComparisonFunc::eLess,
				false,
				0xFF,
				0xFF,
				StencilOp::eInc,
				StencilOp::eDec
			};
		}
	}
}
