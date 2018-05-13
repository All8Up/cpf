//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin.hpp"
#include "CPF/GOM/Result.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/Plugin/iRegistry.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
*/
template <typename IGNORED>
class PluginRegistry
{
public:
    static void* Install(const char* name)
    {
        const auto instance = new PluginInstance{ name, mpInstances };
        mpInstances = instance;
        return instance;
    }
    static void DebugDump()
    {
        PluginInstance* current = mpInstances;
        CPF_LOG(Plugins, Info) << "--- Plugin Registry ---";
        while (current)
        {
            CPF_LOG(Plugins, Info) << "Plugin: " << current->mpName;
            current = current->mpNext;
        }
    }

private:
    struct PluginInstance
    {
        const char* mpName;
        PluginInstance* mpNext;
    };
    static PluginInstance* mpInstances;
};
//////////////////////////////////////////////////////////////////////////

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


// Auto registration system.
struct PluginInstallDesc
{
    const char* mpName;
    bool mRequired;
    const ::PluginDesc* mpDesc;
};
using PluginInstallDescVector = CPF::STD::Vector<PluginInstallDesc>;

#define CPF_PLUGIN_REGISTRATION_NAME(name) PluginRegistration_ ## name

template <typename NotStatic>
struct TestStaticPlugin
{
    static const ::PluginDesc* Get()
    {
        return nullptr;
    }
};

template <typename Type>
struct RegisterPlugin
{
    RegisterPlugin(PluginInstallDescVector& plugins, const char* name, bool required) { plugins.push_back(PluginInstallDesc{ name, required, Type::Get() }); }
};

#define CPF_INSTALL_PLUGIN(plugins, name) \
extern ::PluginDesc CPF_PLUGIN_REGISTRATION_NAME(name); \
struct CPF_CONCAT(IsStatic_, name)##_1; struct CPF_CONCAT(CPF_CONCAT(IsStatic_, name)##_, name)##_STATIC;\
template <> struct TestStaticPlugin<CPF_CONCAT(CPF_CONCAT(IsStatic_, name)##_, 1)> { \
    static const ::PluginDesc* Get() { return &CPF_PLUGIN_REGISTRATION_NAME(name); } }; \
struct CPF_CONCAT(name, Tester) { \
    struct CPF_CONCAT(TestStatic_, name)##_STATIC; \
    static const ::PluginDesc* Get() { return TestStaticPlugin<CPF_CONCAT(CPF_CONCAT(IsStatic_, name)##_, CPF_CONCAT(name, _STATIC))>::Get(); } }; \
RegisterPlugin<CPF_CONCAT(name, Tester)> CPF_CONCAT(RegisterObject_, name)(plugins##Plugins, CPF_STRINGIZE(name), false);

#define CPF_INSTALL_LOCAL_PLUGIN(plugins, name) \
extern ::PluginDesc CPF_PLUGIN_REGISTRATION_NAME(name); \
struct name##Tester { \
    static const ::PluginDesc* Get() { return &CPF_PLUGIN_REGISTRATION_NAME(name); } }; \
RegisterPlugin<name##Tester> RegisterObject_##name(plugins##Plugins, #name, false);


#define CPF_BEGIN_PLUGINS(name) STD::Vector<PluginInstallDesc> name##Plugins;

inline CPF::GOM::Result InstallPlugins(CPF::Plugin::iRegistry* registry, PluginInstallDescVector& plugins)
{
    CPF::GOM::Result result = CPF::GOM::kOK;
    for (const auto& plugin : plugins)
    {
        if (plugin.mpDesc)
        {
            CPF_LOG(Plugin, Info) << "Installing static plugin: " << plugin.mpName;
            result = result == CPF::GOM::kOK ? (plugin.mpDesc->Install)(registry) : result;
        }
        else
        {
            CPF_LOG(Plugin, Info) << "Loading dynamic plugin: " << plugin.mpName;
            CPF::STD::String libName("plugins/");
            libName += plugin.mpName;
            libName += ".cfp";
            const auto newResult = registry->Load(libName.c_str());
            if (plugin.mRequired)
                result = newResult;
        }
    }

    return result;
}

inline CPF::GOM::Result RemovePlugins(CPF::Plugin::iRegistry* registry, PluginInstallDescVector& plugins)
{
    CPF::GOM::Result result = CPF::GOM::kOK;
    for (auto it = plugins.rbegin(); it != plugins.rend(); ++it)
    {
        const auto& plugin = *it;
        if (plugin.mpDesc)
        {
            CPF_LOG(Plugin, Info) << "Removing static plugin: " << plugin.mpName;
            result = result == CPF::GOM::kOK ? (plugin.mpDesc->Remove)(registry) : result;
        }
        else
        {
            CPF_LOG(Plugin, Info) << "Unloading dynamic plugin: " << plugin.mpName;
            CPF::STD::String libName = plugin.mpName;
            libName = "plugins/" + libName + ".cfp";
            result = result == CPF::GOM::kOK ? registry->Unload(libName.c_str()) : result;
        }
    }
    return result;
}

#define CPF_INSTALL_PLUGINS(registry, name) InstallPlugins(registry, name##Plugins)
#define CPF_REMOVE_PLUGINS(registry, name) RemovePlugins(registry, name##Plugins)
