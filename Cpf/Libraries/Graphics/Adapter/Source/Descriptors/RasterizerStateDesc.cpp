//////////////////////////////////////////////////////////////////////////
#include "Graphics/Descriptors/RasterizerStateDesc.hpp"

using namespace Cpf;
using namespace Graphics;

//////////////////////////////////////////////////////////////////////////
RasterizerStateDesc::RasterizerStateDesc()
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

RasterizerStateDesc::Builder RasterizerStateDesc::Build()
{
	return Builder();
}

//////////////////////////////////////////////////////////////////////////
RasterizerStateDesc::Builder::Builder()
{}

RasterizerStateDesc::Builder::operator RasterizerStateDesc () const
{
	return mState;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::FillMode(Graphics::FillMode fillMode)
{
	mState.mFillMode = fillMode;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::CullMode(Graphics::CullMode cullMode)
{
	mState.mCullMode = cullMode;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::WindingOrder(Graphics::WindingOrder windingOrder)
{
	mState.mWindingOrder = windingOrder;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthBias(int32_t depthBias)
{
	mState.mDepthBias = depthBias;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthBiasClamp(float depthBiasClamp)
{
	mState.mDepthBiasClamp = depthBiasClamp;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::SlowScaledDepthBias(float slopeScaledDepthBias)
{
	mState.mSlopeScaledDepthBias = slopeScaledDepthBias;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::DepthClipping(bool clipping)
{
	mState.mDepthClipping = clipping;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::Multisampling(bool multisampling)
{
	mState.mMultisampling = multisampling;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::AALines(bool aaLines)
{
	mState.mAALines = aaLines;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::ForcedSampleCount(int32_t forcedSampleCount)
{
	mState.mForcedSampleCount = forcedSampleCount;
	return *this;
}

RasterizerStateDesc::Builder& RasterizerStateDesc::Builder::ConservativeRasterization(Graphics::ConservativeRasterization conservativeRasterization)
{
	mState.mConservativeRasterization = conservativeRasterization;
	return *this;
}
