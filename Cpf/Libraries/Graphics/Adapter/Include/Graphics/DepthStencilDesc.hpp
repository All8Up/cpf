//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/DepthWriteMask.hpp"
#include "Graphics/ComparisonFunc.hpp"
#include "Graphics/StencilOp.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct DepthStencilStateDesc
		{
			DepthStencilStateDesc();

			struct Builder;
			static Builder Build();

			bool GetDepthTest() const { return mDepthTest; }
			DepthWriteMask GetDepthWriteMask() const { return mDepthWriteMask; }
			ComparisonFunc GetComparison() const { return mComparisonFunc; }
			bool GetStenciling() const { return mStencilEnable; }
			uint8_t GetStencilReadMask() const { return mStencilReadMask; }
			uint8_t GetStencilWriteMask() const { return mStencilWriteMask; }
			StencilOp GetFrontOp() const { return mFrontFace; }
			StencilOp GetBackOp() const { return mBackFace; }

		private:
			bool mDepthTest;
			DepthWriteMask mDepthWriteMask;
			ComparisonFunc mComparisonFunc;
			bool mStencilEnable;
			uint8_t mStencilReadMask;
			uint8_t mStencilWriteMask;
			StencilOp mFrontFace;
			StencilOp mBackFace;
		};

		struct DepthStencilStateDesc::Builder
		{
			Builder();

			operator DepthStencilStateDesc() const;

			Builder& DepthTest(bool flag = true);
			Builder& DepthWriteMask(DepthWriteMask mask);
			Builder& Comparison(ComparisonFunc func);
			Builder& StencilEnable(bool flag = true);
			Builder& StencilReadMask(uint8_t mask);
			Builder& StencilWriteMask(uint8_t mask);
			Builder& StencilFrontFace(StencilOp op);
			Builder& StencilBackFace(StencilOp op);

		private:
			DepthStencilStateDesc mState;
		};
	}
}
