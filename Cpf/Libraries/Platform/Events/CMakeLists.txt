# ###############################################
set( INCLUDE_FILES
	Include/Events/Events.hpp
	Include/Events/Id.hpp
	Include/Events/Event.hpp
	Include/Events/Handle.hpp
	Include/Events/Emitter.hpp
	Include/Events/Integrators.hpp
)
set( SOURCE_FILES
	Source/Events.cpp
)

add_library( s_Events STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Events
	PUBLIC CPF_STATIC_EVENTS
	PRIVATE CPF_BUILD_EVENTS
)
add_library( Events SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( Events
	PRIVATE CPF_BUILD_EVENTS
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( Events Configuration Collections )
target_link_libraries( s_Events Configuration s_Collections )

target_include_directories( Events PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories( s_Events PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Events PROPERTY FOLDER Libraries/Static/Platform )
set_property( TARGET Events PROPERTY FOLDER Libraries/Shared/Platform )

install( DIRECTORY Include/Events
	DESTINATION Include/Events
	PATTERN *
)


install( TARGETS Events
	EXPORT EventsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_Events
	EXPORT EventsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT EventsConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Events GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Emitter.hpp
		UnitTest/Test_DeferredEmitter.hpp
		../../Core/Test/UnitTestMain.cpp
)
