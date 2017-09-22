//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/BlendStateDesc.hpp"
#include "Graphics/RasterizerStateDesc.hpp"
#include "Graphics/DepthStencilStateDesc.hpp"
#include "Graphics/InputLayoutDesc.hpp"
#include "Graphics/SampleDesc.hpp"
#include "Graphics/iResourceBinding.hpp"
#include "Graphics/IndexStripCut.hpp"
#include "Graphics/TopologyType.hpp"
#include "IntrusivePtr.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
		struct iShader;
		struct iPipeline;
		struct iResourceBinding;

		struct PipelineStateDesc
		{
			static constexpr int kMaxRenderTargets = 8;

			PipelineStateDesc();
			PipelineStateDesc(const PipelineStateDesc& rhs);

			IntrusivePtr<iResourceBinding> mpResourceBinding;
			// TODO: Shaders should not be instances, they should be opaque handles or a struct.
			IntrusivePtr<iShader> mpVertex;
			IntrusivePtr<iShader> mpPixel;
			IntrusivePtr<iShader> mpDomain;
			IntrusivePtr<iShader> mpHull;
			IntrusivePtr<iShader> mpGeometry;
			BlendStateDesc mBlendState;
			uint32_t mSampleMask;
			RasterizerStateDesc mRasterizerState;
			DepthStencilStateDesc mDepthStencil;
			InputLayoutDesc mInputLayout;
			IndexStripCut mIndexStripCut;
			TopologyType mTopology;
			int32_t mRenderTargetCount;
			Format mRenderTargetFormats[kMaxRenderTargets];
			Format mDepthStencilFormat;
			SampleDesc mSampleState;

			// Items not in the pipeline at this time.
			// StreamOutput
			// node mask
			// cache pipeline state
			// flags
		};

		inline PipelineStateDesc::PipelineStateDesc()
			: mBlendState(Defaults<BlendStateDesc>())
			, mSampleMask(uint32_t(-1))
			, mRasterizerState(Defaults<RasterizerStateDesc>())
			, mIndexStripCut(IndexStripCut::eNone)
			, mTopology(TopologyType::eTriangle)
			, mRenderTargetCount(0)
			, mDepthStencilFormat(Format::eNone)
			, mSampleState{ 1, 0 }
		{
			for (int i = 0; i < kMaxRenderTargets; ++i)
				mRenderTargetFormats[i] = Format::eNone;
		}

		inline PipelineStateDesc::PipelineStateDesc(const PipelineStateDesc& rhs)
			: mpResourceBinding(rhs.mpResourceBinding)
			, mpVertex(rhs.mpVertex)
			, mpPixel(rhs.mpPixel)
			, mpDomain(rhs.mpDomain)
			, mpHull(rhs.mpHull)
			, mpGeometry(rhs.mpGeometry)
			, mBlendState(rhs.mBlendState)
			, mSampleMask(rhs.mSampleMask)
			, mRasterizerState(rhs.mRasterizerState)
			, mDepthStencil(rhs.mDepthStencil)
			, mInputLayout(rhs.mInputLayout)
			, mIndexStripCut(rhs.mIndexStripCut)
			, mTopology(rhs.mTopology)
			, mRenderTargetCount(rhs.mRenderTargetCount)
			, mDepthStencilFormat(rhs.mDepthStencilFormat)
			, mSampleState(rhs.mSampleState)
		{
			for (int i = 0; i < kMaxRenderTargets; ++i)
				mRenderTargetFormats[i] = rhs.mRenderTargetFormats[i];
		}
	}
}
