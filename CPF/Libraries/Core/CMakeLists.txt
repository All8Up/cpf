# External libraries.
# gflags
set (BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_PACKAGING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_LIB ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_nothreads_LIB OFF CACHE BOOL "" FORCE)
set (GFLAGS_INSTALL_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/gflags-2.2.1")
set_property (TARGET gflags_static PROPERTY FOLDER Core/External/gflags-2.2.1)
target_compile_options (gflags_static PRIVATE /wd4127 /wd4100 /wd4459)

# glog
set (DISABLE_RTTI ON CACHE BOOL "" FORCE)
set (CPF_HAVE_GLOG 1 PARENT_SCOPE)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/glog-0.3.5")
set_property (TARGET glog PROPERTY FOLDER Core/External/glog-0.3.5)
target_compile_options (glog PRIVATE /wd4722 /wd4267 /wd4100 /wd4505)

# gtest
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/googletest-release-1.8.0")
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set_property (TARGET gmock PROPERTY FOLDER Core/External/gtest-1.8.0)
set_property (TARGET gmock_main PROPERTY FOLDER Core/External/gtest-1.8.0)
set_property (TARGET gtest PROPERTY FOLDER Core/External/gtest-1.8.0)
set_property (TARGET gtest_main PROPERTY FOLDER Core/External/gtest-1.8.0)

# Cpf Core Libraries.
add_subdirectory (SIMD)
