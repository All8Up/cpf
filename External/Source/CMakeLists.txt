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
		set (BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)
		set (SDL_SHARED ON CACHE BOOL "" FORCE)
		set (SDL_STATIC OFF CACHE BOOL "" FORCE)
		set (SDL_RENDER OFF CACHE BOOL "" FORCE)
		set (SDL_THREADS OFF CACHE BOOL "" FORCE)
		set (SDL_TIMERS OFF CACHE BOOL "" FORCE)
		set (SDL_FILE OFF CACHE BOOL "" FORCE)
		set (SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
		add_subdirectory (${SDL2_SRC_DIR})
		set_property (TARGET SDL2 PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2main PROPERTY FOLDER External/SDL2)
#		set_property (TARGET SDL2-static PROPERTY FOLDER External/SDL2)
		set_property (TARGET uninstall PROPERTY FOLDER External/SDL2)
		target_include_directories (SDL2 PUBLIC ${SDL2_SRC_DIR}/include)
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

# Vulkan
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/VulkanSDK")
	add_library (vulkan INTERFACE)
	target_include_directories (vulkan INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/Source/VulkanSDK/1.0.46.0/Include")
endif ()

# jsoncons
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/jsoncons-0.99.7.2")
	add_library (jsoncons INTERFACE)
	target_include_directories (jsoncons INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Source/jsoncons-0.99.7.2/src)
endif ()

# flatbuffers
if (NOT EXTERN_INLINE_FLATBUFFERS)
else ()
	if (IS_DIRECTORY "${FLATBUFFERS_SRC_DIR}")
		set (FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
		set (FLATBUFFERS_INSTALL OFF CACHE BOOL "" FORCE)
		add_subdirectory ("${FLATBUFFERS_SRC_DIR}")
		set_property (TARGET flatbuffers PROPERTY FOLDER External)
		set_property (TARGET flatc PROPERTY FOLDER External)
		set_property (TARGET flathash PROPERTY FOLDER External)
	endif ()

endif ()

# Find installed Python 3.6.1 (or higher) for tools.
find_package (PythonLibs 3)
