add_library (TestCSharp SHARED
	AssemblyInfo.cs
	TestCSharp.cs
	IRegistry.cs
	IClassInstance.cs
	MyClassInstance.cs
	Unknown.cs
	IUnknown.cs
# Adding the following changes the compile type, need to
# figure out what properties to use to force managed assembly builds.
#	Test.cpp
)
set_property(TARGET TestCSharp PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
	"mscorlib"
    "System"
    "System.Core"
    "System.Data"
    "System.Runtime.InteropServices"
)
target_link_libraries (TestCSharp CSharpBindings)
set_property (TARGET TestCSharp PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")
set_property (TARGET TestCSharp PROPERTY FOLDER Plugins/CSharp)

add_library (i_TestCSharp INTERFACE)
target_include_directories (i_TestCSharp
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
# Copy as a plugin.
# NOTE: This will be in the plugin directory. Support will be added
# to update the dll search paths so this will load appropriately.
add_custom_command (TARGET TestCSharp POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestCSharp> ${CPF_COMMON_PLUGINS}/TestCSharp.dll
)

#[[
NOTE: I think this needs to look at: https://msdn.microsoft.com/en-us/library/x0w2664k.aspx
and attempt to merge the binding and the C# into the same dll.  This assumes CMake will accept
a mixed assembly.

Add whatever is needed into the "add_library" and it should work.  The only
exception is if WPF is needed, then some additional support will be required
via the "include(CSharpUtilities)" module. The references are incomplete,
add more as needed.

Generally speaking, if C# pans out, I will likely be looking at using
https://github.com/picoe/Eto as a cross platform windowing solution to
write editor and tools items.  I'll also likely drop Python support in
favor of this as I really dislike Python no matter how common it is as
an extension language.
#]]
