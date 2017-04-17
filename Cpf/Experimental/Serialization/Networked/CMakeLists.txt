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
	s_Resources
	s_GraphicsDriver
	i_Application
	i_Adapter_SDL2
	cereal
	asio
)
set_property (TARGET Networked PROPERTY FOLDER Experimental/Serialization/Networked)

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
