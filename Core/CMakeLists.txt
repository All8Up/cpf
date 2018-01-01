# ###############################################
# External libraries.
if (CPF_ENABLE_CSHARP)
	set (CPF_CSHARP 1)
endif ()
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/External/Modules")

# gflags
add_definitions (/DGTEST_LANG_CXX11=1 /DGTEST_USE_OWN_TR1_TUPLE=0 /DGTEST_HAS_TR1_TUPLE=0)
set (BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_PACKAGING OFF CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_LIB ON CACHE BOOL "" FORCE)
set (GFLAGS_BUILD_gflags_nothreads_LIB OFF CACHE BOOL "" FORCE)
set (GFLAGS_INSTALL_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/gflags-2.2.1")
set_property (TARGET gflags_static PROPERTY FOLDER CPF/External/gflags-2.2.1)
target_compile_options (gflags_static PRIVATE /wd4127 /wd4100 /wd4459)

# glog
set (DISABLE_RTTI ON CACHE BOOL "" FORCE)
set (CPF_HAVE_GLOG 1 PARENT_SCOPE)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/glog-0.3.5")
set_property (TARGET glog PROPERTY FOLDER CPF/External/glog-0.3.5)
target_compile_options (glog PRIVATE /wd4722 /wd4267 /wd4100 /wd4505)

# gtest
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/External/googletest-release-1.8.0")
target_compile_options (gtest PUBLIC /DGTEST_LANG_CXX11=1 /DGTEST_HAS_TR1_TUPLE=0)
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set_property (TARGET gmock PROPERTY FOLDER CPF/External/gtest-1.8.0)
set_property (TARGET gmock_main PROPERTY FOLDER CPF/External/gtest-1.8.0)
set_property (TARGET gtest PROPERTY FOLDER CPF/External/gtest-1.8.0)
set_property (TARGET gtest_main PROPERTY FOLDER CPF/External/gtest-1.8.0)

# ###############################################
configure_file (Include/CPF/Configuration/Setup.hpp.in
	${CPF_GENERATED}/CPP/CPF/Configuration/Setup.hpp )

# ###############################################
set (CPF_INCLUDES
	Include/CPF/Configuration.hpp
	Include/CPF/EnumFlagType.hpp
	Include/CPF/Event.hpp
	Include/CPF/GOM.hpp
	Include/CPF/IntrusivePtr.hpp
	Include/CPF/IO.hpp
	Include/CPF/iRefCounted.hpp
	Include/CPF/Logging.hpp
	Include/CPF/Math.hpp
	Include/CPF/Plugin.hpp
	Include/CPF/Simd.hpp
	Include/CPF/Threading.hpp
	Include/CPF/Time.hpp
)
set (CPF_SOURCES
	Source/CPF.cpp
)

set (CONFIGURATION_INCLUDES
	Include/CPF/Configuration/Macros.hpp
	Include/CPF/Configuration/Setup.hpp.in
	${CPF_GENERATED}/CPP/CPF/Configuration/Setup.hpp
)

set (EVENT_INCLUDES
	Include/CPF/Event/Emitter.hpp
	Include/CPF/Event/Event.hpp
	Include/CPF/Event/Handle.hpp
	Include/CPF/Event/Id.hpp
	Include/CPF/Event/Integrators.hpp
)

set (GOM_IDL
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/GOM/iUnknown.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/GOM/iEventEmitter.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/GOM/ResultCodes.idl
)
CPF_GEN_GOM(GOM_GEN_INCLUDES cpp hpp ${CPF_GENERATED}/CPP/CPF/GOM ${GOM_IDL})
set (GOM_INCLUDES
	Include/CPF/GOM/tUnknown.hpp
	Include/CPF/GOM/Result.hpp
	Include/CPF/GOM/Types.hpp
)

set (HASH_INCLUDES
	Include/CPF/Hash/Crc.hpp
	Include/CPF/Hash/HashID.hpp
	Include/CPF/Hash/HashString.hpp
)
set (HASH_DETAIL_INCLUDES
	Include/CPF/Hash/Detail/Crc15Table.hpp
	Include/CPF/Hash/Detail/Crc16Table.hpp
	Include/CPF/Hash/Detail/Crc32Table.hpp
	Include/CPF/Hash/Detail/Crc64Table.hpp
)

set (IO_IDL
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/Access.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/Attributes.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/iDirectory.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/iExecutor.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/iFile.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/iFileStream.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/iStream.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/IO/Origin.idl
)
CPF_GEN_GOM(IO_GEN_INCLUDES cpp hpp ${CPF_GENERATED}/CPP/CPF/IO ${IO_IDL})
set (IO_INCLUDES
	Include/CPF/IO/BinaryReader.hpp
	Include/CPF/IO/BinaryWriter.hpp
	Include/CPF/IO/Directory.hpp
	Include/CPF/IO/File.hpp
	Include/CPF/IO/FileSystem.hpp
	Include/CPF/IO/Globbing.hpp
	Include/CPF/IO/Path.hpp
	Include/CPF/IO/Result.hpp
	Include/CPF/IO/Stream.hpp
	Include/CPF/IO/TextReader.hpp
	Include/CPF/IO/TextWriter.hpp
)
set (IO_SOURCES
	Source/IO/BinaryReader.cpp
	Source/IO/BinaryWriter.cpp
	Source/IO/Directory.cpp
	Source/IO/File.cpp
	Source/IO/FileSystem.cpp
	Source/IO/Globbing.cpp
	Source/IO/IO.cpp
	Source/IO/Path.cpp
	Source/IO/Stream.cpp
	Source/IO/TextReader.cpp
	Source/IO/TextWriter.cpp
	Source/IO/ANSI_C/FileSystem.cpp
	Source/IO/Windows/OsDirectory.cpp
	Source/IO/Windows/OsFile.cpp
)

set (MATH_INCLUDES
	Include/CPF/Math/Algorithm.hpp
	Include/CPF/Math/Ballistics.hpp
	Include/CPF/Math/BitManipulation.hpp
	Include/CPF/Math/Constants.hpp
	Include/CPF/Math/Exponential.hpp
	Include/CPF/Math/FixedPoint.hpp
	Include/CPF/Math/Hyperbolic.hpp
	Include/CPF/Math/Interpolation.hpp
	Include/CPF/Math/LargeVector.hpp
	Include/CPF/Math/Matrix22v.hpp
	Include/CPF/Math/Matrix33v.hpp
	Include/CPF/Math/Matrix44v.hpp
	Include/CPF/Math/Power.hpp
	Include/CPF/Math/Quaternion.hpp
	Include/CPF/Math/Rectangle.hpp
	Include/CPF/Math/Rounding.hpp
	Include/CPF/Math/Signal.hpp
	Include/CPF/Math/Transform.hpp
	Include/CPF/Math/Trigonometric.hpp
	Include/CPF/Math/Types.hpp
	Include/CPF/Math/Vector2v.hpp
	Include/CPF/Math/Vector3v.hpp
	Include/CPF/Math/Vector4v.hpp
)
set (MATH_BOUNDS_INCLUDES
	Include/CPF/Math/Bounds/AABB.hpp
	Include/CPF/Math/Bounds/OBB.hpp
	Include/CPF/Math/Bounds/Sphere.hpp
)
set (MATH_DISTANCE_INCLUDES
	Include/CPF/Math/Distance/Vector_Plane.hpp
)
set (MATH_GEOMETRY_INCLUDES
	Include/CPF/Math/Geometry/AABB.hpp
	Include/CPF/Math/Geometry/OBB.hpp
	Include/CPF/Math/Geometry/Ray3.hpp
	Include/CPF/Math/Geometry/Sphere.hpp
	Include/CPF/Math/Geometry/Plane.hpp
)
set (MATH_INTERSECTION_INCLUDES
	Include/CPF/Math/Intersection/Intersection.hpp
	Include/CPF/Math/Intersection/Ray3_Sphere.hpp
	Include/CPF/Math/Intersection/Ray3_Plane.hpp
)
set (MATH_DETAIL_INCLUDES
	Include/CPF/Math/Detail/LargeVector.inl
	Include/CPF/Math/Detail/Matrix22v.inl
	Include/CPF/Math/Detail/Matrix33v.inl
	Include/CPF/Math/Detail/Matrix44v.inl
	Include/CPF/Math/Detail/Quaternion.inl
	Include/CPF/Math/Detail/Rectangle.inl
	Include/CPF/Math/Detail/Transform.inl
	Include/CPF/Math/Detail/Vector2v.inl
	Include/CPF/Math/Detail/Vector3v.inl
	Include/CPF/Math/Detail/Vector4v.inl
)

set (PATTERNS_INCLUDES
	Include/CPF/Patterns/Factory.hpp
)

set (PERFORMANCE_INCLUDES
	Include/CPF/Performance/VTune.hpp
)

set (PLUGIN_IDL
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Plugin/iClassFactory.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Plugin/iRegistry.idl
)
CPF_GEN_GOM(PLUGIN_GEN_INCLUDES cpp hpp ${CPF_GENERATED}/CPP/CPF/Plugin ${PLUGIN_IDL})
set (PLUGIN_INCLUDES
	Include/CPF/Plugin/Library.hpp
	Include/CPF/Plugin/Registry.hpp
	Include/CPF/Plugin/SharedLibrary.hpp
	Include/CPF/Plugin/tClassFactory.hpp
)
set (PLUGIN_SOURCES
	Source/Plugin/Registry.cpp
)

set (SIMD_INCLUDES
	Include/CPF/SIMD/Types.hpp
	Include/CPF/SIMD/Rounding.hpp
)
set (SIMD_DETAIL_INCLUDES
	Include/CPF/SIMD/Detail/Accessor.hpp
	Include/CPF/SIMD/Detail/LaneIndex.hpp
	Include/CPF/SIMD/Detail/LaneRef.hpp
	Include/CPF/SIMD/Detail/LaneRef_1.inl
	Include/CPF/SIMD/Detail/LaneRef_2.inl
	Include/CPF/SIMD/Detail/LaneRef_3.inl
	Include/CPF/SIMD/Detail/LaneRef_4.inl
	Include/CPF/SIMD/Detail/Swizzles.hpp
)
set (SIMD_DETAIL_FPU_INCLUDES
	Include/CPF/SIMD/Detail/FPU/Bool4.hpp
	Include/CPF/SIMD/Detail/FPU/F32x1.hpp
	Include/CPF/SIMD/Detail/FPU/F32x2.hpp
	Include/CPF/SIMD/Detail/FPU/F32x3.hpp
	Include/CPF/SIMD/Detail/FPU/F32x4.hpp
	Include/CPF/SIMD/Detail/FPU/FPU.hpp
	Include/CPF/SIMD/Detail/FPU/I32x1.hpp
	Include/CPF/SIMD/Detail/FPU/I32x2.hpp
	Include/CPF/SIMD/Detail/FPU/I32x3.hpp
	Include/CPF/SIMD/Detail/FPU/I32x4.hpp
)
set (SIMD_DETAIL_REFERENCE_INCLUDES
	Include/CPF/SIMD/Detail/Reference/Bool4.hpp
	Include/CPF/SIMD/Detail/Reference/F32x4.hpp
	Include/CPF/SIMD/Detail/Reference/F64x4.hpp
	Include/CPF/SIMD/Detail/Reference/I32x4.hpp
)
set (SIMD_DETAIL_SSE3_INCLUDES
	Include/CPF/SIMD/Detail/SSE3/Bool4.hpp
	Include/CPF/SIMD/Detail/SSE3/F32x4.hpp
	Include/CPF/SIMD/Detail/SSE3/F32x4_access.inl
	Include/CPF/SIMD/Detail/SSE3/F32x4_comparison.inl
	Include/CPF/SIMD/Detail/SSE3/F32x4_construction.inl
	Include/CPF/SIMD/Detail/SSE3/F32x4_operations.inl
	Include/CPF/SIMD/Detail/SSE3/I32x4.hpp
)
set (SIMD_DETAIL_SSE4_1_INCLUDES
	Include/CPF/SIMD/Detail/SSE4_1/Bool4.hpp
	Include/CPF/SIMD/Detail/SSE4_1/F32x4.hpp
	Include/CPF/SIMD/Detail/SSE4_1/F32x4_access.inl
	Include/CPF/SIMD/Detail/SSE4_1/F32x4_comparison.inl
	Include/CPF/SIMD/Detail/SSE4_1/F32x4_construction.inl
	Include/CPF/SIMD/Detail/SSE4_1/F32x4_operations.inl
	Include/CPF/SIMD/Detail/SSE4_1/F64x4.hpp
	Include/CPF/SIMD/Detail/SSE4_1/F64x4_access.inl
	Include/CPF/SIMD/Detail/SSE4_1/F64x4_comparison.inl
	Include/CPF/SIMD/Detail/SSE4_1/F64x4_construction.inl
	Include/CPF/SIMD/Detail/SSE4_1/F64x4_operations.inl
	Include/CPF/SIMD/Detail/SSE4_1/I32x4.hpp
	Include/CPF/SIMD/Detail/SSE4_1/Utilities.hpp
)

set (STD_INCLUDES
	Include/CPF/Std/Algorithm.hpp
	Include/CPF/Std/Array.hpp
	Include/CPF/Std/BitSet.hpp
	Include/CPF/Std/CCType.hpp
	Include/CPF/Std/Deque.hpp
	Include/CPF/Std/ForwardList.hpp
	Include/CPF/Std/Functional.hpp
	Include/CPF/Std/Hash.hpp
	Include/CPF/Std/IndexedPool.hpp
	Include/CPF/Std/List.hpp
	Include/CPF/Std/Map.hpp
	Include/CPF/Std/Memory.hpp
	Include/CPF/Std/Move.hpp
	Include/CPF/Std/Pair.hpp
	Include/CPF/Std/Queue.hpp
	Include/CPF/Std/Set.hpp
	Include/CPF/Std/Stack.hpp
	Include/CPF/Std/String.hpp
	Include/CPF/Std/StringUtils.hpp
	Include/CPF/Std/Time.hpp
	Include/CPF/Std/Tuple.hpp
	Include/CPF/Std/UnorderedMap.hpp
	Include/CPF/Std/UnorderedSet.hpp
	Include/CPF/Std/Vector.hpp
)

set (THREADING_INCLUDES
	Include/CPF/Threading/Algorithm.hpp
	Include/CPF/Threading/ConditionVariable.hpp
	Include/CPF/Threading/CPU.hpp
	Include/CPF/Threading/Mutex.hpp
	Include/CPF/Threading/Reactor.hpp
	Include/CPF/Threading/ScopedLock.hpp
	Include/CPF/Threading/Semaphore.hpp
	Include/CPF/Threading/Thread.hpp
	Include/CPF/Threading/ThreadGroup.hpp
	Include/CPF/Threading/ThreadLocal.hpp
)

set (TIME_INCLUDES
	Include/CPF/Time/Counter.hpp
	Include/CPF/Time/Ratio.hpp
	Include/CPF/Time/Unit.hpp
	Include/CPF/Time/Unit.inl
	Include/CPF/Time/Value.hpp
	Include/CPF/Time/Value.inl
)

set (IDL_SOURCES
	${GOM_IDL}
	${IO_IDL}
	${PLUGIN_IDL}
)
set (IDL_GEN
	${GOM_GEN_INCLUDES}
	${IO_GEN_INCLUDES}
	${PLUGIN_GEN_INCLUDES}
)
set (ALL_SOURCES
	${CPF_INCLUDES}
	${CPF_SOURCES}

	${CONFIGURATION_INCLUDES}
	${EVENT_INCLUDES}
	${GOM_INCLUDES}
	${HASH_INCLUDES}
	${HASH_DETAIL_INCLUDES}
	${IO_INCLUDES}
	${IO_SOURCES}
	${MATH_INCLUDES}
	${MATH_BOUNDS_INCLUDES}
	${MATH_DISTANCE_INCLUDES}
	${MATH_GEOMETRY_INCLUDES}
	${MATH_INTERSECTION_INCLUDES}
	${MATH_DETAIL_INCLUDES}
	${PATTERNS_INCLUDES}
	${PERFORMANCE_INCLUDES}
	${PLUGIN_INCLUDES}
	${PLUGIN_SOURCES}
	${SIMD_INCLUDES}
	${SIMD_DETAIL_INCLUDES}
	${SIMD_DETAIL_FPU_INCLUDES}
	${SIMD_DETAIL_REFERENCE_INCLUDES}
	${SIMD_DETAIL_SSE4_1_INCLUDES}
	${STD_INCLUDES}
	${THREADING_INCLUDES}
	${TIME_INCLUDES}
)

if (WIN32)
	set (CPF_EXTRA_LIBS "${CPF_EXTRA_LIBS};Pdh.lib")
endif ()

# ###############################################
add_library (Core_s STATIC
	${ALL_SOURCES}
)
target_link_libraries (Core_s
	gflags_static
	glog
	${CPF_EXTRA_LIBS}
	${CPF_CS_LIBS}
)
target_include_directories (Core_s
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
target_compile_definitions (Core_s
	PUBLIC
		CPF_STATIC
	PRIVATE
		CPF_BUILD
)
set_property (TARGET Core_s PROPERTY FOLDER CPF)


# ###############################################
add_library (Core SHARED
	${ALL_SOURCES}
)
target_link_libraries (Core
	gflags_static
	glog
	${EXTRA_LIBS}
	${CPF_CS_LIBS}
)
target_include_directories (Core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
target_compile_definitions (Core
	PRIVATE
		CPF_BUILD
)
set_property (TARGET Core PROPERTY FOLDER CPF)

# ###############################################
add_library (i_Core INTERFACE)
target_include_directories (i_Core
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
add_custom_target (Core_IDL
	SOURCES
		${IDL_SOURCES}
		${IDL_GEN}
)
add_dependencies (Core_s Core_IDL)
add_dependencies (i_Core Core_IDL)
add_dependencies (Core Core_IDL)
set_property (TARGET Core_IDL PROPERTY FOLDER CPF)

# ###############################################
source_group (Include FILES ${CPF_INCLUDES})
source_group (Source FILES ${CPF_SOURCES})

source_group (Include\\Configuration FILES ${CONFIGURATION_INCLUDES})

source_group (Include\\Event FILES ${EVENT_INCLUDES})

source_group (IDL\\GOM FILES ${GOM_IDL})
source_group (Include\\GOM FILES ${GOM_GEN_INCLUDES} ${GOM_INCLUDES})

source_group (Include\\Hash FILES ${HASH_INCLUDES})
source_group (Include\\Hash\\Detail FILES ${HASH_DETAIL_INCLUDES})

source_group (IDL\\IO FILES ${IO_IDL})
source_group (Include\\IO FILES ${IO_GEN_INCLUDES} ${IO_INCLUDES})
source_group (Source\\IO FILES ${IO_SOURCES})

source_group (Include\\Math FILES ${MATH_INCLUDES})
source_group (Include\\Math\\Bounds FILES ${MATH_BOUNDS_INCLUDES})
source_group (Include\\Math\\Distance FILES ${MATH_DISTANCE_INCLUDES})
source_group (Include\\Math\\Geometry FILES ${MATH_GEOMETRY_INCLUDES})
source_group (Include\\Math\\Intersection FILES ${MATH_INTERSECTION_INCLUDES})
source_group (Include\\Math\\Detail FILES ${MATH_DETAIL_INCLUDES})

source_group (Include\\SIMD FILES ${SIMD_INCLUDES})
source_group (Include\\SIMD\\Detail FILES ${SIMD_DETAIL_INCLUDES})
source_group (Include\\SIMD\\Detail\\FPU FILES ${SIMD_DETAIL_FPU_INCLUDES})
source_group (Include\\SIMD\\Detail\\Reference FILES ${SIMD_DETAIL_REFERENCE_INCLUDES})
source_group (Include\\SIMD\\Detail\\SSE3 FILES ${SIMD_DETAIL_SSE3_INCLUDES})
source_group (Include\\SIMD\\Detail\\SSE4_1 FILES ${SIMD_DETAIL_SSE4_1_INCLUDES})

source_group (Include\\Patterns FILES ${PATTERNS_INCLUDES})

source_group (Include\\Performance FILES ${PERFORMANCE_INCLUDES})

source_group (IDL\\Plugin FILES ${PLUGIN_IDL})
source_group (Include\\Plugin FILES ${PLUGIN_GEN_INCLUDES} ${PLUGIN_INCLUDES})
source_group (Source\\Plugin FILES ${PLUGIN_SOURCES})

source_group (Include\\Std FILES ${STD_INCLUDES})

source_group (Include\\Threading FILES ${THREADING_INCLUDES})

source_group (Include\\Time FILES ${TIME_INCLUDES})


# ###############################################
set (TEST_INCLUDES
	Tests/IOTestFixture.hpp
	Tests/TimeTestFixture.hpp
)
set (TEST_SOURCES
	Tests/Test_AABB.cpp
	Tests/Test_BinaryReader.cpp
	Tests/Test_BinaryWriter.cpp
	Tests/Test_BitManipulation.cpp
	Tests/Test_Bool4.cpp
	Tests/Test_CodeGen.cpp
	Tests/Test_ConditionVariable.cpp
	Tests/Test_Crc.cpp
	Tests/Test_DeferredEmitter.cpp
	Tests/Test_Different_Unit_Comparison.cpp
	Tests/Test_Directory.cpp
	Tests/Test_Emitter.cpp
	Tests/Test_EnumFlagType.cpp
	Tests/Test_Factory.cpp
	Tests/Test_File.cpp
	Tests/Test_FixedPoint.cpp
	Tests/Test_FPU_F32x3.cpp
	Tests/Test_Future.cpp
	Tests/Test_FXXx4_1.cpp
	Tests/Test_FXXx4_2.cpp
	Tests/Test_FXXx4_3.cpp
	Tests/Test_FXXx4_4.cpp
	Tests/Test_Globbing.cpp
	Tests/Test_GOM.cpp
	Tests/Test_HashID.cpp
	Tests/Test_IndexedPool.cpp
	Tests/Test_IO.cpp
	Tests/Test_LargeVector.cpp
	Tests/Test_Matrix22v.cpp
	Tests/Test_Matrix33v.cpp
	Tests/Test_Matrix44v.cpp
	Tests/Test_Mutex.cpp
	Tests/Test_OBB.cpp
	Tests/Test_Path.cpp
	Tests/Test_Plugin.cpp
	Tests/Test_Quaternion.cpp
	Tests/Test_Reactor.cpp
	Tests/Test_Scoped.cpp
	Tests/Test_Semaphore.cpp
	Tests/Test_SSE4_1_Utilities.cpp
	Tests/Test_TextReader.cpp
	Tests/Test_TextWriter.cpp
	Tests/Test_Thread.cpp
	Tests/Test_ThreadLocal.cpp
	Tests/Test_Unit_Us.cpp
	Tests/Test_Value.cpp
	Tests/Test_Vector2v.cpp
	Tests/Test_Vector3.cpp
	Tests/Test_Vector3v.cpp
	Tests/Test_Vector4v.cpp
)
if (CPF_ENABLE_UNITTESTS)
	add_executable (Test_Core
		${TEST_INCLUDES}
		${TEST_SOURCES}
	)
	target_link_libraries(Test_Core
		Core gtest gtest_main
	)
	set_property (TARGET Test_Core PROPERTY FOLDER Tests)

	add_executable (Test_Core_s
		${TEST_INCLUDES}
		${TEST_SOURCES}
	)
	target_link_libraries(Test_Core_s
		Core_s gtest gtest_main
	)
	set_property (TARGET Test_Core_s PROPERTY FOLDER Tests)

	# ###############################################
	# NOTE: Plugins always use the static library so they are isolated, including memory.
	add_library (TestPlugin SHARED
		Tests/TestPlugin/iTestPlugin.hpp
		Tests/TestPlugin/TestPlugin.cpp
	)
	target_link_libraries (TestPlugin
		Core_s
	)
	set_property (TARGET TestPlugin PROPERTY FOLDER Tests/Plugins)
	add_custom_command (TARGET TestPlugin POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestPlugin> ${CPF_COMMON_PLUGINS}/TestPlugin.cfp
	)

	add_library (TestPlugin_s STATIC
		Tests/TestPlugin/iTestPlugin.hpp
		Tests/TestPlugin/TestPlugin.cpp
	)
	target_link_libraries (TestPlugin_s
		Core_s
	)
	target_compile_definitions (TestPlugin_s
		PRIVATE
			CPF_PLUGIN_STATIC
	)
	set_property (TARGET TestPlugin_s PROPERTY FOLDER Tests/Plugins)

	add_executable (Test_StaticPlugin
		Tests/Test_StaticPlugin.cpp
	)
	target_link_libraries(Test_StaticPlugin gtest gtest_main Core_s TestPlugin_s)
	set_property (TARGET Test_StaticPlugin PROPERTY FOLDER Tests)
endif ()
