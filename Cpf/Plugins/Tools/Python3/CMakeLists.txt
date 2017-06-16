# ###############################################
if (PYTHON_LIBRARY AND PYTHON_DEBUG_LIBRARY)
	message ("Found Python3.")

	set (INCLUDE_FILES
		Include/Python3.hpp
	)

	set (INTERFACE_FILES
		Interface/iPython.hpp
	)

	set (SOURCE_FILES
		Source/Plugin.cpp
		Source/Python3.cpp
	)

	set (PYTHON_CPF_LIB_FILES
		Script/cpf/__init__.py
		Script/cpf/gom.py
		Script/cpf/plugin.py
	)

	# ###############################################
	add_library (Python3 SHARED
		${INCLUDE_FILES}
		${INTERFACE_FILES}
		${SOURCE_FILES}
		${PYTHON_CPF_LIB_FILES}
	)
	target_include_directories (Python3
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
			$<INSTALL_INTERFACE:Interface>
		PRIVATE
			${PYTHON_INCLUDE_DIR}
	)
	target_link_libraries (Python3
		PUBLIC
			Configuration Plugin Logging
		PRIVATE
            debug ${PYTHON_DEBUG_LIBRARY}
            optimized ${PYTHON_LIBRARY}
	)
	set_property (TARGET Python3 PROPERTY FOLDER Plugins/Tools)


	# ###############################################
	# Copy as a plugin.
	add_custom_command (
		TARGET Python3 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Python3> ${CPF_COMMON_PLUGINS}/Python3.cfp
	)

	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Script/cpf/__init__.py ${CMAKE_BINARY_DIR}/Debug/resources/plugins/py/cpf/__init__.py COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Script/cpf/gom.py ${CMAKE_BINARY_DIR}/Debug/resources/plugins/py/cpf/gom.py COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Script/cpf/plugin.py ${CMAKE_BINARY_DIR}/Debug/resources/plugins/py/cpf/plugin.py COPYONLY)

	# ###############################################
	source_group (Headers FILES ${INCLUDE_FILES})
	source_group (Interfaces FILES ${INTERFACE_FILES})
	source_group (Sources FILES ${SOURCE_FILES})
	source_group (Sources\\Python\\cpf FILES ${PYTHON_CPF_LIB_FILES})
else ()
	message ("Python not found.")
endif ()

# ###############################################
# The plugin interface is available even if the plugin is not compiled.
add_library (i_Python3 INTERFACE)
target_include_directories (i_Python3
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
