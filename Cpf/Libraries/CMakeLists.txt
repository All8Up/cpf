if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Core")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Core")

	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Platform")
		add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Platform")

		if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic")
			add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic")
		endif ()

		if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Graphics")
			add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Graphics")
		endif ()

		if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Adapter")
			add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Adapter")
		endif ()

		if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Game")
			add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Game")
		endif ()
	endif ()
endif ()

# Make a custom target that represents all plugins.
# This is a pretty shitty solution but the only one I know of to get dependencies sorted out.
add_custom_target (AllPlugins DEPENDS
	MultiCore
	EntityService
	AdapterD3D12
)
set_property (TARGET AllPlugins PROPERTY FOLDER Plugins)
