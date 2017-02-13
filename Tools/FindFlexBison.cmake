if (WIN32)
	set (CMAKE_PROGRAM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/External/bin/windows "${CMAKE_PROGRAM_PATH}")
	set (CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/External/bin/windows "${CMAKE_INCLUDE_PATH}")
endif ()

find_package (FLEX)
find_package (BISON)

if (FLEX_EXECUTABLE AND BISON_EXECUTABLE)
	message ("Flex version: ${FLEX_VERSION}")
	message ("Bison version: ${BISON_VERSION}")
endif ()
