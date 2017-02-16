file (GLOB_RECURSE DataFiles Experimental/*)

set (HEADER_FILES
	Include/ExperimentalD3D12.hpp
)
set (SOURCE_FILES
	Source/ExperimentalD3D12.cpp
	Source/Window.cpp
	Source/WorkerData.cpp
	Source/Rendering.cpp
	Source/Device.cpp
	Source/Resources.cpp
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
		s_Concurrency
		s_SDL2
		Logging
		s_ANSI_C_FileSystem
		s_GO
		s_Resources
		s_GraphicsDriver
		s_AdapterD3D12
	)
	target_compile_definitions (ExperimentalD3D12 PUBLIC -DGFX_ADAPTER=D3D12 )

	set_property (TARGET ExperimentalD3D12 PROPERTY FOLDER Experimental/Graphics/Adapter)
# WIN32
endif ()

#[[
if (WIN32 OR UNIX AND NOT APPLE)
	add_executable (ExperimentalVulkan WIN32
		${HEADER_FILES}
		${SOURCE_FILES}
	)
	target_include_directories (ExperimentalVulkan
		PUBLIC Include
	)
	target_link_libraries (ExperimentalVulkan
		s_PlatformLib
		s_Concurrency
		s_SDL2
		Logging
		s_ANSI_C_FileSystem
		s_GraphicsDriver
		s_GraphicsFactory
		s_AdaptersVulkan
	)
	target_compile_definitions (ExperimentalVulkan PUBLIC -DGFX_ADAPTER=Vulkan )

	set_property (TARGET ExperimentalVulkan PROPERTY FOLDER Experimental/Graphics/Adapters)
# WIN32
endif ()
]]#


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

#[[
if (WIN32)
	add_custom_command (TARGET ExperimentalD3D12 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${EXTERNAL_DIR}/bin/windows/lib64/nvToolsExt64_1.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	)
endif ()
]]#
