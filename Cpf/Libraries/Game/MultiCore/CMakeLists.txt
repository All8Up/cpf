# ###############################################
set (INCLUDE_FILES
	Include/MultiCore.hpp
)
set (MULTICORE_INCLUDE_FILES
	Include/MultiCore/Export.hpp
	Include/MultiCore/Types.hpp
	Include/MultiCore/Service.hpp
	Include/MultiCore/Stage.hpp
	Include/MultiCore/Distributor.hpp
	Include/MultiCore/Container.hpp
	Include/MultiCore/Partitioning.hpp
)

set (SOURCE_FILES
	Source/MultiCore.cpp
)
set (MULTICORE_SOURCE_FILES
	Source/MultiCore/Service.cpp
	Source/MultiCore/Stage.cpp
	Source/MultiCore/Distributor.cpp
)

add_library (s_MultiCore STATIC
	${INCLUDE_FILES}
	${MULTICORE_INCLUDE_FILES}
	${SOURCE_FILES}
	${MULTICORE_SOURCE_FILES}
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
		Configuration s_Collections RefCount Logging s_Hash s_Concurrency
)
set_property (TARGET s_MultiCore PROPERTY FOLDER Libraries/Static/Game)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\MultiCore FILES ${MULTICORE_INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Sources\\MultiCore FILES ${MULTICORE_SOURCE_FILES})

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
