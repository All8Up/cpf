# ###############################################
set (INCLUDE_FILES
	Include/SimdX.hpp
)

set (SIMD_INCLUDE_FILES
	Include/SIMD/Types.hpp
	Include/SIMD/Float32x4.hpp
)
set (SIMD_DETAIL_INCLUDE_FILES
	Include/SIMD/Detail/F32x4_Ref1.hpp
	Include/SIMD/Detail/F32x4_Ref2.hpp
	Include/SIMD/Detail/F32x4_Ref3.hpp
)
set (SIMD_DETAIL_REFERENCE_INCLUDE_FILES
	Include/SIMD/Detail/Reference/F32x4.hpp
	Include/SIMD/Detail/Reference/I32x4.hpp
)
set (SIMD_DETAIL_SSE4_1_INCLUDE_FILES
	Include/SIMD/Detail/SSE4_1/F32x4.hpp
	Include/SIMD/Detail/SSE4_1/I32x4.hpp
)

add_library (SimdX INTERFACE)
target_link_libraries (SimdX INTERFACE Configuration)

target_include_directories (SimdX
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

add_custom_target (SimdX_IDE SOURCES
	${INCLUDE_FILES}
	${SIMD_INCLUDE_FILES}
	${SIMD_DETAIL_INCLUDE_FILES}
	${SIMD_DETAIL_REFERENCE_INCLUDE_FILES}
	${SIMD_DETAIL_SSE4_1_INCLUDE_FILES}
)

set_property (TARGET SimdX_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\SimdX FILES ${SIMD_INCLUDE_FILES})
source_group (Interface\\SimdX\\Detail FILES ${SIMD_DETAIL_INCLUDE_FILES})
source_group (Interface\\SimdX\\Detail\\Reference FILES ${SIMD_DETAIL_REFERENCE_INCLUDE_FILES})
source_group (Interface\\SimdX\\Detail\\SSE4_1 FILES ${SIMD_DETAIL_SSE4_1_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY SimdX GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
