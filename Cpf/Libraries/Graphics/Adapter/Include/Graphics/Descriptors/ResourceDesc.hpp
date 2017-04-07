//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ResourceState;

		enum class HeapType : int32_t
		{
			eDefault = 1,
			eUpload = 2,
			eReadback = 3,
			eCustom = 4
		};
		enum class ResourceType : int32_t
		{
			eBuffer = 1,
			eTexture1D = 2,
			eTexture2D = 3,
			eTexture3D = 4
		};
		enum class ResourceUsage : int32_t
		{
			eNone = 0,
			eRenderTarget = 0x01,
			eDepthStencil = 0x02,
			eUnorderedAccess = 0x04,
			eSimultaneous = 0x20
		};
		CPF_ENUM_FLAG_TYPE(ResourceUsage);

		struct ResourceData
		{
			const void* mpData;
			size_t mPitch;
			size_t mSlicePitch;
		};

		class ResourceDesc
		{
		public:
			ResourceDesc(ResourceType type, HeapType heapType, ResourceState state, int32_t usage, int32_t w);

			ResourceType GetType() const { return mType; }
			HeapType GetHeapType() const { return mHeapType; }
			ResourceState GetResourceState() const { return mState; }
			int32_t GetUsage() const { return mUsage; }
			int32_t GetWidth() const { return mWidth; }

		private:
			ResourceType mType;
			HeapType mHeapType;
			ResourceState mState;
			int32_t mUsage;
			int32_t mWidth;
		};
	}
}
