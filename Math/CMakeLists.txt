# ###############################################
set( INCLUDE_FILES
	Include/Math/Math.hpp
	Include/Math/Bits.hpp
	Include/Math/Color.hpp
	Include/Math/Constants.hpp
	Include/Math/Morton.hpp
	Include/Math/Vector2.hpp
	Include/Math/Vector3.hpp
	Include/Math/Vector3v.hpp
	Include/Math/Vector4.hpp
	Include/Math/Vector4v.hpp
	Include/Math/Matrix33v.hpp
	Include/Math/Matrix44v.hpp
	Include/Math/Half.hpp
	Include/Math/Rectangle.hpp
	Include/Math/Ballistics.hpp
	Include/Math/Easing.hpp
	Include/Math/Matrix44v_Operations.hpp
	Include/Math/LargeVector3f.hpp
	Include/Math/Quaternionv.hpp
	Include/Math/Utilities.hpp
)
set (INCLUDE_DETAIL_FILES
	Include/Math/Detail/Swizzle2.hpp
	Include/Math/Detail/Swizzle2.inl
	Include/Math/Detail/Swizzle3.hpp
	Include/Math/Detail/Swizzle3.inl
	Include/Math/Detail/Swizzle4.hpp
	Include/Math/Detail/Swizzle4.inl
	Include/Math/Detail/SwizzleMacros.hpp
	Include/Math/Detail/Vector2.inl
	Include/Math/Detail/Vector3.inl
	Include/Math/Detail/Vector3v.inl
	Include/Math/Detail/Vector4.inl
	Include/Math/Detail/Vector4v.inl
	Include/Math/Detail/Quaternionv.inl
)
set( SOURCE_FILES
	Source/Math.cpp
	Source/LargeVector3f.cpp
	Source/Utilities.cpp
)

add_library( s_Math STATIC
	${INCLUDE_FILES}
	${INCLUDE_DETAIL_FILES}
	${SOURCE_FILES}
)

target_compile_definitions( s_Math
	PUBLIC
		CPF_STATIC_MATH
	PRIVATE
		CPF_BUILD_MATH
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Detail FILES ${INCLUDE_DETAIL_FILES})
source_group (Sources FILES ${SOURCE_FILES})

target_link_libraries (s_Math Configuration s_Simd)

target_include_directories (s_Math PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Math PROPERTY FOLDER Libraries/Static/Platform )

install( DIRECTORY Include/Math
	DESTINATION Include/Math
	PATTERN *
)


install( TARGETS s_Math
	EXPORT MathConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT MathConfig DESTINATION CMake )


# ###############################################
MakeUnitTest( LIBRARY s_Math GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Vector2.cpp
		UnitTest/Test_Vector3.cpp
		UnitTest/Test_Vector4.cpp
		UnitTest/Test_Matrix33v.cpp
		UnitTest/Test_Matrix44v.cpp
		UnitTest/Test_Bits.cpp
		UnitTest/Test_Morton.cpp
		UnitTest/Test_Mat33Mat44Quat.cpp
		UnitTest/Test_LargeVector3f.cpp
		UnitTest/Test_Utilities.cpp
		../../UnitTesting/Source/Main.cpp
	LINK_LIBRARIES
		Configuration s_Simd
)
