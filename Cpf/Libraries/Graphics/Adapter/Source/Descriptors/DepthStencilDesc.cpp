//////////////////////////////////////////////////////////////////////////
#include "Graphics/Descriptors/DepthStencilDesc.hpp"

using namespace Cpf;
using namespace Graphics;

//////////////////////////////////////////////////////////////////////////
DepthStencilStateDesc::DepthStencilStateDesc()
	: mDepthTest(false)
	, mDepthWriteMask(DepthWriteMask::eAll)
	, mComparisonFunc(ComparisonFunc::eLess)
	, mStencilEnable(false)
	, mStencilReadMask(0xFF)
	, mStencilWriteMask(0xFF)
	, mFrontFace(StencilOp::eInc)
	, mBackFace(StencilOp::eDec)
{}

DepthStencilStateDesc::Builder DepthStencilStateDesc::Build()
{
	return Builder();
}

//////////////////////////////////////////////////////////////////////////
DepthStencilStateDesc::Builder::Builder()
{}

DepthStencilStateDesc::Builder::operator DepthStencilStateDesc() const
{
	return mState;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::DepthTest(bool flag)
{
	mState.mDepthTest = flag;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::DepthWriteMask(Graphics::DepthWriteMask mask)
{
	mState.mDepthWriteMask = mask;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::Comparison(ComparisonFunc func)
{
	mState.mComparisonFunc = func;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilEnable(bool flag)
{
	mState.mStencilEnable = flag;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilReadMask(uint8_t mask)
{
	mState.mStencilReadMask = mask;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilWriteMask(uint8_t mask)
{
	mState.mStencilWriteMask = mask;
	return *this;
}

DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilFrontFace(StencilOp op)
{
	mState.mFrontFace = op;
	return *this;
}
DepthStencilStateDesc::Builder& DepthStencilStateDesc::Builder::StencilBackFace(StencilOp op)
{
	mState.mBackFace = op;
	return *this;
}
