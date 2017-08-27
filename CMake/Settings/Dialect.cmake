# New way to handle dialects.
set (CMAKE_CXX_STANDARD 11)

preferred_include (
	"${CMAKE_CURRENT_SOURCE_DIR}/CMake/Settings/Detail/${CPF_COMPILER_NAME}_Dialect_${CPF_COMPILER_VERSION_MAJOR}-${CPF_COMPILER_VERSION_MINOR}.cmake"
	"${CMAKE_CURRENT_SOURCE_DIR}/CMake/Settings/Detail/${CPF_COMPILER_NAME}_Dialect_${CPF_COMPILER_VERSION_MAJOR}-0.cmake"
)
