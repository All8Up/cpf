function (create_lib_binary_name outName libName config)
	set (${outName} "" PARENT_SCOPE)
	get_target_property (libOutName ${libName} OUTPUT_NAME)
	if (NOT libOutName)
		#message (WARNING "Could not resolve library name for ${libName}")
		#print_target_properties (${libName})

		get_target_property (libOutName ${libName} NAME)
		get_target_property (libPostfix ${libName} ${config}_POSTFIX)
		if (libPostfix)
			set (libOutName "${libOutName}${libPostfix}")
		endif ()
		set (${outName} ${libOutName} PARENT_SCOPE)
	else ()
		set (${outName} ${libOutName} PARENT_SCOPE)
	endif ()
endfunction ()


function (cpf_binary_plugin)
	if (CPF_ENABLE_PACKAGING)
		set (options
			SHARED
			STATIC
			VCRUNTIME
		)
		set (single_value
			NAME
		)
		set (multi_value
			DEPENDENCIES
			WIN32_LIBS
		)
		cmake_parse_arguments (CBP "${options}" "${single_value}" "${multi_value}" ${ARGN})

		file (READ "${CPF_TEMPLATES}/plugin_binary.txt" template)
		if (CBP_SHARED)
			file (READ "${CPF_TEMPLATES}/plugin_binary_shared.txt" sharedTpl)
			string (REPLACE %name% ${CBP_NAME} sharedTpl ${sharedTpl})
		else ()
			set (sharedTpl "")
		endif ()

		if (CBP_DEPENDENCIES)
		endif ()

		if (CBP_VCRUNTIME)
		endif ()

		if (CBP_STATIC)
			file (READ "${CPF_TEMPLATES}/plugin_binary_static.txt" staticTpl)
			string (REPLACE %name% "${CBP_NAME}_s" fullTpl ${staticTpl})
			string (REPLACE %target% "${CBP_NAME}_s" fullTpl ${fullTpl})
			string (REPLACE %target_d% "${CBP_NAME}_s" fullTpl ${fullTpl})

			if (CBP_DEPENDENCIES)
				foreach (lib ${CBP_DEPENDENCIES})
					set (extraLibs "${extraLibs} ${lib}")
				endforeach ()
			else ()
				set (extraLibs "")
			endif ()

			if (CBP_WIN32_LIBS OR CBP_VCRUNTIME)
				set (win32Libs "	if (WIN32)\n		set (WIN32_LIBS")
				foreach (lib ${CBP_WIN32_LIBS})
					get_filename_component (extension ${lib} EXT)
					if (extension STREQUAL ".lib")
						set (win32Libs "${win32Libs}\n			${lib}")
					else ()
						set (win32Libs "${win32Libs}\n			${lib}.lib")
					endif ()
				endforeach ()
				if (CBP_VCRUNTIME)
					set (win32Libs "${win32Libs}\n			debug vcruntimed.lib ucrtd.lib\n			optimized vcruntime.lib ucrt.lib")
				endif ()

				set (win32Libs "${win32Libs}\n		)\n	endif ()\n")
				set (fullTpl "${fullTpl}${win32Libs}")
			endif ()

			if (extraLibs OR win32Libs)
				set (fullTpl "${fullTpl}	target_link_libraries (${CBP_NAME}_s INTERFACE \${WIN32_LIBS} ${extraLibs})")
			endif ()

			foreach (dep ${CBP_DEPENDENCIES})
				get_target_property (libName ${dep} OUTPUT_NAME)
				if (NOT libName)
					string (REPLACE %name% ${dep} depTpl ${staticTpl})
					string (REPLACE %target% ${dep} depTpl ${depTpl})

					create_lib_binary_name (libName ${dep} DEBUG)
					string (REPLACE %target_d% ${libName} depTpl ${depTpl})
					set (fullTpl "${depTpl}\n${fullTpl}")
				else ()
					string (REPLACE %name% ${dep} depTpl ${staticTpl})
					string (REPLACE %target% ${libName} depTpl ${depTpl})
					string (REPLACE %target_d% ${libName} depTpl ${depTpl})
					set (fullTpl "${depTpl}\n${fullTpl}")
				endif ()
			endforeach ()

			set (fullTpl "# ###################################################################\n	# Add target for prebuilt static libraries.\n${fullTpl}")
		else ()
			set (fullTpl "")
		endif ()

		string (REPLACE %name% "${CBP_NAME}" template "${template}")
		string (REPLACE %shared% ${sharedTpl} template "${template}")
		if (CBP_STATIC)
			string (REPLACE %static% ${fullTpl} template "${template}")
		else ()
			string (REPLACE %static% "" template "${template}")
		endif ()

		file (MAKE_DIRECTORY "${CPF_BINARY_PLUGIN_DIR}/${CBP_NAME}")
		if (CPF_BINARY_PLUGIN_PACKAGE)
			set (subdir "${CBP_NAME}/${CBP_NAME}")
			file (MAKE_DIRECTORY "${CPF_BINARY_PLUGIN_DIR}/${subdir}")
		else ()
			set (subdir "${CBP_NAME}")
		endif ()
		file (WRITE "${CPF_BINARY_PLUGIN_DIR}/${subdir}/CMakeLists.txt" ${template})

		# ####################################################
		# Setup binary copies as custom commands on PackageBinaryPlugins.
		# First copy the release only dll(.cfp) plugin.
		add_custom_target (PackageBinaries_${CBP_NAME})
		set_target_properties (PackageBinaries_${CBP_NAME} PROPERTIES FOLDER Packages)
		add_dependencies (PackageBinaries_${CBP_NAME} ${CBP_NAME})
		add_dependencies (PackageBinaryPlugins PackageBinaries_${CBP_NAME})

		set(no_copy_cfp $<NOT:$<CONFIG:Release>>)
		add_custom_command (
			TARGET PackageBinaries_${CBP_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CPF_BINARY_PLUGIN_DIR}/${subdir}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CPF_BINARY_PLUGIN_DIR}/${subdir}/Bin
			COMMAND ${CMAKE_COMMAND} -E
				$<${no_copy_cfp}:echo> $<${no_copy_cfp}:"">
				copy "$<TARGET_FILE:${CBP_NAME}>" "${CPF_BINARY_PLUGIN_DIR}/${subdir}/Bin/${CBP_NAME}.cfp"
	   	)
		foreach (dep ${CBP_DEPENDENCIES})
			get_target_property (type ${dep} TYPE)
			if ("${type}" STREQUAL "SHARED_LIBRARY")
				add_custom_command (
					TARGET PackageBinaries_${CBP_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E
						$<${no_copy_cfp}:echo> $<${no_copy_cfp}:"">
						copy "$<TARGET_FILE:${dep}>" "${CPF_BINARY_PLUGIN_DIR}/${subdir}/Bin"
			   	)
			endif ()
		endforeach ()

	   	if (CBP_STATIC)
		   	# Copy the static library and then the dependencies.
			add_custom_command (
				TARGET PackageBinaries_${CBP_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E make_directory ${CPF_BINARY_PLUGIN_DIR}/${subdir}/Lib
				COMMAND ${CMAKE_COMMAND} -E make_directory ${CPF_BINARY_PLUGIN_DIR}/${subdir}/Lib/$<CONFIG>
				COMMAND ${CMAKE_COMMAND} -E
					copy "$<TARGET_FILE:${CBP_NAME}_s>" "${CPF_BINARY_PLUGIN_DIR}/${subdir}/Lib/$<CONFIG>/${CBP_NAME}_s.lib"
		   	)

			foreach (dep ${CBP_DEPENDENCIES})
				if ("${type}" STREQUAL "STATIC_LIBRARY")
					add_custom_command (
						TARGET PackageBinaries_${CBP_NAME} POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E
							copy "$<TARGET_FILE:${dep}>" "${CPF_BINARY_PLUGIN_DIR}/${subdir}/Lib/$<CONFIG>"
				   	)
				endif ()
			endforeach ()
		endif ()
	endif ()
endfunction ()
