file (GLOB_RECURSE DataFiles integration_res/*)

set (HEADER_FILES
	Include/Integration.hpp
)
set (SOURCE_FILES
	Source/Integration.cpp
)

add_executable (BgfxIntegration WIN32
	${HEADER_FILES}
	${SOURCE_FILES}
	${DataFiles}
)
target_include_directories (BgfxIntegration
	PUBLIC Include
)
target_link_libraries (BgfxIntegration
	s_Concurrency
	s_SDL2
	Logging
	s_ANSI_C_FileSystem
	s_EntityService
	s_Resources
	bx
	bgfx
	bgfx_util
)
target_compile_definitions (BgfxIntegration PUBLIC)

set_property (TARGET BgfxIntegration PROPERTY FOLDER Experimental/Bgfx)


if(MSVC)
	set (targetPath /Cpf/Bgfx/Integration/integration_res)
else()
	set (targetPath /)
endif()
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/integration_res)
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/integration_res/shaders)

foreach (file ${DataFiles})
	file (RELATIVE_PATH relative ${CMAKE_CURRENT_SOURCE_DIR} ${file})
	set (target ${CMAKE_BINARY_DIR}${targetPath}/${relative})
#	message ("src: ${file}  dst: ${target}")
	add_custom_command (OUTPUT ${target}
		COMMAND ${CMAKE_COMMAND} -E copy ${file} ${target}
		MAIN_DEPENDENCY ${file}
	)
endforeach ()
source_group (Data FILES ${DataFiles})
