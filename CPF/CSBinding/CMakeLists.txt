set (INTERFACE_FILES
	Interface/IPlugin.hpp
)

add_library (i_CSBinding INTERFACE)
target_include_directories (i_CSBinding
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
set (INCLUDE_FILES
	Include/CSharpBindings.hpp
)
set (SOURCE_FILES
	Source/CSharpBindings.cpp
	Source/AssemblyInfo.cpp
)

add_library (CSBinding SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${INTERFACE_FILES}
)
target_link_libraries (CSBinding i_CSBinding)
target_compile_definitions (CSBinding PUBLIC _WINDLL _UNICODE UNICODE)
target_include_directories (CSBinding
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
set_property (TARGET CSBinding PROPERTY FOLDER CPF)


# ###############################################
target_compile_options(CSBinding PRIVATE /clr)
target_compile_options(CSBinding PRIVATE /Fa$(IntDir))
target_compile_options(CSBinding PRIVATE /fp:precise)
set_property(TARGET CSBinding PROPERTY VS_GLOBAL_ROOTNAMESPACE CSBinding)
set_property(TARGET CSBinding PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")
set_property(TARGET CSBinding PROPERTY VS_GLOBAL_CLRSupport "true")
set_property(TARGET CSBinding PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")

set_property(TARGET CSBinding PROPERTY VS_DOTNET_REFERENCES
	"mscorlib"
	"System"
	"System.Core"
	"System.Data"
	"System.Xml"
	"System.Runtime.InteropServices"
)

set_target_properties (CSBinding PROPERTIES LINK_FLAGS_DEBUG "/ASSEMBLYDEBUG")
set_target_properties (CSBinding PROPERTIES LINK_FLAGS_DEBUG "/ASSEMBLYDEBUG")
string (REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string (REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string (REPLACE "/GR-" "/GR" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
