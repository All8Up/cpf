# ###############################################
set (INCLUDE_NANOVG_FILES
	Include/NanoVG/nanovg.h
	Include/NanoVG/nanovg_bgfx.h
)
set (SOURCE_NANOVG_FILES
	Source/nanovg.cpp
	Source/nanovg_bgfx.cpp
	Source/stb.c
)

# ###############################################
add_library (s_NanoVG_BGFX STATIC
	${INCLUDE_NANOVG_FILES}
	${SOURCE_NANOVG_FILES}
)

# ###############################################
target_compile_definitions (s_NanoVG_BGFX
	PUBLIC CPF_STATIC_NANOVG_BGFX
	PRIVATE CPF_BUILD_NANOVG_BGFX
)
target_include_directories (s_NanoVG_BGFX
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/NanoVG>
		$<INSTALL_INTERFACE:Include/NanoVG>
)
target_link_libraries (s_NanoVG_BGFX
	PUBLIC
		bgfx
)

# ###############################################
set_property (TARGET s_NanoVG_BGFX
	PROPERTY FOLDER Libraries/Static/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_NANOVG_FILES})
source_group (Sources FILES ${SOURCE_NANOVG_FILES})
