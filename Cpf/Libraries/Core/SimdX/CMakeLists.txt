# ###############################################
set (INCLUDE_FILES
	Include/SimdX.hpp
)

set (SIMD_INCLUDE_FILES
	Include/SIMD/Types.hpp
	Include/SIMD/Vector2.hpp
	Include/SIMD/Vector3.hpp
	Include/SIMD/Vector4.hpp
)
set (SIMD_DETAIL_INCLUDE_FILES
	Include/SIMD/Detail/Ref32x4_1.hpp
	Include/SIMD/Detail/Ref32x4_2.hpp
	Include/SIMD/Detail/Ref32x4_3.hpp
	Include/SIMD/Detail/Ref32x4_4.hpp
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
		UnitTest/Test_F32x4_1.cpp
		UnitTest/Test_F32x4_2.cpp
		UnitTest/Test_F32x4_3.cpp
		UnitTest/Test_F32x4_4.cpp
		UnitTest/Test_Vector2.cpp
		UnitTest/Test_Vector3.cpp
		UnitTest/Test_Vector4.cpp
		../Test/UnitTestMain.cpp
)
