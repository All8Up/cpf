//////////////////////////////////////////////////////////////////////////
#include "Graphics/PipelineStateDesc.hpp"
#include "Graphics/iShader.hpp"
#include "Graphics/iResourceBinding.hpp"
#include "Move.hpp"

using namespace Cpf;
using namespace Graphics;

PipelineStateDesc::PipelineStateDesc()
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


PipelineStateDesc::PipelineStateDesc(const PipelineStateDesc& rhs)
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

PipelineStateDesc::Builder PipelineStateDesc::Build()
{
	return Builder();
}


//////////////////////////////////////////////////////////////////////////
PipelineStateDesc::Builder::Builder()
{

}

PipelineStateDesc::Builder::operator PipelineStateDesc () const
{
	return mState;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::ResourceBinding(iResourceBinding* binding)
{
	mState.mpResourceBinding.Adopt(binding);
	mState.mpResourceBinding.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::VertexShader(iShader* shader)
{
	mState.mpVertex.Adopt(shader);
	mState.mpVertex.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::PixelShader(iShader* shader)
{
	mState.mpPixel.Adopt(shader);
	mState.mpPixel.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::DomainShader(iShader* shader)
{
	mState.mpDomain.Adopt(shader);
	mState.mpDomain.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::HullShader(iShader* shader)
{
	mState.mpHull.Adopt(shader);
	mState.mpHull.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::GeometryShader(iShader* shader)
{
	mState.mpGeometry.Adopt(shader);
	mState.mpGeometry.AddRef();
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::SampleMask(uint32_t mask)
{
	mState.mSampleMask = mask;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::IndexCut(IndexStripCut cut)
{
	mState.mIndexStripCut = cut;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::Topology(TopologyType topology)
{
	mState.mTopology = topology;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::DepthStencilFormat(Format format)
{
	mState.mDepthStencilFormat = format;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::SampleState(int32_t count, int32_t quality)
{
	mState.mSampleState.mCount = count;
	mState.mSampleState.mQuality = quality;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::AlphaToCoverage(bool flag)
{
	mState.mBlendState.mAlphaToCoverage = flag;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::IndependentBlend(bool flag)
{
	mState.mBlendState.mIndependentBlend = flag;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::TargetBlend(int32_t target, RenderTargetBlendStateDesc state)
{
	mState.mBlendState.mRenderTarget[target] = state;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::Rasterizer(RasterizerStateDesc state)
{
	mState.mRasterizerState = state;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::DepthStencil(DepthStencilStateDesc state)
{
	mState.mDepthStencil = state;
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::InputLayout(std::initializer_list<ElementDesc> initList)
{
	mState.mInputLayout = InputLayoutDesc(initList);
	return *this;
}

PipelineStateDesc::Builder& PipelineStateDesc::Builder::RenderTargets(std::initializer_list<Format> formats)
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
