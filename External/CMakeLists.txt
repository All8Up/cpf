# ################################
# External library setup.

# Gmock
option (EXTERN_INLINE_GMOCK "Include the source project for gmock." OFF)
set (GMOCK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/gmock-1.7.0")

# Spdlog
option (EXTERN_INLINE_SPDLOG "Include the source project for spdlog." OFF)
set (SPDLOG_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/spdlog")


# ################################
include ("Source/CMakeLists.txt")
