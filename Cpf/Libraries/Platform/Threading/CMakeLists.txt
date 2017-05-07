# ###############################################
option( CPF_THREADING_DISABLE_PROFILING "" OFF )

# ###############################################
set (THREADING_INCLUDE_FILES
	Include/Threading.hpp
	Include/Threading/Export.hpp
	Include/Threading/CPU.hpp
	Include/Threading/Thread.hpp
	Include/Threading/ThreadLocal.hpp
	Include/Threading/Mutex.hpp
	Include/Threading/Semaphore.hpp
	Include/Threading/ConditionVariable.hpp
	Include/Threading/ScopedLock.hpp
	Include/Threading/Reactor.hpp
	Include/Threading/ThreadGroup.hpp
)
set (THREADING_PLATFORM_INCLUDE_FILES
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/Types.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/CPU.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/Thread.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/ThreadLocal.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/Semaphore.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/ConditionVariable.hpp
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/Mutex.hpp
)
set (THREADING_SOURCE_FILES
	Source/Threading.cpp
)

add_library( Threading SHARED
	${THREADING_INCLUDE_FILES}
	${THREADING_PLATFORM_INCLUDE_FILES}
	${THREADING_SOURCE_FILES}
)
target_compile_definitions( Threading
	PRIVATE CPF_BUILD_THREADING
)

add_library (i_Threading INTERFACE)
target_link_libraries (i_Threading INTERFACE Configuration Atomic Time)
target_include_directories (i_Threading INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)

source_group (Headers FILES ${THREADING_INCLUDE_FILES})
source_group (Headers\\Platform FILES ${THREADING_PLATFORM_INCLUDE_FILES})
source_group (Source FILES ${THREADING_SOURCE_FILES})

if (WIN32)
	set (ADDITIONAL_LIBS "Pdh.lib")
endif ()
target_link_libraries (Threading Configuration s_Collections Time Atomic Logging ${ADDITIONAL_LIBS})

target_include_directories( Threading PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)

set_property( TARGET Threading PROPERTY FOLDER Libraries/Shared/Platform )

#[[
install( DIRECTORY Include/Threading
	DESTINATION Include/Threading
	PATTERN *
)
install( DIRECTORY Include/${CMAKE_SYSTEM_NAME}/Platform/Threading
	DESTINATION ${CPF_PLATFORM_INCLUDE_DIR}/Platform
	PATTERN *
)


install( TARGETS Threading
	EXPORT ThreadingConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT ThreadingConfig DESTINATION CMake )
]]#

# ###############################################
MakeUnitTest( LIBRARY Threading GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_ConditionVariable.hpp
		UnitTest/Test_Mutex.hpp
		UnitTest/Test_Scoped.hpp
		UnitTest/Test_Semaphore.hpp
		UnitTest/Test_Thread.hpp
		UnitTest/Test_ThreadLocal.hpp
		UnitTest/Test_Reactor.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_Collections Time
)

option( CPF_THREADING_PROFILE_BUILD "" OFF )
if (CPF_THREADING_PROFILE_BUILD)
	set(PROFILE_ON 1)
else()
	set(PROFILE_ON 0)
endif()
