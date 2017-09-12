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
		set (SDL_FILE ON CACHE BOOL "" FORCE)
		set (SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
		add_subdirectory (${SDL2_SRC_DIR})
		set_property (TARGET SDL2 PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2main PROPERTY FOLDER External/SDL2)
#		set_property (TARGET SDL2-static PROPERTY FOLDER External/SDL2)
		set_property (TARGET uninstall PROPERTY FOLDER External/SDL2)
		target_include_directories (SDL2 PUBLIC ${SDL2_SRC_DIR}/include)
		target_compile_options (SDL2 PRIVATE /wd4267 /wd4018 /wd4311)
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
	target_compile_definitions (jsoncons INTERFACE JSONCONS_NO_DEPRECATED)
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

# Add the utility modules directory for external libraries.
LIST (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source/Modules")

# gflags
set (BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_PACKAGING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_LIB ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_nothreads_LIB OFF CACHE BOOL "" FORCE)
set (GFLAGS_INSTALL_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Source/gflags-2.2.1")
set_property (TARGET gflags_static PROPERTY FOLDER External/gflags-2.2.1)
target_compile_options (gflags_static PRIVATE /wd4127 /wd4100 /wd4459)

# glog
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Source/glog-0.3.5")
set_property (TARGET glog PROPERTY FOLDER External/glog-0.3.5)
target_compile_options (glog PRIVATE /wd4722 /wd4267 /wd4100 /wd4505)

# gtest
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Source/googletest-release-1.8.0")
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set_property (TARGET gmock PROPERTY FOLDER External/gtest-1.8.0)
set_property (TARGET gmock_main PROPERTY FOLDER External/gtest-1.8.0)
set_property (TARGET gtest PROPERTY FOLDER External/gtest-1.8.0)
set_property (TARGET gtest_main PROPERTY FOLDER External/gtest-1.8.0)

# benchmark
if (CPF_ENABLE_BENCHMARKS)
	set (BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Source/benchmark-1.2.0")
	set_property (TARGET benchmark PROPERTY FOLDER External/benchmark-1.2.0)
	target_compile_options (benchmark PRIVATE /wd4722)
endif ()
