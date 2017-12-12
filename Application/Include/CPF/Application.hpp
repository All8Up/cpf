//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/iApplication.hpp"

#define CPF_APPLICATION(name) \
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry) \
{ \
	if (registry) \
	{ \
		return registry->Install(iApplication::kCID.GetID(), new Plugin::tClassFactory<name>()); \
	} \
	return GOM::kInvalidParameter; \
} \
\
static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry) \
{ \
	if (registry) \
	{ \
		return registry->Remove(iApplication::kCID.GetID()); \
	} \
	return GOM::kInvalidParameter; \
} \
CPF_PLUGIN_REGISTER(Application) \
	&Install, \
	&Remove \
};
