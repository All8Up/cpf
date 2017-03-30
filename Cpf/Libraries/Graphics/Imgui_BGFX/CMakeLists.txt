# ###############################################
set (INCLUDE_IMGUI_FILES
	Include/Imgui/imgui.h
)
set (SOURCE_IMGUI_FILES
	Source/imgui.cpp
	Source/ocornut_imgui.cpp
	Source/scintilla.cpp
	Source/ocornut-imgui/imgui.cpp
	Source/ocornut-imgui/imgui_demo.cpp
	Source/ocornut-imgui/imgui_draw.cpp
	Source/ocornut-imgui/imgui_node_graph_test.cpp
)

# ###############################################
add_library (s_Imgui_BGFX STATIC
	${INCLUDE_IMGUI_FILES}
	${SOURCE_IMGUI_FILES}
)

# ###############################################
target_compile_definitions (s_Imgui_BGFX
	PUBLIC CPF_STATIC_IMGUI_BGFX
	PRIVATE CPF_BUILD_IMGUI_BGFX
)
target_include_directories (s_Imgui_BGFX
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/Imgui>
		$<INSTALL_INTERFACE:Include/Imgui>
)
target_link_libraries (s_Imgui_BGFX
	PUBLIC
		bgfx
		s_NanoVG_BGFX
)

# ###############################################
set_property (TARGET s_Imgui_BGFX
	PROPERTY FOLDER Libraries/Static/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_IMGUI_FILES})
source_group (Sources FILES ${SOURCE_IMGUI_FILES})
