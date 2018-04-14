//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin.hpp"
#include "CPF/GOM/Result.hpp"
#include "CPF/GOM/ResultCodes.hpp"

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
#	define CPF_REGISTER_PLUGIN(name) extern ::PluginDesc CPF_CONCAT(PluginRegistration_, name);							\
	extern "C" { CPF_EXPORT_ATTR const ::PluginDesc* PluginGetDesc() {return &CPF_CONCAT(PluginRegistration_, name);} }	\
	::PluginDesc CPF_CONCAT(PluginRegistration_, name) = { #name,
#else
#	define CPF_REGISTER_PLUGIN(name) PluginDesc CPF_CONCAT(PluginRegistration_, name) = { #name,
#endif

/**
 @brief Install a static plugin.
 @param registry The registry.
 @param name The name of the plugin desired.
 */
#define CPF_INSTALL_STATIC_PLUGIN(registry, name) { extern ::PluginDesc CPF_CONCAT(PluginRegistration_, name); (*CPF_CONCAT(PluginRegistration_, name).Install)(registry); }

#define CPF_REMOVE_STATIC_PLUGIN(registry, name) { extern ::PluginDesc CPF_CONCAT(PluginRegistration_, name); (*CPF_CONCAT(PluginRegistration_, name).Remove)(registry); }
