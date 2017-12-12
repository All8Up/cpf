//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin.hpp"
#include "GOM/Result.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}
}

struct PluginDesc
{
	const char* Name;
	CPF::GOM::Result(CPF_STDCALL *Install)(CPF::Plugin::iRegistry*);
	CPF::GOM::Result(CPF_STDCALL *Remove)(CPF::Plugin::iRegistry*);
};
const char kPluginAPIGetDesc[] = "PluginGetDesc";
using PluginAPIGetDesc = const PluginDesc* (CPF_STDCALL*)();

#if !defined(CPF_PLUGIN_STATIC)
#define CPF_PLUGIN_REGISTER(name) extern PluginDesc PluginRegistration_##name;								\
	extern "C" { CPF_EXPORT_ATTR const PluginDesc* PluginGetDesc() {return &PluginRegistration_##name;} }	\
	PluginDesc PluginRegistration_##name = { #name,
#else
#define CPF_PLUGIN_REGISTER(name) PluginDesc PluginRegistration_##name = { #name,
#endif

#define CPF_INSTALL_STATIC_PLUGIN(registry, name) { extern PluginDesc PluginRegistration_##name; (*PluginRegistration_##name.Install)(registry); }
