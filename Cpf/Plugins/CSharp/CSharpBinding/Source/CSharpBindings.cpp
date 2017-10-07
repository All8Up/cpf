//////////////////////////////////////////////////////////////////////////
#include "Plugin/iRegistry.hpp"
#include "IPlugin.hpp"

#using <system.dll>

using namespace System::Diagnostics;
using namespace CPF;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Reflection;
using namespace System::IO;

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

bool LoadPlugin()
{
	auto dir = Directory::GetCurrentDirectory();
	Trace::WriteLine(dir);
	Assembly^ assembly = Assembly::LoadFrom("../../../../Debug/Bin/TestCSharp_d.dll");
	auto ipluginType = IPlugin::typeid;
	for each(auto type in assembly->GetTypes())
	{
		//auto interfaces = ipluginType->GetInterfaces;

		//if(interfaces->Count > 0)
		{
			
		}
		if (ipluginType->IsAssignableFrom(type) && ipluginType != type)
		{
			ManagedGlobals::pluginInstance = (IPlugin^)Activator::CreateInstance(type);
			return true;
		}
	}

	return false;
}

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry && LoadPlugin())
	{
		IntPtr intPtr(registry);
		return ManagedGlobals::pluginInstance->Install(intPtr);
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