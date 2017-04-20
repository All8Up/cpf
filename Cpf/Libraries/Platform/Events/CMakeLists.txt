# ###############################################
set (INCLUDE_FILES
	Include/Events/Events.hpp
	Include/Events/Id.hpp
	Include/Events/Event.hpp
	Include/Events/Handle.hpp
	Include/Events/Emitter.hpp
	Include/Events/Integrators.hpp
)

add_library (Events INTERFACE)
target_link_libraries (Events INTERFACE Configuration s_Collections)

target_include_directories (Events INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
source_group (Interface FILES ${INCLUDE_FILES})

add_custom_target (Events_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET Events_IDE PROPERTY FOLDER Libraries/Interface/Platform)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include/Platform
	DESTINATION Include/Platform
	PATTERN *
)


install (TARGETS Events
	EXPORT EventsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT EventsConfig DESTINATION CMake)


# ###############################################
# ###############################################
MakeUnitTest (LIBRARY Events GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Emitter.hpp
		UnitTest/Test_DeferredEmitter.hpp
		../../Core/Test/UnitTestMain.cpp
)
