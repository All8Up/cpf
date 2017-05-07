//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/FillMode.hpp"
#include "Graphics/CullMode.hpp"
#include "Graphics/WindingOrder.hpp"
#include "Graphics/ConservativeRasterization.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct RasterizerStateDesc
		{
			RasterizerStateDesc();

			struct Builder;
			static Builder Build();

			FillMode GetFillMode() const { return mFillMode; }
			CullMode GetCullMode() const { return mCullMode; }
			WindingOrder GetWindingOrder() const { return mWindingOrder; }
			int32_t GetDepthBias() const { return mDepthBias; }
			float GetDepthBiasClamp() const { return mDepthBiasClamp; }
			float GetSlopedScaledDepthBias() const { return mSlopeScaledDepthBias; }
			bool GetDepthClipping() const { return mDepthClipping; }
			bool GetMultisampling() const { return mMultisampling; }
			bool GetAALines() const { return mAALines; }
			int32_t GetForcedSampleCount() const { return mForcedSampleCount; }
			ConservativeRasterization GetConservativeRasterization() const { return mConservativeRasterization; }

		private:
			FillMode mFillMode;
			CullMode mCullMode;
			WindingOrder mWindingOrder;
			int32_t mDepthBias;
			float mDepthBiasClamp;
			float mSlopeScaledDepthBias;
			bool mDepthClipping;
			bool mMultisampling;
			bool mAALines;
			int32_t mForcedSampleCount;
			ConservativeRasterization mConservativeRasterization;
		};

		struct RasterizerStateDesc::Builder
		{
			Builder();

			operator RasterizerStateDesc () const;

			Builder& FillMode(FillMode fillMode);
			Builder& CullMode(CullMode cullMode);
			Builder& WindingOrder(WindingOrder windingOrder);
			Builder& DepthBias(int32_t depthBias);
			Builder& DepthBiasClamp(float depthBiasClamp);
			Builder& SlowScaledDepthBias(float slopeScaledDepthBias);
			Builder& DepthClipping(bool clipping = true);
			Builder& Multisampling(bool multisampling = true);
			Builder& AALines(bool aaLines = true);
			Builder& ForcedSampleCount(int32_t forcedSampleCount);
			Builder& ConservativeRasterization(ConservativeRasterization conservativeRasterization);

		private:
			RasterizerStateDesc mState;
		};


		//////////////////////////////////////////////////////////////////////////
		inline RasterizerStateDesc::RasterizerStateDesc()
			: mFillMode(FillMode::eSolid)
			, mCullMode(CullMode::eBack)
			, mWindingOrder(WindingOrder::eClockwise)
			, mDepthBias(0)
			, mDepthBiasClamp(0.0f)
			, mSlopeScaledDepthBias(0.0f)
			, mDepthClipping(true)
			, mMultisampling(false)
			, mAALines(false)
			, mForcedSampleCount(0)
			, mConservativeRasterization(ConservativeRasterization::eOff)
		{}

		inline RasterizerStateDesc::Builder RasterizerStateDesc::Build()
		{
			return Builder();
		}

		//////////////////////////////////////////////////////////////////////////
		inline RasterizerStateDesc::Builder::Builder()
		{}

		inline RasterizerStateDesc::Builder::operator RasterizerStateDesc () const
		{
			return mState;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::FillMode(Graphics::FillMode fillMode)
		{
			mState.mFillMode = fillMode;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::CullMode(Graphics::CullMode cullMode)
		{
			mState.mCullMode = cullMode;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::WindingOrder(Graphics::WindingOrder windingOrder)
		{
			mState.mWindingOrder = windingOrder;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthBias(int32_t depthBias)
		{
			mState.mDepthBias = depthBias;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthBiasClamp(float depthBiasClamp)
		{
			mState.mDepthBiasClamp = depthBiasClamp;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::SlowScaledDepthBias(float slopeScaledDepthBias)
		{
			mState.mSlopeScaledDepthBias = slopeScaledDepthBias;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthClipping(bool clipping)
		{
			mState.mDepthClipping = clipping;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::Multisampling(bool multisampling)
		{
			mState.mMultisampling = multisampling;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::AALines(bool aaLines)
		{
			mState.mAALines = aaLines;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::ForcedSampleCount(int32_t forcedSampleCount)
		{
			mState.mForcedSampleCount = forcedSampleCount;
			return *this;
		}

		inline RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::ConservativeRasterization(Graphics::ConservativeRasterization conservativeRasterization)
		{
			mState.mConservativeRasterization = conservativeRasterization;
			return *this;
		}
	}
}
