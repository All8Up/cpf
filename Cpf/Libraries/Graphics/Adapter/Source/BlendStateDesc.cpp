//////////////////////////////////////////////////////////////////////////
#include "Graphics/BlendStateDesc.hpp"
#include "Graphics/WriteMask.hpp"

using namespace Cpf;
using namespace Graphics;

//////////////////////////////////////////////////////////////////////////
RenderTargetBlendStateDesc::RenderTargetBlendStateDesc()
	: mBlending(false)
	, mLogicOps(false)
	, mSrcBlend(BlendFunc::eSrcColor)
	, mDstBlend(BlendFunc::eDstColor)
	, mBlendOp(BlendOp::eAdd)
	, mSrcBlendAlpha(BlendFunc::eSrcAlpha)
	, mDstBlendAlpha(BlendFunc::eDstAlpha)
	, mBlendOpAlpha(BlendOp::eAdd)
	, mLogicOp(LogicOp::eCopy)
	, mWriteMask(WriteMask::eAll)
{}

RenderTargetBlendStateDesc::Builder RenderTargetBlendStateDesc::Build()
{
	return Builder();
}

RenderTargetBlendStateDesc::Builder::operator RenderTargetBlendStateDesc() const
{
	return mBlend;
}


//////////////////////////////////////////////////////////////////////////
BlendState::BlendState()
	: mAlphaToCoverage(false)
	, mIndependentBlend(false)
{}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Blending(bool flag)
{
	mBlend.mBlending = flag;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::LogicOps(bool flag)
{
	mBlend.mLogicOps = flag;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Src(BlendFunc func)
{
	mBlend.mSrcBlend = func;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Dst(BlendFunc func)
{
	mBlend.mDstBlend = func;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Op(BlendOp op)
{
	mBlend.mBlendOp = op;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::SrcAlpha(BlendFunc func)
{
	mBlend.mSrcBlendAlpha = func;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::DstAlpha(BlendFunc func)
{
	mBlend.mDstBlendAlpha = func;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::OpAlpha(BlendOp op)
{
	mBlend.mBlendOpAlpha = op;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Logic(LogicOp op)
{
	mBlend.mLogicOp = op;
	return *this;
}

RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::WriteMask(Graphics::WriteMask mask)
{
	mBlend.mWriteMask = mask;
	return *this;
}
