//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/BlendStateDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct RenderTargetBlendStateDescBuilder
		{
			RenderTargetBlendStateDescBuilder() : mBlend(Defaults<RenderTargetBlendStateDesc>()) {}

			operator RenderTargetBlendStateDesc() const;

			RenderTargetBlendStateDescBuilder& Blending(bool flag = true);
			RenderTargetBlendStateDescBuilder& LogicOps(bool flag = true);
			RenderTargetBlendStateDescBuilder& Src(BlendFunc func);
			RenderTargetBlendStateDescBuilder& Dst(BlendFunc func);
			RenderTargetBlendStateDescBuilder& Op(BlendOp op);
			RenderTargetBlendStateDescBuilder& SrcAlpha(BlendFunc func);
			RenderTargetBlendStateDescBuilder& DstAlpha(BlendFunc func);
			RenderTargetBlendStateDescBuilder& OpAlpha(BlendOp op);
			RenderTargetBlendStateDescBuilder& Logic(LogicOp op);
			RenderTargetBlendStateDescBuilder& WriteMask(Graphics::WriteMask mask);

		private:
			RenderTargetBlendStateDesc mBlend;
		};

		template <>
		struct BuilderType<RenderTargetBlendStateDesc>
		{
			using Builder = RenderTargetBlendStateDescBuilder;
		};

		//////////////////////////////////////////////////////////////////////////
		inline RenderTargetBlendStateDescBuilder::operator RenderTargetBlendStateDesc() const
		{
			return mBlend;
		}


		//////////////////////////////////////////////////////////////////////////
		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::Blending(bool flag)
		{
			mBlend.mBlending = flag;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::LogicOps(bool flag)
		{
			mBlend.mLogicOps = flag;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::Src(BlendFunc func)
		{
			mBlend.mSrcBlend = func;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::Dst(BlendFunc func)
		{
			mBlend.mDstBlend = func;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::Op(BlendOp op)
		{
			mBlend.mBlendOp = op;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::SrcAlpha(BlendFunc func)
		{
			mBlend.mSrcBlendAlpha = func;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::DstAlpha(BlendFunc func)
		{
			mBlend.mDstBlendAlpha = func;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::OpAlpha(BlendOp op)
		{
			mBlend.mBlendOpAlpha = op;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::Logic(LogicOp op)
		{
			mBlend.mLogicOp = op;
			return *this;
		}

		inline RenderTargetBlendStateDescBuilder& RenderTargetBlendStateDescBuilder::WriteMask(Graphics::WriteMask mask)
		{
			mBlend.mWriteMask = mask;
			return *this;
		}
	}
}
