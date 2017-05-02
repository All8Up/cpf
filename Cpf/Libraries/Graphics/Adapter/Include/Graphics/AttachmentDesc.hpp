//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Format.hpp"
#include "Graphics/SampleDesc.hpp"
#include "Graphics/LoadOp.hpp"
#include "Graphics/StoreOp.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ResourceState : int32_t;

		struct AttachmentDesc
		{
			int32_t mFlags; // TODO:
			Format mFormat;
			SampleDesc mSamples;
			LoadOp mLoadOp;
			StoreOp mStoreOp;
			LoadOp mStencilLoadOp;
			StoreOp mStencilStoreOp;
			ResourceState mStartState;
			ResourceState mFinalState;
		};

		static constexpr int32_t kInvalidAttachment = -1;
		struct AttachmentRef
		{
			int32_t mIndex;
			ResourceState mState;
		};
	}
}
