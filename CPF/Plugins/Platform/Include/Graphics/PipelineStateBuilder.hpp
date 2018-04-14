//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Platform/Graphics/InputElementDesc.hpp"
#include "CPF/Platform/Graphics/PipelineStateDesc.hpp"

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
			PipelineStateBuilder& InputLayout(const CPF::STD::Vector<InputElementDesc>& initList);

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
			: mState(Defaults<PipelineStateDesc>())
		{

		}

		inline PipelineStateBuilder::operator PipelineStateDesc () const
		{
			return mState;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::VertexShader(iShader* shader)
		{
			mState.mpVertex = shader;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::PixelShader(iShader* shader)
		{
			mState.mpPixel = shader;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::DomainShader(iShader* shader)
		{
			mState.mpDomain = shader;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::HullShader(iShader* shader)
		{
			mState.mpHull = shader;
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::GeometryShader(iShader* shader)
		{
			mState.mpGeometry = shader;
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

		inline PipelineStateBuilder& PipelineStateBuilder::InputLayout(const CPF::STD::Vector<InputElementDesc>& layout)
		{
			mState.mInputLayout.mCount = int32_t(layout.size());
			mState.mInputLayout.mpElements = new InputElementDesc[layout.size()];
			int i = 0;
			for (auto& element : layout)
			{
				mState.mInputLayout.mpElements[i++] = element;
			}
			return *this;
		}

		inline PipelineStateBuilder& PipelineStateBuilder::RenderTargets(std::initializer_list<Format> formats)
		{
			CPF_ASSERT(formats.size() <= kMaxRenderTargets);
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
