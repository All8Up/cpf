# ###############################################
set( INCLUDE_FILES
	Include/Atomic/Atomic.hpp
	Include/Atomic/Fence.hpp
)
set( PLATFORM_INCLUDE_FILES
	Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}/Platform/Atomic/MemoryOrder.hpp
	Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}/Platform/Atomic/Operations.hpp
)
set( SOURCE_FILES
	Source/Atomic.cpp
)

add_library( s_Atomic STATIC
	${INCLUDE_FILES}
	${PLATFORM_INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Atomic
	PUBLIC CPF_STATIC_ATOMIC
	PRIVATE CPF_BUILD_ATOMIC
)
add_library( Atomic SHARED
	${INCLUDE_FILES}
	${PLATFORM_INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( Atomic
	PRIVATE CPF_BUILD_ATOMIC
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Headers\\Platform FILES ${PLATFORM_INCLUDE_FILES})
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( Atomic Configuration )
target_link_libraries( s_Atomic Configuration )

target_include_directories( Atomic PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}>
)
target_include_directories( s_Atomic PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}>
)

set_property (TARGET s_Atomic PROPERTY FOLDER Libraries/Static/Core)
set_property (TARGET Atomic PROPERTY FOLDER Libraries/Shared/Core)

install( DIRECTORY Include/Atomic
	DESTINATION Include/Atomic
	PATTERN *
)
install( DIRECTORY Include/${CMAKE_SYSTEM_NAME}/Platform/Atomic
	DESTINATION ${CPF_PLATFORM_INCLUDE_DIR}/Platform
	PATTERN *
)


install( TARGETS Atomic
	EXPORT AtomicConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_Atomic
	EXPORT AtomicConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT AtomicConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Atomic GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../../UnitTesting/Source/Main.cpp
)
