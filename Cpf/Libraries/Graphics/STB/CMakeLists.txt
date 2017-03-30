# ###############################################
set (INCLUDE_STB_FILES
	Include/STB/STB.h
)
set (SOURCE_STB_FILES
	Source/STB.c
)

# ###############################################
add_library (s_STB STATIC
	${INCLUDE_STB_FILES}
	${SOURCE_STB_FILES}
)

# ###############################################
target_compile_definitions (s_STB
	PUBLIC CPF_STATIC_STB
	PRIVATE CPF_BUILD_STB
)
target_include_directories (s_STB
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
set_property (TARGET s_STB
	PROPERTY FOLDER Libraries/Static/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_STB_FILES})
source_group (Sources FILES ${SOURCE_STB_FILES})
