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

# Cereal
set (CEREAL_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/cereal-1.2.2")
option (EXTERN_INLINE_CEREAL "Include the source project for cereal." ON)

# ASIO
set (ASIO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/asio-1.10.8")
option (EXTERN_INLINE_ASIO "Include the source project for asio." ON)

# Aurora
set (AURORA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/Aurora")
option (EXTERN_INLINE_AURORA "Include the source project for Aurora" ON)

# BGFX
set (BGFX_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/bgfx")
option (EXTERN_INLINE_BGFX "Include the source project for Bgfx" ON)

# Box2D
set (BOX2D_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/Box2D-2.3.1")
option (EXTERN_INLINE_BOX2D "Include the source project for Box2D" ON)

# ################################
include ("Source/CMakeLists.txt")
