# ###############################################
set (INCLUDE_FILES
	Include/SIMD.hpp
)

set (SIMD_INCLUDE_FILES
	Include/SIMD/Types.hpp
	Include/SIMD/Rounding.hpp
)
set (SIMD_DETAIL_INCLUDE_FILES
	Include/SIMD/Detail/Accessor.hpp
	Include/SIMD/Detail/LaneIndex.hpp
	Include/SIMD/Detail/LaneRef.hpp
	Include/SIMD/Detail/LaneRef_1.inl
	Include/SIMD/Detail/LaneRef_2.inl
	Include/SIMD/Detail/LaneRef_3.inl
	Include/SIMD/Detail/LaneRef_4.inl
	Include/SIMD/Detail/Swizzles.hpp
)
set (SIMD_DETAIL_FPU_INCLUDE_FILES
	Include/SIMD/Detail/FPU/Bool4.hpp
	Include/SIMD/Detail/FPU/F32x1.hpp
	Include/SIMD/Detail/FPU/F32x2.hpp
	Include/SIMD/Detail/FPU/F32x3.hpp
	Include/SIMD/Detail/FPU/F32x4.hpp
	Include/SIMD/Detail/FPU/FPU.hpp
	Include/SIMD/Detail/FPU/I32x1.hpp
	Include/SIMD/Detail/FPU/I32x2.hpp
	Include/SIMD/Detail/FPU/I32x3.hpp
	Include/SIMD/Detail/FPU/I32x4.hpp
)
set (SIMD_DETAIL_REFERENCE_INCLUDE_FILES
	Include/SIMD/Detail/Reference/Bool4.hpp
	Include/SIMD/Detail/Reference/F32x4.hpp
	Include/SIMD/Detail/Reference/I32x4.hpp
)
set (SIMD_DETAIL_SSE3_INCLUDE_FILES
	Include/SIMD/Detail/SSE3/Bool4.hpp
	Include/SIMD/Detail/SSE3/F32x4.hpp
	Include/SIMD/Detail/SSE3/F32x4_access.inl
	Include/SIMD/Detail/SSE3/F32x4_comparison.inl
	Include/SIMD/Detail/SSE3/F32x4_construction.inl
	Include/SIMD/Detail/SSE3/F32x4_operations.inl
	Include/SIMD/Detail/SSE3/I32x4.hpp
)
set (SIMD_DETAIL_SSE4_1_INCLUDE_FILES
	Include/SIMD/Detail/SSE4_1/Bool4.hpp
	Include/SIMD/Detail/SSE4_1/F32x4.hpp
	Include/SIMD/Detail/SSE4_1/F32x4_access.inl
	Include/SIMD/Detail/SSE4_1/F32x4_comparison.inl
	Include/SIMD/Detail/SSE4_1/F32x4_construction.inl
	Include/SIMD/Detail/SSE4_1/F32x4_operations.inl
	Include/SIMD/Detail/SSE4_1/F64x4.hpp
	Include/SIMD/Detail/SSE4_1/F64x4_access.inl
	Include/SIMD/Detail/SSE4_1/F64x4_comparison.inl
	Include/SIMD/Detail/SSE4_1/F64x4_construction.inl
	Include/SIMD/Detail/SSE4_1/F64x4_operations.inl
	Include/SIMD/Detail/SSE4_1/I32x4.hpp
	Include/SIMD/Detail/SSE4_1/Utilities.hpp
)

add_library (SIMD INTERFACE)
target_link_libraries (SIMD INTERFACE Configuration)

target_include_directories (SIMD
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

add_custom_target (SIMD_IDE SOURCES
	${INCLUDE_FILES}
	${SIMD_INCLUDE_FILES}
	${SIMD_DETAIL_INCLUDE_FILES}
	${SIMD_DETAIL_REFERENCE_INCLUDE_FILES}
	${SIMD_DETAIL_FPU_INCLUDE_FILES}
	${SIMD_DETAIL_SSE4_1_INCLUDE_FILES}
)

install (TARGETS SIMD
	EXPORT SIMDConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT SIMDConfig
	DESTINATION CMake
)

set_property (TARGET SIMD_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\SIMD FILES ${SIMD_INCLUDE_FILES})
source_group (Headers\\SIMD\\Detail FILES ${SIMD_DETAIL_INCLUDE_FILES})
source_group (Headers\\SIMD\\Detail\\Reference FILES ${SIMD_DETAIL_REFERENCE_INCLUDE_FILES})
source_group (Headers\\SIMD\\Detail\\FPU FILES ${SIMD_DETAIL_FPU_INCLUDE_FILES})
source_group (Headers\\SIMD\\Detail\\SSE4_1 FILES ${SIMD_DETAIL_SSE4_1_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY SIMD GROUP Core
	TEST_FILES
		UnitTest/Test_Bool4.cpp
		UnitTest/Test_F32x4_1.cpp
		UnitTest/Test_F32x4_2.cpp
		UnitTest/Test_F32x4_3.cpp
		UnitTest/Test_F32x4_4.cpp
		UnitTest/Test_FPU_F32x3.cpp
		UnitTest/Test_SSE4_1_Utilities.cpp
		../Test/UnitTestMain.cpp
)
