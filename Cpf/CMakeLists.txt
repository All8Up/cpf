if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Experimental")
endif ()

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tools")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Tools")
endif ()
