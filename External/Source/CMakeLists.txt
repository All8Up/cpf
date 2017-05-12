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

# Vulkan
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/VulkanSDK")
	add_library (vulkan INTERFACE)
	target_include_directories (vulkan INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/Source/VulkanSDK/1.0.46.0/Include")
endif ()

# Rttr
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/Rttr-master")
	set (BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
	set (USE_PCH OFF CACHE BOOL "" FORCE)
	set (BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
	set (BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	set (BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)
	set (BUILD_INSTALLER OFF CACHE BOOL "" FORCE)
	set (BUILD_PACKAGE OFF CACHE BOOL "" FORCE)
	set (CUSTOM_DOXYGEN_STYLE OFF CACHE BOOL "" FORCE)
	add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Source/Rttr-master)
	set_property (TARGET rttr_core PROPERTY FOLDER External)
endif ()

# jsoncons
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/jsoncons-0.99.7.2")
	add_library (jsoncons INTERFACE)
	target_include_directories (jsoncons INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Source/jsoncons-0.99.7.2/src)
endif ()

#find_package (PythonLibs 3)
