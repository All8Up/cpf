function (cpf_binary_plugin)
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

		if (CBP_DEPENDENCIES)
			set (extraLibs "${CBP_DEPENDENCIES}")
		else ()
			set (extraLibs "")
		endif ()

		if (CBP_WIN32_LIBS OR CBP_VCRUNTIME)
			set (win32Libs "	if (WIN32)\n		set (WIN32_LIBS")
			foreach (lib ${CBP_WIN32_LIBS})
				set (win32Libs "${win32Libs}\n			${lib}.lib")
			endforeach ()
			if (CBP_VCRUNTIME)
				set (win32Libs "${win32Libs}\n			debug vcruntimed.lib ucrtd.lib\n			optimized vcruntime.lib ucrt.lib")
			endif ()

			set (win32Libs "${win32Libs}\n		)\n	endif ()\n")
			set (fullTpl "${fullTpl}${win32Libs}")
		endif ()

		if (extraLibs)
			set (fullTpl "${fullTpl}	target_link_libraries (${CBP_NAME}_s INTERFACE \${WIN32_LIBS} ${extraLibs})")
		endif ()

		foreach (dep ${CBP_DEPENDENCIES})
			string (REPLACE %name% ${dep} depTpl ${staticTpl})
			set (fullTpl "${depTpl}\n${fullTpl}")
		endforeach ()

		set (fullTpl "# ###################################################################\n	# Add target for prebuilt static libraries.\n${fullTpl}")
	else ()
		set (fullTpl "")
	endif ()

	string (REPLACE %name% "${CBP_NAME}" template "${template}")
	string (REPLACE %shared% ${sharedTpl} template "${template}")
	string (REPLACE %static% ${fullTpl} template "${template}")

	file (WRITE "${CMAKE_BINARY_DIR}/Packages/${CBP_NAME}/CMakeLists.txt" ${template})

	
endfunction ()
