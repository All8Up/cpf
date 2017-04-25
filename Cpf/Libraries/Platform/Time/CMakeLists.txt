# ###############################################
set (INCLUDE_FILES
	Include/Time.hpp
)
set (TIME_INCLUDE_FILES
	Include/Time/Export.hpp
	Include/Time/Counter.hpp
	Include/Time/Unit.hpp
	Include/Time/Unit.inl
	Include/Time/Value.hpp
	Include/Time/Value.inl
	Include/Time/Scoped.hpp
	Include/Time/Ratio.hpp
)
set (TIME_SOURCE_FILES
	Source/Time.cpp
	Source/Value.cpp
	Source/Scoped.cpp
	Source/Ratio.cpp
	Source/${CMAKE_SYSTEM_NAME}/Counter.cpp
)

add_library (Time SHARED
	${INCLUDE_FILES}
	${TIME_INCLUDE_FILES}
	${TIME_SOURCE_FILES}
)
target_compile_definitions (Time
	PRIVATE CPF_BUILD_TIME
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Time FILES ${TIME_INCLUDE_FILES})
source_group (Sources FILES ${TIME_SOURCE_FILES})

target_link_libraries (Time Configuration)

target_include_directories (Time
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

set_property (TARGET Time PROPERTY FOLDER Libraries/Shared/Platform )

install (DIRECTORY Include/Time
	DESTINATION Include/Time
	PATTERN *
)

install (TARGETS Time
	EXPORT TimeConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT TimeConfig DESTINATION CMake)


# ###############################################
MakeUnitTest (LIBRARY Time GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Value.hpp
		UnitTest/Test_Unit_Us.hpp
		UnitTest/Test_Different_Unit_Comparison.hpp
		../../Core/Test/UnitTestMain.cpp
)
