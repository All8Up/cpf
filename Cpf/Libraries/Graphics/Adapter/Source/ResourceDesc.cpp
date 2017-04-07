//////////////////////////////////////////////////////////////////////////
#include "Graphics/ResourceDesc.hpp"

using namespace Cpf;
using namespace Graphics;


ResourceDesc::ResourceDesc(ResourceType type, HeapType heapType, ResourceState state, int32_t usage, int32_t w)
	: mType(type)
	, mHeapType(heapType)
	, mState(state)
	, mUsage(usage)
	, mWidth(w)
{
}
