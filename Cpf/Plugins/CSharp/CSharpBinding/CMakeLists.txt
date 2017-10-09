set (INTERFACE_FILES
	Interface/IPlugin.hpp
)

add_library (i_CSharpBinding INTERFACE)
target_include_directories (i_CSharpBinding
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

add_library (CSharpBindings SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${INTERFACE_FILES}
)
target_link_libraries (CSharpBindings i_CSharpBinding Plugin)
set_property (TARGET CSharpBindings PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")
target_include_directories (CSharpBindings
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
set_property (TARGET CSharpBindings PROPERTY FOLDER Plugins/CSharp)

MakeUnitTest (LIBRARY CSharpBindings GROUP CSharp
	TEST_FILES
		UnitTest/Test_All.hpp
		../../../Libraries/Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_IO s_PluginHost i_TestCSharp
)


# ###############################################
set_target_properties (CSharpBindings PROPERTIES COMPILE_FLAGS "/clr")
set_target_properties (CSharpBindings PROPERTIES LINK_FLAGS_DEBUG "/ASSEMBLYDEBUG")
string (REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string (REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string (REPLACE "/GR-" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
