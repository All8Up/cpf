# ###############################################
set (INCLUDE_FILES
	Include/SimdX.hpp
)

set (SIMD_INCLUDE_FILES
	Include/Simd/Float32x4.hpp
	Include/Simd/Float32x4_RefOne.hpp
)

add_library (SimdX INTERFACE
)
target_link_libraries (SimdX INTERFACE Configuration)

target_include_directories (SimdX
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

add_custom_target (SimdX_IDE SOURCES
	${INCLUDE_FILES}
	${SIMD_INCLUDE_FILES}
)

set_property (TARGET SimdX_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\SimdX FILES ${SIMD_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY SimdX GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
