set (INCLUDE_FILES
	Include/CPF/Application.hpp
)
set (SOURCE_FILES
	Source/Application.cpp
)

add_library (Application_s STATIC
	${APPLICATION_GEN_INCLUDES}
	${APPLICATION_IDL}
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_link_libraries (Application_s
	Core_s
	gflags_static
)
target_include_directories (Application_s
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
set_property (TARGET Application_s PROPERTY FOLDER CPF)

source_group (Include FILES ${INCLUDE_FILES} ${APPLICATION_GEN_INCLUDES})
source_group (Source FILES ${SOURCE_FILES})
