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
		s_ANSI_C_FileSystem
		s_Resources
		i_Application
		i_Adapter_SDL2
		s_GraphicsDriver
		EntityService_Interface
		Concurrency
	)

	target_compile_definitions (ExperimentalD3D12
		PUBLIC
			-DGFX_ADAPTER=D3D12
			-DCPF_COMMON_RESOURCES="${CPF_COMMON_RESOURCES}"
			-DCPF_COMMON_PLUGINS="${CPF_COMMON_PLUGINS}"
	)

	set_property (TARGET ExperimentalD3D12 PROPERTY FOLDER Experimental/Graphics/Adapter)
# WIN32
endif ()

foreach (config ${CMAKE_CONFIGURATION_TYPES})
	foreach (file ${DataFiles})
		file (RELATIVE_PATH relative ${CMAKE_CURRENT_SOURCE_DIR} ${file})
		set (target "${CMAKE_BINARY_DIR}/${config}/resources/${relative}")
		message ("src: ${file}  dst: ${target}")
		add_custom_command (OUTPUT ${target}
			COMMAND ${CMAKE_COMMAND} -E copy ${file} ${target}
			MAIN_DEPENDENCY ${file}
		)
	endforeach ()
endforeach ()
source_group (Data FILES ${DataFiles})
