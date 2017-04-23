# ###############################################
set (INCLUDE_FILES
)
set (INCLUDE_SCENE_FILES
)
set (INTERFACE_FILES
)

set (SOURCE_FILES
	Source/Scene.cpp
)

# ###############################################
add_library (Scene SHARED
	${INCLUDE_FILES}
	${INCLUDE_Scene_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
)
target_include_directories (Scene
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (Scene
	PUBLIC
		Configuration Plugin
)
set_property (TARGET Scene PROPERTY FOLDER Plugins/Graphics)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Scene POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Scene> ${CPF_COMMON_PLUGINS}/Scene.cfp
)

# ###############################################
add_library (i_Scene INTERFACE)
target_include_directories (i_Scene
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
