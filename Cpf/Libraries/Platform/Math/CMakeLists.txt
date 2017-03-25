# ###############################################
set (MATH_INCLUDE_FILES
	Include/Math/AABB.hpp
	Include/Math/BitManipulation.hpp
	Include/Math/Constants.hpp
	Include/Math/Matrix22v.hpp
	Include/Math/Matrix33v.hpp
	Include/Math/Matrix44v.hpp
	Include/Math/OBB.hpp
	Include/Math/Quaternion.hpp
	Include/Math/Rectangle.hpp
	Include/Math/Transform.hpp
	Include/Math/Types.hpp
	Include/Math/Vector2v.hpp
	Include/Math/Vector3v.hpp
	Include/Math/Vector4v.hpp
)
set (MATH_DETAIL_INCLUDE_FILES
	Include/Math/Detail/AABB.inl
	Include/Math/Detail/Matrix22v.inl
	Include/Math/Detail/Matrix33v.inl
	Include/Math/Detail/Matrix44v.inl
	Include/Math/Detail/OBB.inl
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
source_group (Interface FILES Include/Math.hpp)
source_group (Interface\\Math FILES ${MATH_INCLUDE_FILES})
source_group (Interface\\Math\\Detail FILES ${MATH_DETAIL_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY Math GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_AABB.cpp
		UnitTest/Test_BitManipulation.cpp
		UnitTest/Test_CodeGen.cpp
		UnitTest/Test_Vector2v.cpp
		UnitTest/Test_Vector3.cpp
		UnitTest/Test_Vector3v.cpp
		UnitTest/Test_Vector4v.cpp
		UnitTest/Test_Matrix22v.cpp
		UnitTest/Test_Matrix33v.cpp
		UnitTest/Test_Matrix44v.cpp
		UnitTest/Test_OBB.cpp
		UnitTest/Test_Quaternion.cpp
		../../Core/Test/UnitTestMain.cpp
)
