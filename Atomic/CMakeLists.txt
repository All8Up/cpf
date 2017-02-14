# ###############################################
set (INCLUDE_FILES
	Include/Atomic.hpp
	Include/Atomic/Operations.hpp
	Include/Atomic/Fence.hpp
)
set (PLATFORM_INCLUDE_FILES
	Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}/Platform/Atomic/MemoryOrder.hpp
	Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}/Platform/Atomic/Operations.hpp
)

add_library (Atomic INTERFACE)
target_link_libraries (Atomic INTERFACE Configuration)
target_include_directories (Atomic INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}>
)

add_custom_target (Atomic_IDE SOURCES ${INCLUDE_FILES} ${PLATFORM_INCLUDE_FILES})
set_property (TARGET Atomic_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Platform FILES ${PLATFORM_INCLUDE_FILES})

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
install( EXPORT AtomicConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY Atomic GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
