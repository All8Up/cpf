# ###############################################
option( CPF_THREADING_DISABLE_PROFILING "" OFF )

# ###############################################
set( THREADING_INCLUDE_FILES
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
)
set( THREADING_PLATFORM_INCLUDE_FILES
	Include/${CMAKE_SYSTEM_NAME}/Platform/Threading/Types.hpp
)
set( THREADING_SOURCE_FILES
	Source/Threading.cpp
	Source/${CMAKE_SYSTEM_NAME}/CPU.cpp
	Source/${CMAKE_SYSTEM_NAME}/Thread.cpp
	Source/${CMAKE_SYSTEM_NAME}/ThreadLocal.cpp
	Source/${CMAKE_SYSTEM_NAME}/Mutex.cpp
	Source/${CMAKE_SYSTEM_NAME}/Semaphore.cpp
	Source/${CMAKE_SYSTEM_NAME}/ConditionVariable.cpp
	Source/Reactor.cpp
)

add_library( s_Threading STATIC
	${THREADING_INCLUDE_FILES}
	${THREADING_PLATFORM_INCLUDE_FILES}
	${THREADING_SOURCE_FILES}
)
target_compile_definitions( s_Threading
	PUBLIC CPF_STATIC_THREADING
	PRIVATE CPF_BUILD_THREADING
)
if(CPF_THREADING_DISABLE_PROFILING)
	target_compile_definitions( s_Threading
		PUBLIC CPF_THREADING_DISABLE_PROFILING
	)
endif()

add_library( Threading SHARED
	${THREADING_INCLUDE_FILES}
	${THREADING_PLATFORM_INCLUDE_FILES}
	${THREADING_SOURCE_FILES}
)
target_compile_definitions( Threading
	PRIVATE CPF_BUILD_THREADING
)

source_group( Headers FILES ${THREADING_INCLUDE_FILES} ${THREADING_PLATFORM_INCLUDE_FILES} )
source_group( Source FILES ${THREADING_SOURCE_FILES} )

if (WIN32)
	set (ADDITIONAL_LIBS "Pdh.lib")
endif ()
target_link_libraries( Threading Configuration Collections Time Atomic Logging ${ADDITIONAL_LIBS})
target_link_libraries( s_Threading Configuration s_Collections s_Time Atomic Logging ${ADDITIONAL_LIBS})

target_include_directories( Threading PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)
target_include_directories( s_Threading PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
)

set_property( TARGET s_Threading PROPERTY FOLDER Libraries/Static/Platform )
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
install( TARGETS s_Threading
	EXPORT ThreadingConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT ThreadingConfig DESTINATION CMake )
]]#

# ###############################################
MakeUnitTests( LIBRARY Threading GROUP Platform
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
		Collections Time
)

option( CPF_THREADING_PROFILE_BUILD "" OFF )
if (CPF_THREADING_PROFILE_BUILD)
	set(PROFILE_ON 1)
else()
	set(PROFILE_ON 0)
endif()
# Only profile in static link libraries.
if (TARGET Test_s_Threading)
	target_compile_definitions( Test_s_Threading
		PUBLIC CPF_THREADING_PROFILE_BUILD=${PROFILE_ON}
	)
endif ()
