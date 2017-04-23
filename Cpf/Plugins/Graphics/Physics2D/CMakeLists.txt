# ###############################################
set (INCLUDE_FILES
)
set (INCLUDE_PHYSICS2D_FILES
)
set (INTERFACE_FILES
)

set (SOURCE_FILES
	Source/Physics2D.cpp
)

# ###############################################
add_library (Physics2D SHARED
	${INCLUDE_FILES}
	${INCLUDE_PHYSICS2D_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
)
target_include_directories (Physics2D
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (Physics2D
	PUBLIC
		Configuration Plugin
)
set_property (TARGET Physics2D PROPERTY FOLDER Plugins/Graphics)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Physics2D POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Physics2D> ${CPF_COMMON_PLUGINS}/Physics2D.cfp
)

# ###############################################
add_library (i_Physics2D INTERFACE)
target_include_directories (i_Physics2D
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
