file (GLOB_RECURSE DataFiles networked/*)

set (HEADER_FILES
	Include/Networked.hpp
	Include/NetworkSystem.hpp
	Include/RenderSystem.hpp
)
set (SOURCE_FILES
	Source/Networked.cpp
	Source/NetworkSystem.cpp
	Source/RenderSystem.cpp
)

add_executable (Networked WIN32
	${HEADER_FILES}
	${SOURCE_FILES}
	${DataFiles}
)
target_include_directories (Networked
	PUBLIC Include
)
target_link_libraries (Networked
	Logging
	s_ANSI_C_FileSystem
	s_MultiCore
	s_SDL2
	s_Resources
	s_AdapterD3D12
	cereal
	asio
)

set_property (TARGET Networked PROPERTY FOLDER Experimental/Serialization/Networked)

if(MSVC)
	set (targetPath /Cpf/Experimental/Serialization/Networked)
else()
	set (targetPath /)
endif()
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/networked)
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}${targetPath}/networked/shaders)

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
