add_library (Application_s STATIC
	Source/Application.cpp
)
target_link_libraries (Application_s
	Core_s
)
target_include_directories (Application_s
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
set_property (TARGET Application_s PROPERTY FOLDER CPF)
