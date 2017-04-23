# ###############################################
set (INCLUDE_FILES
)
set (INCLUDE_RENDERER_FILES
)
set (INTERFACE_FILES
)

set (SOURCE_FILES
	Source/Renderer.cpp
)

# ###############################################
add_library (Renderer SHARED
	${INCLUDE_FILES}
	${INCLUDE_RENDERER_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
)
target_include_directories (Renderer
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (Renderer
	PUBLIC
		Configuration Plugin
)
set_property (TARGET Renderer PROPERTY FOLDER Plugins/Graphics)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Renderer POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Renderer> ${CPF_COMMON_PLUGINS}/Renderer.cfp
)

# ###############################################
add_library (i_Renderer INTERFACE)
target_include_directories (i_Renderer
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
