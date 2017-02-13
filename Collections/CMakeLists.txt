# ###############################################
set( INCLUDE_FILES
	Include/Algorithm.hpp
	Include/Collections.hpp
	Include/Array.hpp
	Include/Deque.hpp
	Include/ForwardList.hpp
	Include/List.hpp
	Include/Map.hpp
	Include/Pair.hpp
	Include/Queue.hpp
	Include/Set.hpp
	Include/Stack.hpp
	Include/UnorderedMap.hpp
	Include/UnorderedSet.hpp
	Include/Vector.hpp
	Include/String.hpp
	Include/Functional.hpp
	Include/Move.hpp
	Include/Memory.hpp
	Include/StringUtils.hpp
	Include/HandlePool.hpp
	Include/Tuple.hpp
	Include/PacketStream.hpp
	Include/BitSet.hpp
)
set( SOURCE_FILES
	Source/Collections.cpp
)

add_library( s_Collections STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Collections
	PUBLIC CPF_STATIC_COLLECTIONS
	PRIVATE CPF_BUILD_COLLECTIONS
)
add_library( Collections SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( Collections
	PRIVATE CPF_BUILD_COLLECTIONS
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( Collections Configuration eastl Atomic )
target_link_libraries( s_Collections Configuration eastl s_Atomic )

target_include_directories( Collections PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories( s_Collections PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Collections PROPERTY FOLDER Libraries/Static/Core )
set_property( TARGET Collections PROPERTY FOLDER Libraries/Shared/Core )

install( DIRECTORY Include
	DESTINATION Include
	PATTERN *
)

install( TARGETS Collections
	EXPORT CollectionsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_Collections
	EXPORT CollectionsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT CollectionsConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Collections GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_HandlePool.hpp
		UnitTest/Test_PacketStream.cpp
		../Test/UnitTestMain.cpp
)
