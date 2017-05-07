# ###############################################
set (INCLUDE_FILES
	Include/Concurrency/Concurrency.hpp
	Include/Concurrency/Backoff.hpp
	Include/Concurrency/Scheduler.hpp
	Include/Concurrency/Opcodes.hpp
	Include/Concurrency/Queue.hpp
	Include/Concurrency/ThreadContext.hpp
	Include/Concurrency/ThreadPool.hpp
	Include/Concurrency/LoadBalancer.hpp
)
set (SOURCE_FILES
	Source/Concurrency.cpp
	Source/Scheduler.cpp
	Source/Opcodes.cpp
	Source/Queue.cpp
	Source/ThreadContext.cpp
	Source/ThreadPool.cpp
	Source/LoadBalancer.cpp
)

set (COLLECTIONS_INCLUDE
	Include/Concurrency/Collections/RingBuffer.hpp
)
set (COLLECTIONS_SOURCE
)


set (DISPATCH_INCLUDE
	Include/Concurrency/Dispatch/Vector.hpp
)
set (DISPATCH_SOURCE
)

add_library (Concurrency SHARED
	${INCLUDE_FILES}
	${DISPATCH_INCLUDE}
	${COLLECTIONS_INCLUDE}
	${SOURCE_FILES}
	${DISPATCH_SOURCE}
	${COLLECTIONS_SOURCE}
)
target_compile_definitions (Concurrency
	PRIVATE
		CPF_BUILD_CONCURRENCY
)
target_link_libraries (Concurrency Configuration Atomic Threading Logging VTune)
target_include_directories (Concurrency PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
set_property (TARGET Concurrency PROPERTY FOLDER Libraries/Shared/Platform)

add_library (i_Concurrency INTERFACE)
target_link_libraries (i_Concurrency INTERFACE Configuration Atomic Threading)
target_include_directories (i_Concurrency INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)


source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Headers\\Dispatch FILES ${DISPATCH_INCLUDE})
source_group (Sources\\Dispatch FILES ${DISPATCH_SOURCE})
source_group (Headers\\Collections FILES ${COLLECTIONS_INCLUDE})
source_group (Sources\\Collections FILES ${COLLECTIONS_SOURCE})


#[[
install (DIRECTORY Include/Concurrency
	DESTINATION Include/Concurrency
	PATTERN *
)


install (TARGETS s_Concurrency
	EXPORT ConcurrencyConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT ConcurrencyConfig DESTINATION CMake)
]]#

# ###############################################
MakeUnitTest (LIBRARY Concurrency GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Backoff.cpp
		UnitTest/Test_RingBuffer.cpp
		UnitTest/Test_Scheduler.cpp
		UnitTest/Test_Scheduler_Opcode_All.cpp
		UnitTest/Test_Scheduler_Opcode_AllBarrier.cpp
		UnitTest/Test_Scheduler_Opcode_First.cpp
		UnitTest/Test_Scheduler_Opcode_FirstBarrier.cpp
		UnitTest/Test_Scheduler_Opcode_Last.cpp
		UnitTest/Test_Scheduler_Opcode_LastBarrier.cpp
		UnitTest/Test_Scheduler_Opcode_ActiveThreads.cpp
		UnitTest/Test_Scheduler_Opcode_ThreadLocalDataRegister.cpp
		UnitTest/Test_Scheduler_Opcode_ThreadLocalAddressRegister.cpp
		UnitTest/Test_Scheduler_Opcode_SharedDataRegister.cpp
		UnitTest/Test_Scheduler_Opcode_SharedAddressRegister.cpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Configuration Atomic Threading VTune
)


# ###############################################
# Performance testing application.
#[[
add_executable (SchedulerPerformance
	Performance/SchedulerPerformance.cpp
)
target_link_libraries (SchedulerPerformance Configuration Logging Math s_Application s_Concurrency)

set_property (TARGET SchedulerPerformance PROPERTY FOLDER Performance/Concurrency)
]]#
