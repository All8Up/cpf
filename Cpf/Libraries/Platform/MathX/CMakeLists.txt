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
	Include/Math/Vector2.hpp
	Include/Math/Vector3.hpp
	Include/Math/Vector4.hpp
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
	Include/Math/Detail/Vector2.inl
	Include/Math/Detail/Vector3.inl
	Include/Math/Detail/Vector4.inl
	Include/Math/Detail/Vector2v.inl
	Include/Math/Detail/Vector3v.inl
	Include/Math/Detail/Vector4v.inl
	Include/Math/Detail/Swizzle2.hpp
	Include/Math/Detail/Swizzle2.inl
	Include/Math/Detail/Swizzle3.hpp
	Include/Math/Detail/Swizzle3.inl
	Include/Math/Detail/Swizzle4.hpp
	Include/Math/Detail/Swizzle4.inl
	Include/Math/Detail/SwizzleMacros.hpp
)

add_library (MathX INTERFACE)
target_link_libraries (MathX INTERFACE Configuration SimdX)

target_include_directories (MathX
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

add_custom_target (MathX_IDE SOURCES
	Include/Math.hpp
	${MATH_INCLUDE_FILES}
	${MATH_DETAIL_INCLUDE_FILES}
)

install (TARGETS MathX
	EXPORT MathXConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT MathXConfig
	DESTINATION CMake
)

set_property (TARGET MathX_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES Include/Math.hpp)
source_group (Interface\\MathX FILES ${MATH_INCLUDE_FILES})
source_group (Interface\\MathX\\Detail FILES ${MATH_DETAIL_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY MathX GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_AABB.cpp
		UnitTest/Test_BitManipulation.cpp
		UnitTest/Test_CodeGen.cpp
		UnitTest/Test_Vector2v.cpp
		UnitTest/Test_Vector3v.cpp
		UnitTest/Test_Vector4v.cpp
		UnitTest/Test_Matrix22v.cpp
		UnitTest/Test_Matrix33v.cpp
		UnitTest/Test_Matrix44v.cpp
		UnitTest/Test_OBB.cpp
		UnitTest/Test_Quaternion.cpp
		../../Core/Test/UnitTestMain.cpp
)
