# ###############################################
set (INTERFACE_FILES
	Interface/iDebugUI.hpp
)

set (INCLUDE_FILES
	Include/DebugUI.hpp
)
set (SOURCE_FILES
	Source/DebugUI.cpp
)
set (SOURCE_IMGUI_FILES
	Source/imgui/imconfig.h
	Source/imgui/imgui.cpp
	Source/imgui/imgui.h
	Source/imgui/imgui_demo.cpp
	Source/imgui/imgui_draw.cpp
	Source/imgui/imgui_internal.h
	Source/imgui/stb_image.h
	Source/imgui/stb_image.cpp
	Source/imgui/stb_textedit.h
	Source/imgui/stb_truetype.h
	Source/imgui/stb_rect_pack.h
)

# ###############################################
add_library (DebugUI SHARED
	${INCLUDE_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
	${SOURCE_IMGUI_FILES}
)
target_include_directories (DebugUI
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
target_link_libraries (DebugUI
	PUBLIC
		Configuration Std Plugin Math GraphicsDriver Logging i_Application s_IO i_Resources
)
set_property (TARGET DebugUI PROPERTY FOLDER Plugins/Graphics)
source_group (Sources\\Graphics\\imgui FILES ${SOURCE_IMGUI_FILES})


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET DebugUI POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DebugUI> ${CPF_COMMON_PLUGINS}/DebugUI.cfp
)

# ###############################################
add_library (i_DebugUI INTERFACE)
target_include_directories (i_DebugUI
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
