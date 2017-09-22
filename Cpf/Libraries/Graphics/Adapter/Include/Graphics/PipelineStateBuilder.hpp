//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/PipelineStateDesc.hpp"

namespace CPF
{
	namespace Graphics
	{

		class PipelineStateBuilder
		{
		public:
			PipelineStateBuilder();

			PipelineStateBuilder& ResourceBinding(iResourceBinding*);
			PipelineStateBuilder& VertexShader(iShader*);
			PipelineStateBuilder& PixelShader(iShader*);
			PipelineStateBuilder& DomainShader(iShader*);
			PipelineStateBuilder& HullShader(iShader*);
			PipelineStateBuilder& GeometryShader(iShader*);
			PipelineStateBuilder& SampleMask(uint32_t mask);
			PipelineStateBuilder& IndexCut(IndexStripCut cut);
			PipelineStateBuilder& Topology(TopologyType topology);
			PipelineStateBuilder& DepthStencilFormat(Format format);
			PipelineStateBuilder& SampleState(int32_t count, int32_t quality);

			PipelineStateBuilder& AlphaToCoverage(bool flag = true);
			PipelineStateBuilder& IndependentBlend(bool flag = true);
			PipelineStateBuilder& TargetBlend(int32_t target, RenderTargetBlendStateDesc state);

			PipelineStateBuilder& Rasterizer(RasterizerStateDesc state);
			PipelineStateBuilder& DepthStencil(DepthStencilStateDesc state);
			PipelineStateBuilder& InputLayout(std::initializer_list<InputElementDesc> initList);

			PipelineStateBuilder& RenderTargets(std::initializer_list<Format> formats);

			operator PipelineStateDesc () const;

		private:
			PipelineStateDesc mState;
		};

		template <>
		struct BuilderType<PipelineStateDesc>
		{
			using Builder = PipelineStateBuilder;
		};

		//////////////////////////////////////////////////////////////////////////
		inline PipelineStateBuilder::PipelineStateBuilder()
		{

		}

		inline PipelineStateBuilder::operator PipelineStateDesc () const
		{
			return mState;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::ResourceBinding(iResourceBinding* binding)
		{
			mState.mpResourceBinding.Adopt(binding);
			mState.mpResourceBinding.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::VertexShader(iShader* shader)
		{
			mState.mpVertex.Adopt(shader);
			mState.mpVertex.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::PixelShader(iShader* shader)
		{
			mState.mpPixel.Adopt(shader);
			mState.mpPixel.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::DomainShader(iShader* shader)
		{
			mState.mpDomain.Adopt(shader);
			mState.mpDomain.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::HullShader(iShader* shader)
		{
			mState.mpHull.Adopt(shader);
			mState.mpHull.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::GeometryShader(iShader* shader)
		{
			mState.mpGeometry.Adopt(shader);
			mState.mpGeometry.AddRef();
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::SampleMask(uint32_t mask)
		{
			mState.mSampleMask = mask;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::IndexCut(IndexStripCut cut)
		{
			mState.mIndexStripCut = cut;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::Topology(TopologyType topology)
		{
			mState.mTopology = topology;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::DepthStencilFormat(Format format)
		{
			mState.mDepthStencilFormat = format;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::SampleState(int32_t count, int32_t quality)
		{
			mState.mSampleState.mCount = count;
			mState.mSampleState.mQuality = quality;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::AlphaToCoverage(bool flag)
		{
			mState.mBlendState.mAlphaToCoverage = flag;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::IndependentBlend(bool flag)
		{
			mState.mBlendState.mIndependentBlend = flag;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::TargetBlend(int32_t target, RenderTargetBlendStateDesc state)
		{
			mState.mBlendState.mRenderTarget[target] = state;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::Rasterizer(RasterizerStateDesc state)
		{
			mState.mRasterizerState = state;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::DepthStencil(DepthStencilStateDesc state)
		{
			mState.mDepthStencil = state;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::InputLayout(std::initializer_list<InputElementDesc> initList)
		{
			mState.mInputLayout = cInputLayoutDesc(initList);
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::RenderTargets(std::initializer_list<Format> formats)
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
