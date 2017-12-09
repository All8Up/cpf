# ###############################################
set (MATH_INCLUDE_FILES
	Include/Math/Algorithm.hpp
	Include/Math/Ballistics.hpp
	Include/Math/BitManipulation.hpp
	Include/Math/Constants.hpp
	Include/Math/Exponential.hpp
	Include/Math/FixedPoint.hpp
	Include/Math/Hyperbolic.hpp
	Include/Math/Interpolation.hpp
	Include/Math/LargeVector.hpp
	Include/Math/Matrix22v.hpp
	Include/Math/Matrix33v.hpp
	Include/Math/Matrix44v.hpp
	Include/Math/Power.hpp
	Include/Math/Quaternion.hpp
	Include/Math/Rectangle.hpp
	Include/Math/Rounding.hpp
	Include/Math/Signal.hpp
	Include/Math/Transform.hpp
	Include/Math/Trigonometric.hpp
	Include/Math/Types.hpp
	Include/Math/Vector2v.hpp
	Include/Math/Vector3v.hpp
	Include/Math/Vector4v.hpp
)
set (MATH_BOUNDS_INCLUDE_FILES
	Include/Math/Bounds/AABB.hpp
	Include/Math/Bounds/OBB.hpp
	Include/Math/Bounds/Sphere.hpp
)
set (MATH_DISTANCE_INCLUDE_FILES
	Include/Math/Distance/Vector_Plane.hpp
)
set (MATH_GEOMETRY_INCLUDE_FILES
	Include/Math/Geometry/AABB.hpp
	Include/Math/Geometry/OBB.hpp
	Include/Math/Geometry/Ray3.hpp
	Include/Math/Geometry/Sphere.hpp
	Include/Math/Geometry/Plane.hpp
)
set (MATH_INTERSECTION_INCLUDE_FILES
	Include/Math/Intersection/Intersection.hpp
	Include/Math/Intersection/Ray3_Sphere.hpp
	Include/Math/Intersection/Ray3_Plane.hpp
)
set (MATH_DETAIL_INCLUDE_FILES
	Include/Math/Detail/LargeVector.inl
	Include/Math/Detail/Matrix22v.inl
	Include/Math/Detail/Matrix33v.inl
	Include/Math/Detail/Matrix44v.inl
	Include/Math/Detail/Quaternion.inl
	Include/Math/Detail/Rectangle.inl
	Include/Math/Detail/Transform.inl
	Include/Math/Detail/Vector2v.inl
	Include/Math/Detail/Vector3v.inl
	Include/Math/Detail/Vector4v.inl
)

add_library (Math INTERFACE)
target_link_libraries (Math INTERFACE Configuration SIMD)

target_include_directories (Math
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

add_custom_target (Math_IDE SOURCES
	Include/Math.hpp
	${MATH_INCLUDE_FILES}
	${MATH_BOUNDS_INCLUDE_FILES}
	${MATH_DISTANCE_INCLUDE_FILES}
	${MATH_GEOMETRY_INCLUDE_FILES}
	${MATH_INTERSECTION_INCLUDE_FILES}
	${MATH_DETAIL_INCLUDE_FILES}
)

install (TARGETS Math
	EXPORT MathConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT MathConfig
	DESTINATION CMake
)

set_property (TARGET Math_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Headers FILES Include/Math.hpp)
source_group (Headers\\Math FILES ${MATH_INCLUDE_FILES})
source_group (Headers\\Math\\Bounds FILES ${MATH_BOUNDS_INCLUDE_FILES})
source_group (Headers\\Math\\Distance FILES ${MATH_DISTANCE_INCLUDE_FILES})
source_group (Headers\\Math\\Geometry FILES ${MATH_GEOMETRY_INCLUDE_FILES})
source_group (Headers\\Math\\Intersection FILES ${MATH_INTERSECTION_INCLUDE_FILES})
source_group (Headers\\Math\\Detail FILES ${MATH_DETAIL_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY Math GROUP Platform
	TEST_FILES
		UnitTest/Test_AABB.cpp
		UnitTest/Test_All.hpp
		UnitTest/Test_BitManipulation.cpp
		UnitTest/Test_CodeGen.cpp
		UnitTest/Test_FixedPoint.cpp
		UnitTest/Test_LargeVector.cpp
		UnitTest/Test_Matrix22v.cpp
		UnitTest/Test_Matrix33v.cpp
		UnitTest/Test_Matrix44v.cpp
		UnitTest/Test_OBB.cpp
		UnitTest/Test_Quaternion.cpp
		UnitTest/Test_Vector2v.cpp
		UnitTest/Test_Vector3.cpp
		UnitTest/Test_Vector3v.cpp
		UnitTest/Test_Vector4v.cpp
		UnitTest/Test_Quaternion.cpp
		../../Core/Test/UnitTestMain.cpp
)
