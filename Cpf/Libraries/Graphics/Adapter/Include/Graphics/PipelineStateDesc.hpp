//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/BlendStateDesc.hpp"
#include "Graphics/RasterizerStateDesc.hpp"
#include "Graphics/DepthStencilDesc.hpp"
#include "Graphics/InputLayoutDesc.hpp"
#include "Graphics/SampleDesc.hpp"
#include "Graphics/iResourceBinding.hpp"
#include "Graphics/IndexStripCut.hpp"
#include "Graphics/TopologyType.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
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

			class Builder;
			static Builder Build();

			iResourceBinding* GetResourceBinding() const { return mpResourceBinding; }

			iShader* GetVertexShader() const { return mpVertex; }
			iShader* GetPixelShader() const { return mpPixel; }
			iShader* GetDomainShader() const { return mpDomain; }
			iShader* GetHullShader() const { return mpHull; }
			iShader* GetGeometryShader() const { return mpGeometry; }

			bool GetAlphaToCoverage() const { return mBlendState.mAlphaToCoverage; }
			bool GetIndependentBlend() const { return mBlendState.mIndependentBlend; }
			const BlendState& GetBlendState() const { return mBlendState; }
			uint32_t GetSampleMask() const { return mSampleMask; }

			const RasterizerStateDesc& GetRasterizationState() const { return mRasterizerState; }
			const DepthStencilStateDesc& GetDepthStencilState() const { return mDepthStencil; }
			const cInputLayoutDesc& GetInputLayoutState() const { return mInputLayout; }
			IndexStripCut GetIndexStripCut() const { return mIndexStripCut; }
			TopologyType GetTopology() const { return mTopology; }
			int32_t GetRenderTargetCount() const { return mRenderTargetCount; }
			Format GetRenderTargetFormat(int i) const { return mRenderTargetFormats[i]; }
			Format GetDepthStencilFormat() const { return mDepthStencilFormat; }
			SampleDesc GetSampleState() const { return mSampleState; }

		private:
			IntrusivePtr<iResourceBinding> mpResourceBinding;
			IntrusivePtr<iShader> mpVertex;
			IntrusivePtr<iShader> mpPixel;
			IntrusivePtr<iShader> mpDomain;
			IntrusivePtr<iShader> mpHull;
			IntrusivePtr<iShader> mpGeometry;
			BlendState mBlendState;
			uint32_t mSampleMask;
			RasterizerStateDesc mRasterizerState;
			DepthStencilStateDesc mDepthStencil;
			cInputLayoutDesc mInputLayout;
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

		class PipelineStateDesc::Builder
		{
		public:
			Builder();

			Builder& ResourceBinding(iResourceBinding*);
			Builder& VertexShader(iShader*);
			Builder& PixelShader(iShader*);
			Builder& DomainShader(iShader*);
			Builder& HullShader(iShader*);
			Builder& GeometryShader(iShader*);
			Builder& SampleMask(uint32_t mask);
			Builder& IndexCut(IndexStripCut cut);
			Builder& Topology(TopologyType topology);
			Builder& DepthStencilFormat(Format format);
			Builder& SampleState(int32_t count, int32_t quality);

			Builder& AlphaToCoverage(bool flag = true);
			Builder& IndependentBlend(bool flag = true);
			Builder& TargetBlend(int32_t target, RenderTargetBlendStateDesc state);

			Builder& Rasterizer(RasterizerStateDesc state);
			Builder& DepthStencil(DepthStencilStateDesc state);
			Builder& InputLayout(std::initializer_list<ElementDesc> initList);

			Builder& RenderTargets(std::initializer_list<Format> formats);

			operator PipelineStateDesc () const;

		private:
			PipelineStateDesc mState;
		};
	}
}
