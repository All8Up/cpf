if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Core")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Core")

	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Platform")
		add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Platform")

		if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic")
			add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic")
		endif ()
	endif ()
endif ()
