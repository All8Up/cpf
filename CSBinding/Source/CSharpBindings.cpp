//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/GOM/ResultCodes.hpp"

#using <system.dll>

using namespace System::Diagnostics;
using namespace CPF;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Reflection;
using namespace System::IO;

public class PluginDesc
{
	IntPtr Install;
	IntPtr Remove;
};

public interface class IPlugin
{
	UInt32 Install(IntPtr registryPtr);
	UInt32 Uninstall(IntPtr registryPtr);
};

ref class ManagedGlobals
{
public:
	static IPlugin^ pluginInstance = nullptr;
};

extern "C"
bool CPF_EXPORT_ATTR CPF_STDCALL LoadCSharpPlugin(Plugin::iRegistry* regy, const char* name)
{
	auto dir = Directory::GetCurrentDirectory();
	Trace::WriteLine(dir);
	try
	{
		System::String^ dllName = gcnew System::String(name);
		Assembly^ assembly = Assembly::LoadFrom(dllName);
		auto ipluginType = IPlugin::typeid;
		for each(auto type in assembly->GetTypes())
		{
			auto isAssignable = ipluginType->IsAssignableFrom(type);
			auto isPluginType = ipluginType != type;
			if (isAssignable && isPluginType)
			{
				ManagedGlobals::pluginInstance = (IPlugin^)Activator::CreateInstance(type);
				return true;
			}
		}
	}
	catch (...)
	{ }

	return false;
}

extern "C"
GOM::Result CPF_EXPORT_ATTR CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry && LoadCSharpPlugin(nullptr, ""))
	{
		IntPtr intPtr(registry);
		return ManagedGlobals::pluginInstance->Install(intPtr);
	}

	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT_ATTR CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
