file (GLOB_RECURSE DataFiles integration_res/*)

set (HEADER_FILES
	Include/Integration.hpp
)
set (SOURCE_FILES
	Source/Integration.cpp
)
set (SHADER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/fs_cubes.bin.h
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/vs_cubes.bin.h
)

add_executable (BgfxIntegration WIN32
	${HEADER_FILES}
	${SOURCE_FILES}
	${SHADER_FILES}
	${DataFiles}
)
target_include_directories (BgfxIntegration
	PUBLIC
		Include
		${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
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
)
target_compile_definitions (BgfxIntegration PUBLIC)

set_property (TARGET BgfxIntegration PROPERTY FOLDER Experimental/Bgfx)

function (add_shader type src varying outfile)
	if (type STREQUAL "f")
		add_custom_command (
			OUTPUT ${outfile}
			COMMAND shaderc -f ${src} -o ${outfile} --type ${type} --platform windows -p ps_5_0 -i integration_res --varyingdef ${varying} --bin2c
		)
	else ()
		add_custom_command (
			OUTPUT ${outfile}
			COMMAND shaderc -f ${src} -o ${outfile} --type ${type} --platform windows -p vs_5_0 -i integration_res --varyingdef ${varying} --bin2c
		)
	endif ()
endfunction (add_shader)

add_shader (f integration_res/fs_cubes.sc integration_res/varying.def.sc ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/fs_cubes.bin.h)
add_shader (v integration_res/vs_cubes.sc integration_res/varying.def.sc ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/vs_cubes.bin.h)


if(MSVC)
	set (targetPath /Cpf/Experimental/Bgfx/Integration)
else()
	set (targetPath /)
endif()
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/integration_res)
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/integration_res/shaders)

foreach (file ${DataFiles})
	file (RELATIVE_PATH relative ${CMAKE_CURRENT_SOURCE_DIR} ${file})
	set (target ${CMAKE_BINARY_DIR}${targetPath}/${relative})
	message ("src: ${file}  dst: ${target}")
	add_custom_command (OUTPUT ${target}
		COMMAND ${CMAKE_COMMAND} -E copy ${file} ${target}
		MAIN_DEPENDENCY ${file}
	)
endforeach ()
source_group (Data FILES ${DataFiles})
