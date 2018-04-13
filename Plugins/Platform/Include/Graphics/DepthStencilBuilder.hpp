//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/DepthStencilStateDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		struct DepthStencilStateDescBuilder
		{
			DepthStencilStateDescBuilder();

			operator DepthStencilStateDesc() const;

			DepthStencilStateDescBuilder& DepthTest(bool flag = true);
			DepthStencilStateDescBuilder& DepthWriteMask(DepthWriteMask mask);
			DepthStencilStateDescBuilder& Comparison(ComparisonFunc func);
			DepthStencilStateDescBuilder& StencilEnable(bool flag = true);
			DepthStencilStateDescBuilder& StencilReadMask(uint8_t mask);
			DepthStencilStateDescBuilder& StencilWriteMask(uint8_t mask);
			DepthStencilStateDescBuilder& StencilFrontFace(StencilOp op);
			DepthStencilStateDescBuilder& StencilBackFace(StencilOp op);

		private:
			DepthStencilStateDesc mState;
		};

		template <>
		struct BuilderType<DepthStencilStateDesc>
		{
			using Builder = DepthStencilStateDescBuilder;
		};

		//////////////////////////////////////////////////////////////////////////
		inline DepthStencilStateDescBuilder DepthStencilStateDescBuild()
		{
			return DepthStencilStateDescBuilder();
		}

		//////////////////////////////////////////////////////////////////////////
		inline DepthStencilStateDescBuilder::DepthStencilStateDescBuilder()
			: mState(Defaults<DepthStencilStateDesc>())
		{}

		inline DepthStencilStateDescBuilder::operator DepthStencilStateDesc() const
		{
			return mState;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::DepthTest(bool flag)
		{
			mState.mDepthTest = flag;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::DepthWriteMask(Graphics::DepthWriteMask mask)
		{
			mState.mDepthWriteMask = mask;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::Comparison(ComparisonFunc func)
		{
			mState.mComparisonFunc = func;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::StencilEnable(bool flag)
		{
			mState.mStencilEnable = flag;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::StencilReadMask(uint8_t mask)
		{
			mState.mStencilReadMask = mask;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::StencilWriteMask(uint8_t mask)
		{
			mState.mStencilWriteMask = mask;
			return *this;
		}

		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::StencilFrontFace(StencilOp op)
		{
			mState.mFrontFace = op;
			return *this;
		}
		inline DepthStencilStateDescBuilder& DepthStencilStateDescBuilder::StencilBackFace(StencilOp op)
		{
			mState.mBackFace = op;
			return *this;
		}
	}
}
