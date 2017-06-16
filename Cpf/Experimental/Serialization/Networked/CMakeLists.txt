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
	MultiCore
	i_Resources
	GraphicsDriver
	s_Application
	i_DebugUI
	i_Adapter_SDL2
	i_Python3
	asio
)
set_property (TARGET Networked PROPERTY FOLDER Experimental/Serialization/Networked)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_integration/__init__.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_integration/__init__.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_integration/__init__.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_integration/__init__.py COPYONLY)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/result.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_gom/result.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/result.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_gom/result.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/classid.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_gom/classid.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/classid.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_gom/classid.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/interfaceid.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_gom/interfaceid.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/interfaceid.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_gom/interfaceid.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/methods.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_gom/methods.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/methods.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_gom/methods.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/__init__.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_gom/__init__.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_gom/__init__.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_gom/__init__.py COPYONLY)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_plugin/__init__.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_plugin/__init__.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_plugin/__init__.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_plugin/__init__.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_plugin/registry.py ${CMAKE_BINARY_DIR}/Debug/resources/networked/test_plugin/registry.py COPYONLY)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/networked/test_plugin/registry.py ${CMAKE_BINARY_DIR}/Release/resources/networked/test_plugin/registry.py COPYONLY)

foreach (file ${DataFiles})
	file (RELATIVE_PATH relative ${CMAKE_CURRENT_SOURCE_DIR}/networked ${file})
	set (groupName "Data/${relative}")
	get_filename_component (group ${groupName} DIRECTORY)
	string (REPLACE "/" "\\\\" group ${group})
	source_group (${group} FILES ${file})
endforeach ()

foreach (file ${DataFiles})
	get_filename_component (ext "${file}" EXT)
	if (${ext} STREQUAL ".hlsl")
		set_source_files_properties (${file} PROPERTIES HEADER_FILE_ONLY TRUE)
	endif ()
endforeach ()
