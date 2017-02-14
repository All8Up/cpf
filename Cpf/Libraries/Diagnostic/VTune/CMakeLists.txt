# Setup if VTune found or not.
if (VTune_INCLUDE_DIRS)
	if (CPF_ENABLE_VTUNE)
		set (vtune_includes ${VTune_INCLUDE_DIRS})
		set (vtune_libs ${VTune_LIBRARIES})
	endif ()
endif ()


#
set (INCLUDE_FILES
	Include/VTune/VTune.hpp
)

add_library (VTune INTERFACE)
target_include_directories (VTune
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${vtune_includes}>
)

target_link_libraries (VTune INTERFACE Configuration ${vtune_libs})

add_custom_target (VTune_IDE SOURCES ${INCLUDE_FILES} )
set_property (TARGET VTune_IDE PROPERTY FOLDER Libraries/Static/Diagnostics)
source_group (Include FILES ${INCLUDE_FILES})


# Installation setup.
install (DIRECTORY Include/VTune
	DESTINATION Include/VTune
	PATTERN *
)


install( TARGETS VTune
	EXPORT VTuneConfiguration
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

install( EXPORT VTuneConfiguration DESTINATION CMake )


# ###############################################
MakeUnitTest( LIBRARY VTune GROUP Diagnostics
	TEST_FILES
		UnitTest/Test_All.hpp
		../../UnitTesting/Source/Main.cpp
	LINK_LIBRARIES
		VTune Configuration Threading Time
)
