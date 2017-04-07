# ###############################################
set (INCLUDE_FILES
	Include/Imgui.hpp
)
set (SOURCE_FILES
	Source/Imgui.cpp
)

# ###############################################
add_library (Imgui SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (Imgui
	PRIVATE CPF_BUILD_IMGUI
)
target_include_directories (Imgui
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (Imgui
	LINK_PUBLIC
		Configuration s_Collections Plugin COM Logging Hash EntityService_Interface s_Imgui_BGFX
)
set_property (TARGET Imgui PROPERTY FOLDER Libraries/Plugin/Game)

# ###############################################
add_library (Imgui_Interface INTERFACE)
target_include_directories (Imgui_Interface
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
