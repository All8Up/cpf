if (TARGET eastl)
	message ("Using eastl.")
	set (CPF_USE_EASTL )
	set (STL_LIB "eastl")
else ()
	message ("Using compiler supplied STL.")

	set (STL_LIB "")
endif ()

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
	Include/Tuple.hpp
	Include/BitSet.hpp
	Include/EnumFlagType.hpp
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
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( s_Collections CPF ${STL_LIB} )

target_include_directories( s_Collections PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Collections PROPERTY FOLDER Libraries/Static/Core )

install( DIRECTORY Include
	DESTINATION Include
	PATTERN *
)

install( TARGETS s_Collections
	EXPORT CollectionsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT CollectionsConfig DESTINATION CMake )

#[[
# ###############################################
MakeUnitTest( LIBRARY Collections GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_EnumFlagType.cpp
		../Test/UnitTestMain.cpp
)
]]#
