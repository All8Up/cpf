if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Plugins")
endif ()

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tools")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Tools")
endif ()

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Support")
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/KPI")
