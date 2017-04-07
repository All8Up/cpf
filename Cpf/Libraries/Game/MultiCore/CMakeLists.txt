# ###############################################
set (INCLUDE_FILES
	Include/MultiCore.hpp
)
set (MULTICORE_INCLUDE_FILES
	Include/MultiCore/Export.hpp
	Include/MultiCore/Types.hpp
	Include/MultiCore/iStage.hpp
	Include/MultiCore/Container.hpp
	Include/MultiCore/Partitioning.hpp
	Include/MultiCore/iPipeline.hpp
	Include/MultiCore/iSystem.hpp
)
set (MULTICORE_SYSTEM_INCLUDE_FILES
	Include/MultiCore/System/iTimer.hpp
)

set (SOURCE_FILES
	Source/MultiCore.cpp
)
set (MULTICORE_SOURCE_FILES
	Source/MultiCore/Types.cpp
	Source/MultiCore/Stage.hpp
	Source/MultiCore/Stage.cpp
	Source/MultiCore/Pipeline.hpp
	Source/MultiCore/Pipeline.cpp
	Source/MultiCore/System.hpp
	Source/MultiCore/System.cpp
	Source/MultiCore/QueueBuilder.hpp
	Source/MultiCore/QueueBuilder.cpp
)
set (MULTICORE_SYSTEM_SOURCE_FILES
	Source/MultiCore/System/Timer.hpp
	Source/MultiCore/System/Timer.cpp
)

add_library (s_MultiCore STATIC
	${INCLUDE_FILES}
	${MULTICORE_INCLUDE_FILES}
	${MULTICORE_SYSTEM_INCLUDE_FILES}
	${SOURCE_FILES}
	${MULTICORE_SOURCE_FILES}
	${MULTICORE_SYSTEM_SOURCE_FILES}
)
target_compile_definitions (s_MultiCore
	PUBLIC CPF_STATIC_MULTICORE
	PRIVATE CPF_BUILD_MULTICORE
)
target_include_directories (s_MultiCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_MultiCore
	LINK_PUBLIC
		Configuration s_Collections COM Logging s_Hash s_Concurrency Plugin
)
set_property (TARGET s_MultiCore PROPERTY FOLDER Libraries/Static/Game)


# ###############################################
add_library (MultiCore SHARED
	${INCLUDE_FILES}
	${MULTICORE_INCLUDE_FILES}
	${MULTICORE_SYSTEM_INCLUDE_FILES}
	${SOURCE_FILES}
	${MULTICORE_SOURCE_FILES}
	${MULTICORE_SYSTEM_SOURCE_FILES}
)
target_compile_definitions (MultiCore
	PRIVATE CPF_BUILD_MULTICORE
)
target_include_directories (MultiCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (MultiCore
	LINK_PUBLIC
		Configuration s_Collections Plugin COM Logging Hash s_Concurrency
)
set_property (TARGET MultiCore PROPERTY FOLDER Plugins/Game)

# ###############################################
add_library (MultiCore_Interface INTERFACE)
target_include_directories (MultiCore_Interface
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\MultiCore FILES ${MULTICORE_INCLUDE_FILES})
source_group (Headers\\MultiCore\\System FILES ${MULTICORE_SYSTEM_INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Sources\\MultiCore FILES ${MULTICORE_SOURCE_FILES})
source_group (Sources\\MultiCore\\System FILES ${MULTICORE_SYSTEM_SOURCE_FILES})

# ###############################################
#[[
install (TARGETS s_MultiCore
	EXPORT MultiCoreSystemConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT MultiCoreSystemConfig DESTINATION CMake)
]]#

# ###############################################
MakeUnitTest( LIBRARY s_MultiCore GROUP Game
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_QueueBuilder.hpp
		../../Core/Test/UnitTestMain.cpp
)
