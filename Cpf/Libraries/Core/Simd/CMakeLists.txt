# ###############################################
set( CPF_SIMD_LEVEL "Sse2" CACHE STRING "Simd level supported." )
set_property( CACHE CPF_SIMD_LEVEL PROPERTY STRINGS Reference Sse1 Sse2 Sse3 Sse4.1 Sse4.2 Sse4a Avx Avx2 )


# ###############################################
set( INCLUDE_FILES
	Include/Simd/Simd.hpp
	Include/${CPF_COMPILER_INCLUDE_DIR}/${CPF_TARGET_CPU_DIR}/Simd/Types.hpp
)
set( INCLUDE_REFERENCE
	Include/Simd/Detail/Reference/All.hpp
	Include/Simd/Detail/Reference/Int8x16.hpp
	Include/Simd/Detail/Reference/Uint8x16.hpp
	Include/Simd/Detail/Reference/Int8x32.hpp
	Include/Simd/Detail/Reference/Uint8x32.hpp
	Include/Simd/Detail/Reference/Int16x8.hpp
	Include/Simd/Detail/Reference/Uint16x8.hpp
	Include/Simd/Detail/Reference/Int16x16.hpp
	Include/Simd/Detail/Reference/Uint16x16.hpp
	Include/Simd/Detail/Reference/Int32x4.hpp
	Include/Simd/Detail/Reference/Uint32x4.hpp
	Include/Simd/Detail/Reference/Int32x8.hpp
	Include/Simd/Detail/Reference/Uint32x8.hpp
	Include/Simd/Detail/Reference/Int64x2.hpp
	Include/Simd/Detail/Reference/Uint64x2.hpp
	Include/Simd/Detail/Reference/Int64x4.hpp
	Include/Simd/Detail/Reference/Uint64x4.hpp
	Include/Simd/Detail/Reference/Float32x4.hpp
	Include/Simd/Detail/Reference/Float64x2.hpp
	Include/Simd/Detail/Reference/Float32x8.hpp
	Include/Simd/Detail/Reference/Float64x4.hpp
)
set( INCLUDE_SSE1
	Include/Simd/Detail/Sse/Sse1/Float32x4.hpp
	Include/Simd/Detail/Sse/Sse1/Float32x8.hpp
)
set( INCLUDE_SSE2
	Include/Simd/Detail/Sse/Sse2/Int8x16.hpp
	Include/Simd/Detail/Sse/Sse2/Float32x4.hpp
)
set( INCLUDE_SSE3
	Include/Simd/Detail/Sse/Sse3/Float32x4.hpp
)
set( INCLUDE_SSE4_1
	Include/Simd/Detail/Sse/Sse4_1/Int8x16.hpp
	Include/Simd/Detail/Sse/Sse4_1/Float32x4.hpp
)
set( INCLUDE_SSE4_2
	Include/Simd/Detail/Sse/Sse4_2/Float32x4.hpp
)
set( INCLUDE_SSE4a
	Include/Simd/Detail/Sse/Sse4a/Float32x4.hpp
)
set( INCLUDE_AVX
	Include/Simd/Detail/Sse/Avx/Float32x8.hpp
	Include/Simd/Detail/Sse/Avx/Float32x4.hpp
)
set( INCLUDE_AVX2
	Include/Simd/Detail/Sse/Avx2/Float32x4.hpp
)
set( INCLUDE_SSE
	Include/Simd/Detail/Sse/Sse1.hpp
	Include/Simd/Detail/Sse/Sse2.hpp
	Include/Simd/Detail/Sse/Sse3.hpp
	Include/Simd/Detail/Sse/Sse4_1.hpp
	Include/Simd/Detail/Sse/Sse4_2.hpp
	Include/Simd/Detail/Sse/Sse4a.hpp
	Include/Simd/Detail/Sse/Avx.hpp
	Include/Simd/Detail/Sse/Avx2.hpp
)
set( SOURCE_FILES
	Source/Simd.cpp
)

add_library( s_Simd STATIC
	${INCLUDE_FILES}
	${INCLUDE_REFERENCE}
	${INCLUDE_SSE1}
	${INCLUDE_SSE2}
	${INCLUDE_SSE3}
	${INCLUDE_SSE4_1}
	${INCLUDE_SSE4_2}
	${INCLUDE_AVX}
	${INCLUDE_AVX2}
	${INCLUDE_SSE}
	${SOURCE_FILES}
)

target_compile_definitions( s_Simd
	PUBLIC
		CPF_STATIC_SIMD
	PRIVATE
		CPF_BUILD_SIMD
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Headers\\Reference FILES ${INCLUDE_REFERENCE} )
source_group( Headers\\Sse FILES ${INCLUDE_SSE} )
source_group( Headers\\Sse\\Sse1 FILES ${INCLUDE_SSE1} )
source_group( Headers\\Sse\\Sse2 FILES ${INCLUDE_SSE2} )
source_group( Headers\\Sse\\Sse3 FILES ${INCLUDE_SSE3} )
source_group( Headers\\Sse\\Sse4_1 FILES ${INCLUDE_SSE4_1} )
source_group( Headers\\Sse\\Sse4_2 FILES ${INCLUDE_SSE4_2} )
source_group( Headers\\Sse\\Sse4a FILES ${INCLUDE_SSE4a} )
source_group( Headers\\Sse\\Avx FILES ${INCLUDE_AVX} )
source_group( Headers\\Sse\\Avx2 FILES ${INCLUDE_AVX2} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( s_Simd Configuration )

target_include_directories( s_Simd PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_COMPILER_INCLUDE_DIR}/${CPF_TARGET_CPU_DIR}>
	$<INSTALL_INTERFACE:Include/${CPF_COMPILER_INCLUDE_DIR}/${CPF_TARGET_CPU_DIR}>
)

set_property( TARGET s_Simd PROPERTY FOLDER Libraries/Static/Core )

install( DIRECTORY Include/Simd
	DESTINATION Include/Simd
	PATTERN *
)


install( TARGETS s_Simd
	EXPORT SimdConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT SimdConfig DESTINATION CMake )


# ###############################################
MakeUnitTest( LIBRARY s_Simd GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Int8x16.hpp
		UnitTest/Test_Float32x4.hpp
		UnitTest/Test_Float32x8.hpp
		../Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Configuration
)
