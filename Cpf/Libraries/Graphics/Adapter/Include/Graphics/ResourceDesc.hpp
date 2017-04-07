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
