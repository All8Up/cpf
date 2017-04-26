# ###############################################
set (INTERFACE_FILES
	Interface/iRenderSystem.hpp
	Interface/iRenderable.hpp
)

set (INCLUDE_FILES
	Include/RenderSystem.hpp
	Include/Renderable.hpp
)
set (SOURCE_FILES
	Source/RenderSystem.cpp
	Source/Renderable.cpp
	Source/Plugin.cpp
)

# ###############################################
add_library (RenderSystem SHARED
	${INCLUDE_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
)
target_include_directories (RenderSystem
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
target_link_libraries (RenderSystem
	PUBLIC
		Configuration Plugin i_MultiCore i_Concurrency i_EntityService
)
set_property (TARGET RenderSystem PROPERTY FOLDER Plugins/Graphics)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET RenderSystem POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:RenderSystem> ${CPF_COMMON_PLUGINS}/RenderSystem.cfp
)

# ###############################################
add_library (i_RenderSystem INTERFACE)
target_include_directories (i_RenderSystem
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
