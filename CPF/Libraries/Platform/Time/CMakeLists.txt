# ###############################################
set (TIME_INCLUDE_FILES
	Include/Time/Counter.hpp
	Include/Time/Unit.hpp
	Include/Time/Unit.inl
	Include/Time/Value.hpp
	Include/Time/Value.inl
	Include/Time/Ratio.hpp
)
set (TIME_INCLUDE_PLATFORM_FILES
	Include/${CMAKE_SYSTEM_NAME}/Platform/Time/Counter.hpp
)

add_library (Time INTERFACE)

add_custom_target (Time_IDE
	SOURCES
		${TIME_INCLUDE_FILES}
		${TIME_INCLUDE_PLATFORM_FILES}
)
set_property (TARGET Time_IDE PROPERTY FOLDER Libraries/Interface/Platform)

source_group (Headers FILES ${TIME_INCLUDE_FILES})
source_group (Headers\\Platform ${TIME_INCLUDE_PLATFORM_FILES})

target_link_libraries (Time INTERFACE Configuration)

target_include_directories (Time
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
		$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)


# ###############################################
MakeUnitTest (LIBRARY Time GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Value.hpp
		UnitTest/Test_Unit_Us.hpp
		UnitTest/Test_Different_Unit_Comparison.hpp
		../../Core/Test/UnitTestMain.cpp
)
