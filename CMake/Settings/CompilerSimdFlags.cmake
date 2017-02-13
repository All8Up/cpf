# TODO: This should be setup in processor detection instead of here.
if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
	set (CPF_SIMD_INSTRUCTION_SET "SSE" CACHE STRING "SIMD instruction set.")
	set_property (CACHE CPF_SIMD_INSTRUCTION_SET PROPERTY STRINGS "SSE")

	set (CPF_SIMD_INSTRUCTION_LEVEL "Sse2" CACHE STRING "SIMD instruction set level.")
	set_property (CACHE CPF_SIMD_INSTRUCTION_LEVEL
		PROPERTY STRINGS Reference Sse1 Sse2 Sse3 Sse3_1 Sse4 Sse4_1 Sse4_2 Sse4a Avx Avx2)

	set (CPF_TARGET_PROCESSOR "x86_64" CACHE STRING "Target device processor.")

CheckInclusiveValue( ${CPF_SIMD_INSTRUCTION_LEVEL} 1 0
	"Reference;Sse1;Sse2;Sse3;Sse4;Sse4_1;Sse4_2;Sse4a;Avx;Avx2"
	"CPF_SIMD_REFERENCE;CPF_SIMD_SSE1;CPF_SIMD_SSE2;CPF_SIMD_SSE3;CPF_SIMD_SSE4;CPF_SIMD_SSE4_1;CPF_SIMD_SSE4_2;CPF_SIMD_SSE4a;CPF_SIMD_AVX;CPF_SIMD_AVX2" )

message("CPF_SIMD_REF:    ${CPF_SIMD_REFERENCE}")
message("CPF_SIMD_SSE1:   ${CPF_SIMD_SSE1}")
message("CPF_SIMD_SSE2:   ${CPF_SIMD_SSE2}")
message("CPF_SIMD_SSE3:   ${CPF_SIMD_SSE3}")
message("CPF_SIMD_SSE4:   ${CPF_SIMD_SSE4}")
message("CPF_SIMD_SSE4_1: ${CPF_SIMD_SSE4_1}")
message("CPF_SIMD_SSE4_2: ${CPF_SIMD_SSE4_2}")
message("CPF_SIMD_SSE4a:  ${CPF_SIMD_SSE4a}")
message("CPF_SIMD_AVX:    ${CPF_SIMD_AVX}")
message("CPF_SIMD_AVX2:   ${CPF_SIMD_AVX2}")

else ()
	message (ERROR "** Not an intel processor.  This is probably not correct until iOS/Android targets are supported.")
endif ()



# Just calls out to a compiler specific versioned file.
include (CMake/Settings/Detail/${CPF_COMPILER_NAME}_Simd_${CPF_COMPILER_VERSION_MAJOR}-${CPF_COMPILER_VERSION_MINOR}.cmake)
