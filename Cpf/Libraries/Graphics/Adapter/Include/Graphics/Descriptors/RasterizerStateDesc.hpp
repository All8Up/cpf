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
	}
}
