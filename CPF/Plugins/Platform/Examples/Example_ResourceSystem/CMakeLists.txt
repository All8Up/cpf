# Setup data files.
# TODO: Most of this can be put in a common cmake function.
file (GLOB_RECURSE DataFiles examples_resourcesapp/*)

# Make the example app.
add_executable (Example_ResourceSystem
	${TEST_INCLUDES}
	Source/Main.cpp
	${DataFiles}
)
target_link_libraries (Example_ResourceSystem
	Core_s Application_s
)
set_property (TARGET Example_ResourceSystem PROPERTY FOLDER Examples/Basics)

# Add the data copy command.
add_custom_command (TARGET Example_ResourceSystem POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/examples_resourcesapp
	${CMAKE_BINARY_DIR}/$<CONFIG>/resources/examples_resourcesapp
)
source_group (Data FILES ${DataFiles})

foreach (file ${DataFiles})
	get_filename_component (ext "${file}" EXT)
	if (${ext} STREQUAL ".hlsl")
		set_source_files_properties (${file} PROPERTIES HEADER_FILE_ONLY TRUE)
	endif ()
endforeach ()
