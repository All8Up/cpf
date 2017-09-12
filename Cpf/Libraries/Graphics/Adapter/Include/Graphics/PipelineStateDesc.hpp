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

		inline PipelineStateDesc::PipelineStateDesc()
			: mSampleMask(uint32_t(-1))
			, mIndexStripCut(IndexStripCut::eNone)
			, mTopology(TopologyType::eTriangle)
			, mRenderTargetCount(0)
			, mDepthStencilFormat(Format::eNone)
			, mSampleState(1, 0)
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

		inline PipelineStateDesc::Builder PipelineStateDesc::Build()
		{
			return Builder();
		}


		//////////////////////////////////////////////////////////////////////////
		inline PipelineStateDesc::Builder::Builder()
		{

		}

		inline PipelineStateDesc::Builder::operator PipelineStateDesc () const
		{
			return mState;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::ResourceBinding(iResourceBinding* binding)
		{
			mState.mpResourceBinding.Adopt(binding);
			mState.mpResourceBinding.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::VertexShader(iShader* shader)
		{
			mState.mpVertex.Adopt(shader);
			mState.mpVertex.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::PixelShader(iShader* shader)
		{
			mState.mpPixel.Adopt(shader);
			mState.mpPixel.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::DomainShader(iShader* shader)
		{
			mState.mpDomain.Adopt(shader);
			mState.mpDomain.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::HullShader(iShader* shader)
		{
			mState.mpHull.Adopt(shader);
			mState.mpHull.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::GeometryShader(iShader* shader)
		{
			mState.mpGeometry.Adopt(shader);
			mState.mpGeometry.AddRef();
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::SampleMask(uint32_t mask)
		{
			mState.mSampleMask = mask;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::IndexCut(IndexStripCut cut)
		{
			mState.mIndexStripCut = cut;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::Topology(TopologyType topology)
		{
			mState.mTopology = topology;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::DepthStencilFormat(Format format)
		{
			mState.mDepthStencilFormat = format;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::SampleState(int32_t count, int32_t quality)
		{
			mState.mSampleState.mCount = count;
			mState.mSampleState.mQuality = quality;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::AlphaToCoverage(bool flag)
		{
			mState.mBlendState.mAlphaToCoverage = flag;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::IndependentBlend(bool flag)
		{
			mState.mBlendState.mIndependentBlend = flag;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::TargetBlend(int32_t target, RenderTargetBlendStateDesc state)
		{
			mState.mBlendState.mRenderTarget[target] = state;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::Rasterizer(RasterizerStateDesc state)
		{
			mState.mRasterizerState = state;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::DepthStencil(DepthStencilStateDesc state)
		{
			mState.mDepthStencil = state;
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::InputLayout(std::initializer_list<ElementDesc> initList)
		{
			mState.mInputLayout = cInputLayoutDesc(initList);
			return *this;
		}

		inline PipelineStateDesc::Builder& PipelineStateDesc::Builder::RenderTargets(std::initializer_list<Format> formats)
		{
			CPF_ASSERT(formats.size() <= PipelineStateDesc::kMaxRenderTargets);
			mState.mRenderTargetCount = int32_t(formats.size());
			int i = 0;
			for (auto it : formats)
			{
				mState.mRenderTargetFormats[i++] = it;
			}
			return *this;
		}
	}
}
