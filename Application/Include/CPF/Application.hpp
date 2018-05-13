//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/iApplication.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/tClassFactory.hpp"

#define CPF_APPLICATION(name) \
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry) \
{ \
	if (registry) \
	{ \
		return registry->Install(iApplication::kCID, new Plugin::tClassFactory<name>()); \
	} \
	return GOM::kInvalidParameter; \
} \
\
static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry) \
{ \
	if (registry) \
	{ \
		return registry->Remove(iApplication::kCID); \
	} \
	return GOM::kInvalidParameter; \
} \
CPF_REGISTER_PLUGIN(Application) \
	&Install, \
	&Remove \
}; \
template <> PluginRegistry<void>::PluginInstance* PluginRegistry<void>::mpInstances = nullptr;
