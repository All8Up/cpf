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

add_library (Threading INTERFACE)
target_include_directories (Threading INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)


if (WIN32)
	set (ADDITIONAL_LIBS "Pdh.lib")
endif ()
target_link_libraries (Threading INTERFACE Configuration s_Collections Time Atomic Logging ${ADDITIONAL_LIBS})

add_custom_target (Threading_IDE SOURCES ${THREADING_INCLUDE_FILES} ${THREADING_PLATFORM_INCLUDE_FILES})
set_property (TARGET Threading_IDE PROPERTY FOLDER Libraries/Interface/Platform)
source_group (Interface FILES ${THREADING_INCLUDE_FILES})
source_group (Interface\\Platform FILES ${THREADING_PLATFORM_INCLUDE_FILES})


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
MakeUnitTest (LIBRARY Threading GROUP Platform
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
