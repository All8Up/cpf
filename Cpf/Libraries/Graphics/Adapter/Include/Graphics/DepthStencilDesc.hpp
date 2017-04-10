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

		//////////////////////////////////////////////////////////////////////////
		inline DepthStencilStateDesc::DepthStencilStateDesc()
			: mDepthTest(false)
			, mDepthWriteMask(DepthWriteMask::eAll)
			, mComparisonFunc(ComparisonFunc::eLess)
			, mStencilEnable(false)
			, mStencilReadMask(0xFF)
			, mStencilWriteMask(0xFF)
			, mFrontFace(StencilOp::eInc)
			, mBackFace(StencilOp::eDec)
		{}

		inline DepthStencilStateDesc::Builder DepthStencilStateDesc::Build()
		{
			return Builder();
		}

		//////////////////////////////////////////////////////////////////////////
		inline DepthStencilStateDesc::Builder::Builder()
		{}

		inline DepthStencilStateDesc::Builder::operator DepthStencilStateDesc() const
		{
			return mState;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::DepthTest(bool flag)
		{
			mState.mDepthTest = flag;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::DepthWriteMask(Graphics::DepthWriteMask mask)
		{
			mState.mDepthWriteMask = mask;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::Comparison(ComparisonFunc func)
		{
			mState.mComparisonFunc = func;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilEnable(bool flag)
		{
			mState.mStencilEnable = flag;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilReadMask(uint8_t mask)
		{
			mState.mStencilReadMask = mask;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilWriteMask(uint8_t mask)
		{
			mState.mStencilWriteMask = mask;
			return *this;
		}

		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilFrontFace(StencilOp op)
		{
			mState.mFrontFace = op;
			return *this;
		}
		inline DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilBackFace(StencilOp op)
		{
			mState.mBackFace = op;
			return *this;
		}
	}
}
