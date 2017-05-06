//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ResourceState;

		enum class HeapType : int32_t;
		enum class ResourceType : int32_t;
		enum class ResourceUsage : int32_t;
		struct ResourceData;

		struct ResourceDesc
		{
		public:
			ResourceDesc(ResourceType type, HeapType heapType, ResourceState state, int32_t w, int32_t h = 0);

			ResourceType GetType() const { return mType; }
			HeapType GetHeapType() const { return mHeapType; }
			ResourceState GetResourceState() const { return mState; }
			int32_t GetWidth() const { return mWidth; }
			int32_t GetHeight() const { return mHeight; }

		private:
			ResourceType mType;
			HeapType mHeapType;
			ResourceState mState;
			int32_t mWidth;
			int32_t mHeight;
		};

		inline ResourceDesc::ResourceDesc(ResourceType type, HeapType heapType, ResourceState state, int32_t w, int32_t h)
			: mType(type)
			, mHeapType(heapType)
			, mState(state)
			, mWidth(w)
			, mHeight(h)
		{
		}
	}
}
