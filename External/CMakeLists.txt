# ################################
# External library setup.
option (EXTERN_INLINE_GMOCK "Include the source project for gmock." OFF)
set (GMOCK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/gmock-1.7.0")

include ("Source/CMakeLists.txt")
