# jsoncons
add_library (jsoncons INTERFACE)
target_include_directories (jsoncons INTERFACE ${CMAKE_CURRENT_LIST_DIR}/External/jsoncons-0.100.2/include)
target_compile_definitions (jsoncons INTERFACE JSONCONS_NO_DEPRECATED)
if (MSVC)
	target_compile_options (jsoncons INTERFACE /wd4189 /wd4100 )
endif ()

add_subdirectory (RayTracer)
