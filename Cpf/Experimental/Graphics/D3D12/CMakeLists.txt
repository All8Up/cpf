file (GLOB_RECURSE DataFiles Experimental/*)

set (HEADER_FILES
	Include/ExperimentalD3D12.hpp
	Include/Instance.hpp
	Include/RenderSystem.hpp
	Include/MovementSystem.hpp
	Include/InstanceSystem.hpp
)
set (SOURCE_FILES
	Source/ExperimentalD3D12.cpp
	Source/Window.cpp
	Source/WorkerData.cpp
	Source/Rendering.cpp
	Source/Device.cpp
	Source/Resources.cpp
	Source/DebugUI.cpp
	Source/RenderSystem.cpp
	Source/MovementSystem.cpp
	Source/InstanceSystem.cpp
)

if (WIN32)
	add_executable (ExperimentalD3D12 WIN32
		${HEADER_FILES}
		${SOURCE_FILES}
		${DataFiles}
	)
	target_include_directories (ExperimentalD3D12
		PUBLIC Include
	)

	target_link_libraries (ExperimentalD3D12
		s_SDL2
		s_ANSI_C_FileSystem

		s_Resources
		s_GraphicsDriver

#		s_Concurrency
#		s_EntityService
		EntityService_Interface
		Concurrency
	)

	target_compile_definitions (ExperimentalD3D12 PUBLIC -DGFX_ADAPTER=D3D12)

	set_property (TARGET ExperimentalD3D12 PROPERTY FOLDER Experimental/Graphics/Adapter)
# WIN32
endif ()


if(MSVC)
	set (targetPath /Cpf/Experimental/Graphics/D3D12)
else()
	set (targetPath /)
endif()
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/Experimental)
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/Experimental/shaders)

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

# ############################################
if(MSVC)
	set (targetPath ${CMAKE_BINARY_DIR}/Cpf/Experimental/Graphics/D3D12)
else()
	set (targetPath test/)
endif()
file (MAKE_DIRECTORY ${targetPath}/plugins)
add_custom_command (
	TARGET ExperimentalD3D12 POST_BUILD
	DEPENDS AllPlugins
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:EntityService> ${targetPath}/plugins/EntityService.cfp
)
add_custom_command (
	TARGET ExperimentalD3D12 POST_BUILD
	DEPENDS AllPlugins
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MultiCore> ${targetPath}/plugins/MultiCore.cfp
)
add_custom_command (
	TARGET ExperimentalD3D12 POST_BUILD
	DEPENDS AllPlugins
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AdapterD3D12> ${targetPath}/plugins/AdapterD3D12.cfp
)
