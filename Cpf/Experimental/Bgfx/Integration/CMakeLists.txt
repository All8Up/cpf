file (GLOB_RECURSE DataFiles integration_res/*)

set (HEADER_FILES
	Include/Integration.hpp
)
set (SOURCE_FILES
	Source/Integration.cpp
)
set (SHADER_FILES
	Shaders/bgfx_shader.sh
	Shaders/common.sh
	Shaders/shaderlib.sh
	Shaders/varying.def.sc
	Shaders/fs_cubes.sc
	Shaders/vs_cubes.sc
)

set (DataFiles ${DataFiles}
	${CMAKE_CURRENT_SOURCE_DIR}/integration_res/fs_cubes.sc.bin
	${CMAKE_CURRENT_SOURCE_DIR}/integration_res/vs_cubes.sc.bin
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
	Logging
	s_ANSI_C_FileSystem
	s_Resources
	i_Application
	i_Adapter_SDL2
	s_Application
	Math
	bx
	bgfx
	s_NanoVG_BGFX
	s_Imgui_BGFX
	Concurrency
	EntityService_Interface
)
target_compile_definitions (BgfxIntegration
	PUBLIC
		-DCPF_COMMON_RESOURCES="${CPF_COMMON_RESOURCES}"
		-DCPF_COMMON_PLUGINS="${CPF_COMMON_PLUGINS}"
)

source_group (Shaders FILES ${SHADER_FILES})
set_property (TARGET BgfxIntegration PROPERTY FOLDER Experimental/Bgfx)

function (add_shader type src varying outfile)
	if (type STREQUAL "f")
		add_custom_command (
			OUTPUT ${outfile}
			COMMAND shaderc -f ${src} -o ${outfile} --type ${type} --platform windows -p ps_5_0 -i ${CMAKE_CURRENT_SOURCE_DIR}/Shaders --varyingdef ${varying}
		)
	else ()
		add_custom_command (
			OUTPUT ${outfile}
			COMMAND shaderc -f ${src} -o ${outfile} --type ${type} --platform windows -p vs_5_0 -i ${CMAKE_CURRENT_SOURCE_DIR}/Shaders --varyingdef ${varying}
		)
	endif ()
endfunction (add_shader)

add_shader (f ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/fs_cubes.sc ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/varying.def.sc ${CMAKE_CURRENT_SOURCE_DIR}/integration_res/fs_cubes.sc.bin)
add_shader (v ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/vs_cubes.sc ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/varying.def.sc ${CMAKE_CURRENT_SOURCE_DIR}/integration_res/vs_cubes.sc.bin)


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
#	message ("src: ${file}  dst: ${target}")
	add_custom_command (OUTPUT ${target}
		COMMAND ${CMAKE_COMMAND} -E copy ${file} ${target}
		MAIN_DEPENDENCY ${file}
	)
endforeach ()
source_group (Data FILES ${DataFiles})
