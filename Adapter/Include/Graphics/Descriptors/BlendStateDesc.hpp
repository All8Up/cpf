//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/BlendFunc.hpp"
#include "Graphics/BlendOp.hpp"
#include "Graphics/LogicOp.hpp"
#include <initializer_list>


namespace Cpf
{
	namespace Graphics
	{
		struct WriteMask
		{
			enum : uint8_t
			{
				eRed = 1,
				eGreen = 2,
				eBlue = 4,
				eAlpha = 8,
				eAll = (eRed | eGreen | eBlue | eAlpha)
			};
		};

		struct RenderTargetBlendStateDesc
		{
			RenderTargetBlendStateDesc();

			struct Builder;
			static Builder Build();

			bool mBlending;
			bool mLogicOps;
			BlendFunc mSrcBlend;
			BlendFunc mDstBlend;
			BlendOp mBlendOp;
			BlendFunc mSrcBlendAlpha;
			BlendFunc mDstBlendAlpha;
			BlendOp mBlendOpAlpha;
			LogicOp mLogicOp;
			uint8_t mWriteMask;
		};

		struct RenderTargetBlendStateDesc::Builder
		{
			operator RenderTargetBlendStateDesc() const;

			Builder& Blending(bool flag = true);
			Builder& LogicOps(bool flag = true);
			Builder& Src(BlendFunc func);
			Builder& Dst(BlendFunc func);
			Builder& Op(BlendOp op);
			Builder& SrcAlpha(BlendFunc func);
			Builder& DstAlpha(BlendFunc func);
			Builder& OpAlpha(BlendOp op);
			Builder& Logic(LogicOp op);
			Builder& WriteMask(uint8_t mask);

		private:
			RenderTargetBlendStateDesc mBlend;
		};

		struct BlendState
		{
			BlendState();

			bool mAlphaToCoverage;
			bool mIndependentBlend;
			RenderTargetBlendStateDesc mRenderTarget[8];
		};
	}
}
