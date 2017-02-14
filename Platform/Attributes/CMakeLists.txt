# ###############################################
set (INCLUDE_FILES
	Include/Attributes/Attributes.hpp
)
set (SOURCE_FILES
	Source/Attributes.cpp
)

add_library (s_Attributes STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (s_Attributes
	PUBLIC CPF_STATIC_ATTRIBUTES
	PRIVATE CPF_BUILD_ATTRIBUTES
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

target_link_libraries (s_Attributes Configuration s_Collections s_Math)

target_include_directories (s_Attributes PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property (TARGET s_Attributes PROPERTY FOLDER Libraries/Static/Platform)

install (DIRECTORY Include/Attributes
	DESTINATION Include/Attributes
	PATTERN *
)


install (TARGETS s_Attributes
	EXPORT AttributesConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT AttributesConfig DESTINATION CMake)


# ###############################################
MakeUnitTests (LIBRARY Attributes:static GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Attributes.hpp
		../../UnitTesting/Source/Main.cpp
)
