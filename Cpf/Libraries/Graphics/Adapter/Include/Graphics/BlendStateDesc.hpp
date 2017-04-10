//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/BlendFunc.hpp"
#include "Graphics/BlendOp.hpp"
#include "Graphics/LogicOp.hpp"
#include "Graphics/WriteMask.hpp"
#include <initializer_list>


namespace Cpf
{
	namespace Graphics
	{
		/** @brief Write mask for render targets. */
		enum class WriteMask : uint8_t;

		/** @brief Single render target blend states. */
		struct RenderTargetBlendStateDesc
		{
			RenderTargetBlendStateDesc();

			struct Builder;
			static Builder Build();

			bool mBlending;
			bool mLogicOps;
			BlendFunc mSrcBlend;
			BlendFunc mDstBlend;
			BlendOp mBlendOp;
			BlendFunc mSrcBlendAlpha;
			BlendFunc mDstBlendAlpha;
			BlendOp mBlendOpAlpha;
			LogicOp mLogicOp;
			WriteMask mWriteMask;
		};

		/** @brief Helper to make RenderTargetBlendStateDesc's easier to build. */
		struct RenderTargetBlendStateDesc::Builder
		{
			operator RenderTargetBlendStateDesc() const;

			Builder& Blending(bool flag = true);
			Builder& LogicOps(bool flag = true);
			Builder& Src(BlendFunc func);
			Builder& Dst(BlendFunc func);
			Builder& Op(BlendOp op);
			Builder& SrcAlpha(BlendFunc func);
			Builder& DstAlpha(BlendFunc func);
			Builder& OpAlpha(BlendOp op);
			Builder& Logic(LogicOp op);
			Builder& WriteMask(Graphics::WriteMask mask);

		private:
			RenderTargetBlendStateDesc mBlend;
		};

		/** @brief Full multi-target blend state. */
		struct BlendState
		{
			BlendState();

			bool mAlphaToCoverage;
			bool mIndependentBlend;
			RenderTargetBlendStateDesc mRenderTarget[8];
		};

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		inline RenderTargetBlendStateDesc::RenderTargetBlendStateDesc()
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

		inline RenderTargetBlendStateDesc::Builder RenderTargetBlendStateDesc::Build()
		{
			return Builder();
		}

		inline RenderTargetBlendStateDesc::Builder::operator RenderTargetBlendStateDesc() const
		{
			return mBlend;
		}


		//////////////////////////////////////////////////////////////////////////
		inline BlendState::BlendState()
			: mAlphaToCoverage(false)
			, mIndependentBlend(false)
		{}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Blending(bool flag)
		{
			mBlend.mBlending = flag;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::LogicOps(bool flag)
		{
			mBlend.mLogicOps = flag;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Src(BlendFunc func)
		{
			mBlend.mSrcBlend = func;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Dst(BlendFunc func)
		{
			mBlend.mDstBlend = func;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Op(BlendOp op)
		{
			mBlend.mBlendOp = op;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::SrcAlpha(BlendFunc func)
		{
			mBlend.mSrcBlendAlpha = func;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::DstAlpha(BlendFunc func)
		{
			mBlend.mDstBlendAlpha = func;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::OpAlpha(BlendOp op)
		{
			mBlend.mBlendOpAlpha = op;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::Logic(LogicOp op)
		{
			mBlend.mLogicOp = op;
			return *this;
		}

		inline RenderTargetBlendStateDesc::Builder& RenderTargetBlendStateDesc::Builder::WriteMask(Graphics::WriteMask mask)
		{
			mBlend.mWriteMask = mask;
			return *this;
		}
	}
}
