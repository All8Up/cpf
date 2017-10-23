//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Graphics/RasterizerStateDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct RasterizerStateDescBuilder
		{
			RasterizerStateDescBuilder();

			operator RasterizerStateDesc () const;

			RasterizerStateDescBuilder& FillMode(FillMode fillMode);
			RasterizerStateDescBuilder& CullMode(CullMode cullMode);
			RasterizerStateDescBuilder& WindingOrder(WindingOrder windingOrder);
			RasterizerStateDescBuilder& DepthBias(int32_t depthBias);
			RasterizerStateDescBuilder& DepthBiasClamp(float depthBiasClamp);
			RasterizerStateDescBuilder& SlopeScaledDepthBias(float slopeScaledDepthBias);
			RasterizerStateDescBuilder& DepthClipping(bool clipping = true);
			RasterizerStateDescBuilder& Multisampling(bool multisampling = true);
			RasterizerStateDescBuilder& AALines(bool aaLines = true);
			RasterizerStateDescBuilder& ForcedSampleCount(int32_t forcedSampleCount);
			RasterizerStateDescBuilder& ConservativeRasterization(ConservativeRasterization conservativeRasterization);

		private:
			RasterizerStateDesc mState;
		};

		template <>
		struct BuilderType<RasterizerStateDesc>
		{
			using Builder = RasterizerStateDescBuilder;
		};

		//////////////////////////////////////////////////////////////////////////
		inline RasterizerStateDescBuilder::RasterizerStateDescBuilder()
			: mState(Defaults<RasterizerStateDesc>())
		{}

		inline RasterizerStateDescBuilder::operator RasterizerStateDesc () const
		{
			return mState;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::FillMode(Graphics::FillMode fillMode)
		{
			mState.mFillMode = fillMode;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::CullMode(Graphics::CullMode cullMode)
		{
			mState.mCullMode = cullMode;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::WindingOrder(Graphics::WindingOrder windingOrder)
		{
			mState.mWindingOrder = windingOrder;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::DepthBias(int32_t depthBias)
		{
			mState.mDepthBias = depthBias;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::DepthBiasClamp(float depthBiasClamp)
		{
			mState.mDepthBiasClamp = depthBiasClamp;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::SlopeScaledDepthBias(float slopeScaledDepthBias)
		{
			mState.mSlopeScaledDepthBias = slopeScaledDepthBias;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::DepthClipping(bool clipping)
		{
			mState.mDepthClipping = clipping;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::Multisampling(bool multisampling)
		{
			mState.mMultisampling = multisampling;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::AALines(bool aaLines)
		{
			mState.mAALines = aaLines;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::ForcedSampleCount(int32_t forcedSampleCount)
		{
			mState.mForcedSampleCount = forcedSampleCount;
			return *this;
		}

		inline RasterizerStateDescBuilder& RasterizerStateDescBuilder::ConservativeRasterization(Graphics::ConservativeRasterization conservativeRasterization)
		{
			mState.mConservativeRasterization = conservativeRasterization;
			return *this;
		}
	}
}
