# ###############################################
set (INCLUDE_FILES
	Include/Concurrency/Backoff.hpp
	Include/Concurrency/Scheduler.hpp
	Include/Concurrency/Opcodes.hpp
	Include/Concurrency/WorkBuffer.hpp
	Include/Concurrency/ThreadPool.hpp
	Include/Concurrency/LoadBalancer.hpp
	Include/Concurrency/Fence.hpp
	Include/Concurrency/ThreadTimes.hpp
)
set (INTERFACE_FILES
	Interface/Concurrency/Concurrency.hpp
	Interface/Concurrency/WorkContext.hpp
	Interface/Concurrency/ThreadTimeInfo.hpp
	Interface/Concurrency/iWorkBuffer.hpp
	Interface/Concurrency/iScheduler.hpp
	Interface/Concurrency/iThreadPool.hpp
	Interface/Concurrency/iLoadBalancer.hpp
	Interface/Concurrency/iFence.hpp
	Interface/Concurrency/iThreadTimes.hpp
)
set (SOURCE_FILES
	Source/Plugin.cpp
	Source/Scheduler.cpp
	Source/Opcodes.cpp
	Source/WorkBuffer.cpp
	Source/ThreadPool.cpp
	Source/LoadBalancer.cpp
	Source/Fence.cpp
	Source/ThreadTimes.cpp
)

set (COLLECTIONS_INCLUDE
	Include/Concurrency/Collections/RingBuffer.hpp
)


set (DISPATCH_INCLUDE
	Include/Concurrency/Dispatch/Vector.hpp
)

add_library (Concurrency SHARED
	${INCLUDE_FILES}
	${INTERFACE_FILES}
	${DISPATCH_INCLUDE}
	${COLLECTIONS_INCLUDE}
	${SOURCE_FILES}
)
target_compile_definitions (Concurrency
	PRIVATE
		CPF_BUILD_CONCURRENCY
)
target_link_libraries (Concurrency Configuration Plugin Threading Logging VTune)
target_include_directories (Concurrency PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
	$<INSTALL_INTERFACE:Interface>
)
set_property (TARGET Concurrency PROPERTY FOLDER Plugins/Platform)

add_library (i_Concurrency INTERFACE)
target_link_libraries (i_Concurrency INTERFACE Configuration Plugin Threading)
target_include_directories (i_Concurrency INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
	$<INSTALL_INTERFACE:Interface>
)


source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Headers\\Dispatch FILES ${DISPATCH_INCLUDE})
source_group (Sources\\Dispatch FILES ${DISPATCH_SOURCE})
source_group (Headers\\Collections FILES ${COLLECTIONS_INCLUDE})
source_group (Sources\\Collections FILES ${COLLECTIONS_SOURCE})

# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Concurrency POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Concurrency> ${CPF_COMMON_PLUGINS}/Concurrency.cfp
)


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
		../../../Libraries/Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Configuration Threading VTune s_PluginHost
)

# ###############################################
# Performance testing application.
#[[
add_executable (SchedulerPerformance
	Performance/SchedulerPerformance.cpp
)
target_link_libraries (SchedulerPerformance Configuration Logging Math s_Application Concurrency)

set_property (TARGET SchedulerPerformance PROPERTY FOLDER KPI/Concurrency)
#]]
