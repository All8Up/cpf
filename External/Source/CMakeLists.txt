# Gmock
if (NOT EXTERN_INLINE_GMOCK)
	# Detect that the binaries exist.
else ()
	if (IS_DIRECTORY "${GMOCK_SRC_DIR}")
		add_library (gmock STATIC ${GMOCK_SRC_DIR}/fused-src/gmock-gtest-all.cc)
		target_include_directories (gmock PUBLIC ${GMOCK_SRC_DIR}/fused-src)
		set_property (TARGET gmock PROPERTY FOLDER External)
	endif ()
endif ()

# Spdlog
if (NOT EXTERN_INLINE_SPDLOG)
else ()
	if (IS_DIRECTORY "${SPDLOG_SRC_DIR}")
		set (CPF_HAVE_SPDLOG 1 PARENT_SCOPE)
		set (CPF_SPDLOG_LIBRARY spdlog PARENT_SCOPE)
		add_library (spdlog INTERFACE)
		target_include_directories (spdlog
			INTERFACE
				$<BUILD_INTERFACE:${SPDLOG_SRC_DIR}/include/>
		)
	endif ()
endif ()

# Sdl2
if (NOT EXTERN_INLINE_SDL2)
else ()
	if (IS_DIRECTORY "${SDL2_SRC_DIR}")
		add_subdirectory (${SDL2_SRC_DIR})
		target_include_directories (SDL2-static PUBLIC ${SDL2_SRC_DIR}/include)
		set (BUILD_DOCUMENTATION OFF)
		set (SDL_SHARED OFF)
		set (SDL_STATIC ON)
		set (SDL_RENDER OFF)
		set (SDL_THREADS OFF)
		set (SDL_TIMERS OFF)
		set (SDL_FILE OFF)
		set (SDL_FILESYSTEM OFF)
		set_property (TARGET SDL2 PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2main PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2-static PROPERTY FOLDER External/SDL2)
		set_property (TARGET uninstall PROPERTY FOLDER External/SDL2)
	endif ()
endif ()

# Rapidjson
if (NOT EXTERN_INLINE_RAPIDJSON)
else ()
	if (IS_DIRECTORY "${RAPIDJSON_SRC_DIR}")
		add_library (rapidjson INTERFACE)
		target_include_directories (rapidjson INTERFACE $<BUILD_INTERFACE:${RAPIDJSON_SRC_DIR}/include/>)
	endif ()
endif ()

# Cereal
if (NOT EXTERN_INLINE_CEREAL)
else ()
	if (IS_DIRECTORY "${CEREAL_SRC_DIR}")
		set (CPF_HAVE_CEREAL ON PARENT_SCOPE)
		set (JUST_INSTALL_CEREAL ON CACHE BOOL "" FORCE)
		add_subdirectory (${CEREAL_SRC_DIR})
	endif ()
endif ()

# ASIO
if (NOT EXTERN_INLINE_ASIO)
else ()
	if (IS_DIRECTORY "${ASIO_SRC_DIR}")
		set (CPF_HAVE_ASIO ON PARENT_SCOPE)
		add_library (asio INTERFACE)
		target_include_directories (asio INTERFACE "${ASIO_SRC_DIR}/include")
		target_compile_definitions (asio
			INTERFACE ASIO_STANDALONE
		)
	endif ()
endif ()

# Aurora
if (NOT EXTERN_INLINE_AURORA)
else ()
	if (IS_DIRECTORY "${AURORA_SRC_DIR}")
		set (BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		set (GLFW_SYSTEM OFF CACHE BOOL "" FORCE)
		add_subdirectory (${AURORA_SRC_DIR})
		set_property (TARGET RuntimeCompiler PROPERTY FOLDER External)
		set_property (TARGET RuntimeObjectSystem PROPERTY FOLDER External)
	endif ()
endif ()

# Bx
if (NOT EXTERN_INLINE_BX)
else ()
	if (IS_DIRECTORY "${BX_SRC_DIR}")
		add_library (bx STATIC
			${BX_SRC_DIR}/src/amalgamated.cpp
		)
		target_include_directories (bx PUBLIC "${BX_SRC_DIR}/include")
		if (WIN32)
			target_include_directories (bx PUBLIC "${BX_SRC_DIR}/include/compat/msvc")
		endif ()
		set_property (TARGET bx PROPERTY FOLDER External)
	endif ()
endif ()


# Bgfx
if (NOT EXTERN_INLINE_BGFX)
else ()
	if (IS_DIRECTORY "${BGFX_SRC_DIR}")
		add_library (bgfx STATIC
			${BGFX_SRC_DIR}/src/amalgamated.cpp
		)
		target_include_directories (bgfx PUBLIC
			"${BGFX_SRC_DIR}/include"
			"${BGFX_SRC_DIR}/3rdparty"
			"${BGFX_SRC_DIR}/3rdparty/dxsdk/include"
			"${BGFX_SRC_DIR}/3rdparty/khronos"
			)
		target_link_libraries (bgfx bx SDL2)
		target_compile_definitions (bgfx PUBLIC
			BGFX_CONFIG_USE_OVR=0
			BGFX_CONFIG_RENDERER_DIRECT3D9=1
			BGFX_CONFIG_RENDERER_DIRECT3D11=1
			BGFX_CONFIG_RENDERER_DIRECT3D12=1
			BGFX_CONFIG_RENDERER_OPENGL=1
			BGFX_CONFIG_RENDERER_VULKAN=1
			)
		set_property (TARGET bgfx PROPERTY FOLDER External)

		add_library (bgfx_util STATIC
			${BGFX_SRC_DIR}/examples/common/entry/cmd.h
			${BGFX_SRC_DIR}/examples/common/entry/cmd.cpp
			${BGFX_SRC_DIR}/examples/common/entry/entry.h
			${BGFX_SRC_DIR}/examples/common/entry/entry.cpp
			${BGFX_SRC_DIR}/examples/common/entry/entry_windows.cpp
			${BGFX_SRC_DIR}/examples/common/entry/input.h
			${BGFX_SRC_DIR}/examples/common/entry/input.cpp
			${BGFX_SRC_DIR}/examples/common/debugdraw/debugdraw.h
			${BGFX_SRC_DIR}/examples/common/debugdraw/debugdraw.cpp
			${BGFX_SRC_DIR}/examples/common/font/font_manager.h
			${BGFX_SRC_DIR}/examples/common/font/font_manager.cpp
			${BGFX_SRC_DIR}/examples/common/nanovg/nanovg.h
			${BGFX_SRC_DIR}/examples/common/nanovg/nanovg.cpp
			${BGFX_SRC_DIR}/examples/common/nanovg/nanovg_bgfx.h
			${BGFX_SRC_DIR}/examples/common/nanovg/nanovg_bgfx.cpp
			${BGFX_SRC_DIR}/examples/common/ps/particle_system.h
			${BGFX_SRC_DIR}/examples/common/ps/particle_system.cpp
			${BGFX_SRC_DIR}/examples/common/bgfx_utils.h
			${BGFX_SRC_DIR}/examples/common/bgfx_utils.cpp
			${BGFX_SRC_DIR}/examples/common/bounds.h
			${BGFX_SRC_DIR}/examples/common/bounds.cpp
			${BGFX_SRC_DIR}/examples/common/camera.h
			${BGFX_SRC_DIR}/examples/common/camera.cpp
			${BGFX_SRC_DIR}/examples/common/cube_atlas.h
			${BGFX_SRC_DIR}/examples/common/cube_atlas.cpp
			${BGFX_SRC_DIR}/examples/common/image.h
			${BGFX_SRC_DIR}/examples/common/image.cpp
			${BGFX_SRC_DIR}/examples/common/packrect.h
			${BGFX_SRC_DIR}/examples/common/imgui/imgui.h
			${BGFX_SRC_DIR}/examples/common/imgui/imgui.cpp
			${BGFX_SRC_DIR}/examples/common/imgui/ocornut_imgui.h
			${BGFX_SRC_DIR}/examples/common/imgui/ocornut_imgui.cpp
			${BGFX_SRC_DIR}/examples/common/imgui/scintilla.h
			${BGFX_SRC_DIR}/examples/common/imgui/scintilla.cpp
			${BGFX_SRC_DIR}/3rdparty/ocornut-imgui/imgui.h
			${BGFX_SRC_DIR}/3rdparty/ocornut-imgui/imgui.cpp
			${BGFX_SRC_DIR}/3rdparty/ocornut-imgui/imgui_demo.cpp
			${BGFX_SRC_DIR}/3rdparty/ocornut-imgui/imgui_draw.cpp
			${BGFX_SRC_DIR}/3rdparty/ocornut-imgui/imgui_node_graph_test.cpp
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexbuffercompression.h
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexbuffercompression.cpp
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexbuffercompressionformat.h
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexbufferdecompression.h
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexbufferdecompression.cpp
			${BGFX_SRC_DIR}/3rdparty/ib-compress/indexcompressionconstants.h
			)
		target_link_libraries (bgfx_util bx bgfx)
		target_include_directories (bgfx_util PUBLIC
			"${BGFX_SRC_DIR}/examples/common"
			)
		set_property (TARGET bgfx_util PROPERTY FOLDER External)
	endif ()
endif ()
