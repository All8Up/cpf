if (NOT CPF_PLUGIN_BINARY_PlatformConcurrency)
	# ###############################################
	set (INCLUDE_FILES
		Include/Backoff.hpp
		Include/Scheduler.hpp
		Include/Opcodes.hpp
		Include/WorkBuffer.hpp
		Include/ThreadPool.hpp
		Include/LoadBalancer.hpp
		Include/Fence.hpp
		Include/TimerService.hpp
	)
	set (SOURCE_FILES
		Source/Plugin.cpp
		Source/Scheduler.cpp
		Source/Opcodes.cpp
		Source/WorkBuffer.cpp
		Source/ThreadPool.cpp
		Source/LoadBalancer.cpp
		Source/Fence.cpp
		Source/TimerService.cpp
	)

	set (COLLECTIONS_INCLUDE
		Include/Collections/RingBuffer.hpp
	)


	set (DISPATCH_INCLUDE
		Include/Dispatch/Vector.hpp
	)

	add_library (PlatformConcurrency SHARED
		${INCLUDE_FILES}
		${DISPATCH_INCLUDE}
		${COLLECTIONS_INCLUDE}
		${SOURCE_FILES}
		${IDL_FILES}
		${CPP_IDL_FILES}
	)
	target_link_libraries (PlatformConcurrency Core_s)
	target_include_directories (PlatformConcurrency PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
	)
	set_property (TARGET PlatformConcurrency PROPERTY FOLDER Plugins/Drivers/Platform)

	if (CPF_BUILD_STATIC_VARIANTS)
		add_library (PlatformConcurrency_s STATIC
			${INCLUDE_FILES}
			${DISPATCH_INCLUDE}
			${COLLECTIONS_INCLUDE}
			${SOURCE_FILES}
			${IDL_FILES}
			${CPP_IDL_FILES}
		)
		target_link_libraries (PlatformConcurrency_s Core_s)
		target_include_directories (PlatformConcurrency_s PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
		)
		target_compile_definitions (PlatformConcurrency_s PUBLIC PlatformConcurrency_STATIC=1 PRIVATE CPF_PLUGIN_STATIC)
		set_property (TARGET PlatformConcurrency_s PROPERTY FOLDER Plugins/Drivers/Platform)
	endif ()


	source_group (Headers FILES ${INCLUDE_FILES})
	source_group (Sources FILES ${SOURCE_FILES})
	source_group (Headers\\Dispatch FILES ${DISPATCH_INCLUDE})
	source_group (Sources\\Dispatch FILES ${DISPATCH_SOURCE})
	source_group (Headers\\Collections FILES ${COLLECTIONS_INCLUDE})
	source_group (Sources\\Collections FILES ${COLLECTIONS_SOURCE})
	source_group (IDL FILES ${IDL_FILES})
	source_group (Headers FILES ${CPP_IDL_FILES})

	# ###############################################
	# Copy as a plugin.
	add_custom_command (
		TARGET PlatformConcurrency POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlatformConcurrency> ${CPF_COMMON_PLUGINS}/PlatformConcurrency.cfp
	)

	if (CPF_ENABLE_UNITTESTS)
		add_executable (Test_PlatformConcurrency
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
			UnitTest/Test_PlatformConcurrency_TimerService.cpp
		)
		target_link_libraries(Test_PlatformConcurrency
			Core_s gtest gtest_main PlatformConcurrency
		)
		target_include_directories (Test_PlatformConcurrency PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		)
		set_property (TARGET Test_PlatformConcurrency PROPERTY FOLDER Tests)
	endif ()

	# ###############################################
	cpf_binary_plugin(
		SHARED
		STATIC
		NAME
			PlatformConcurrency
	)
endif ()
