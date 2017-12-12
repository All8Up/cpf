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


/** @brief Description of a plugin. */
struct PluginDesc
{
	const char* Name;
	CPF::GOM::Result(CPF_STDCALL *Install)(CPF::Plugin::iRegistry*);
	CPF::GOM::Result(CPF_STDCALL *Remove)(CPF::Plugin::iRegistry*);
};

/** @brief The function name exported by each plugin. */
const char kPluginAPIGetDesc[] = "PluginGetDesc";

/** @brief The call prototype for plugin initialization. */
using PluginAPIGetDesc = const PluginDesc* (CPF_STDCALL*)();

// Select the registration method based on if the plugin is static or not.
#if !defined(CPF_PLUGIN_STATIC)
#define CPF_PLUGIN_REGISTER(name) extern PluginDesc PluginRegistration_##name;								\
	extern "C" { CPF_EXPORT_ATTR const PluginDesc* PluginGetDesc() {return &PluginRegistration_##name;} }	\
	PluginDesc PluginRegistration_##name = { #name,
#else
#define CPF_PLUGIN_REGISTER(name) PluginDesc PluginRegistration_##name = { #name,
#endif

/**
 @brief Install a static plugin.
 @param registry The registry.
 @param name The name of the plugin desired.
 */
#define CPF_INSTALL_STATIC_PLUGIN(registry, name) { extern PluginDesc PluginRegistration_##name; (*PluginRegistration_##name.Install)(registry); }
