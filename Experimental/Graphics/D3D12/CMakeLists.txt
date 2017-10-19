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
		i_Resources
		s_Application
		AdapterSDL2
		GraphicsDriver
		i_EntityService
		i_DebugUI
		i_Concurrency
		VTune
	)

	set_property (TARGET ExperimentalD3D12 PROPERTY FOLDER Experimental/Graphics/Adapter)
# WIN32
endif ()

add_custom_command (TARGET ExperimentalD3D12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/Experimental
	${CMAKE_BINARY_DIR}/$<CONFIG>/resources/experimental
)
source_group (Data FILES ${DataFiles})

foreach (file ${DataFiles})
	get_filename_component (ext "${file}" EXT)
	if (${ext} STREQUAL ".hlsl")
		set_source_files_properties (${file} PROPERTIES HEADER_FILE_ONLY TRUE)
	endif ()
endforeach ()
