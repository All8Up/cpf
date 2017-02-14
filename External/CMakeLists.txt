# ################################
# External library setup.

# Gmock
option (EXTERN_INLINE_GMOCK "Include the source project for gmock." OFF)
set (GMOCK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/gmock-1.7.0")

# Spdlog
option (EXTERN_INLINE_SPDLOG "Include the source project for spdlog." OFF)
set (SPDLOG_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/spdlog")

# Sdl2
option (EXTERN_INLINE_SDL2 "Include the source project for sdl2." OFF)
set (SDL2_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL2-2.0.5")

# ################################
include ("Source/CMakeLists.txt")
