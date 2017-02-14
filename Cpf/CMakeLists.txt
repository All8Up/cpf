if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Experimental")
endif ()
