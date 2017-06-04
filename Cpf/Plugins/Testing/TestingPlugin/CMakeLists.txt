# ###############################################
set (INCLUDE_FILES
	Include/Test.hpp
)
set (INTERFACE_FILES
	Interface/iTest.hpp
)
set (SOURCE_FILES
	Source/Test.cpp
)

# ###############################################
add_library (TestingPlugin SHARED
	${INCLUDE_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
)
target_include_directories (TestingPlugin
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
target_link_libraries (TestingPlugin
	PUBLIC
		Configuration Plugin Logging
)
set_property (TARGET TestingPlugin PROPERTY FOLDER Plugins/Testing)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET TestingPlugin POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestingPlugin> ${CPF_COMMON_PLUGINS}/TestingPlugin.cfp
)

# ###############################################
add_library (i_TestingPlugin INTERFACE)
target_include_directories (i_TestingPlugin
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
