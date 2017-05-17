#include "Plugin/iRegistry.hpp"

using namespace Cpf;

extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return true;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
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
