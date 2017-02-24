# ################################
# External library setup.

# Gmock
set (GMOCK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/gmock-1.7.0")
option (EXTERN_INLINE_GMOCK "Include the source project for gmock." ON)

# Spdlog
set (SPDLOG_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/spdlog")
option (EXTERN_INLINE_SPDLOG "Include the source project for spdlog." ON)

# Sdl2
set (SDL2_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL2-2.0.5")
option (EXTERN_INLINE_SDL2 "Include the source project for sdl2." ON)

# Rapidjson
set (RAPIDJSON_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/rapidjson-1.1.0")
option (EXTERN_INLINE_RAPIDJSON "Include the source project for rapidjson." ON)

# ################################
include ("Source/CMakeLists.txt")
