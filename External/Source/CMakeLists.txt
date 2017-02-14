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
		set_property (TARGET SDL2 PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2main PROPERTY FOLDER External/SDL2)
		set_property (TARGET SDL2-static PROPERTY FOLDER External/SDL2)
		set_property (TARGET DOCUMENTATION PROPERTY FOLDER External/SDL2)
		set_property (TARGET uninstall PROPERTY FOLDER External/SDL2)
	endif ()
endif ()

# Rapidjson
if (NOT EXTERN_INLINE_RAPIDJSON)
else ()
	if (IS_DIRECTORY "${RAPIDJSON_SRC_DIR}")
#		add_subdirectory (${RAPIDJSON_SRC_DIR})
		add_library (rapidjson INTERFACE)
		target_include_directories (rapidjson INTERFACE $<BUILD_INTERFACE:${RAPIDJSON_SRC_DIR}/include/>)
	endif ()
endif ()
