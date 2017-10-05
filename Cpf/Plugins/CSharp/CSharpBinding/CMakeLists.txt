set (INCLUDE_FILES
	Include/CSharpBindings.hpp
)
set (SOURCE_FILES
	Source/CSharpBindings.cpp
)

add_library (CSharpBindings SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_link_libraries (CSharpBindings Plugin)
set_property (TARGET CSharpBindings PROPERTY FOLDER Plugins/CSharp)

# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET CSharpBindings POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CSharpBindings> ${CPF_COMMON_PLUGINS}/CSharpBindings.cfp
)


MakeUnitTest (LIBRARY CSharpBindings GROUP CSharp
	TEST_FILES
		UnitTest/Test_All.hpp
		../../../Libraries/Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_IO s_PluginHost
)
