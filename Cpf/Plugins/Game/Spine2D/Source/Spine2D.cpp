#include "CPF/Plugin/iRegistry.hpp"

using namespace CPF;

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

#include "spine/extension.h"
extern "C"
{
	void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
	{}

	void _spAtlasPage_disposeTexture(spAtlasPage* self)
	{}

	char* _spUtil_readFile(const char* path, int* length)
	{
		return nullptr;
	}
}
