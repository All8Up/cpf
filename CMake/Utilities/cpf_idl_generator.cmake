function (cpf_idl_generator)
	set (options
		REQUIRED
		MAKE_RELEASE
	)
	set (single_value
		TARGET
		BASE
		OUTPUT_ROOT
		OUTPUT_BASE
		IDL_ROOT
	)
	set (multi_value
		FILES
	)
	cmake_parse_arguments (IDL "${options}" "${single_value}" "${multi_value}" ${ARGN})

	set (generated_files "")
	set (lang_target "cpp")
	set (lang_dir "CPP")
	set (out_extension ".hpp")
	foreach (file ${IDL_FILES})
		set_source_files_properties (${file} PROPERTIES HEADER_FILE_ONLY TRUE)

		get_filename_component (directory ${file} DIRECTORY)
		file (RELATIVE_PATH relative ${IDL_IDL_ROOT} ${file})
		get_filename_component (sub_directory ${relative} DIRECTORY)
		get_filename_component (fileName ${file} NAME_WE)

		set (target_file "${IDL_OUTPUT_ROOT}/${lang_dir}/${IDL_OUTPUT_BASE}/${sub_directory}/${fileName}${out_extension}")

		add_custom_command (OUTPUT ${target_file}
			DEPENDS ${file}
			COMMAND ${CPF_OS_BIN_DIR}/IDL --${lang_target}
				--input="${file}"
				--output="${target_file}"
		)

		LIST (APPEND generated_files ${target_file})
		source_group (IDL\\${sub_directory} FILES ${file})
		source_group (Include\\${sub_directory} FILES ${target_file})
	endforeach ()

	add_custom_target (${IDL_TARGET} SOURCES ${generated_files} ${IDL_FILES})
	set_property (TARGET ${IDL_TARGET} PROPERTY FOLDER ${IDL_OUTPUT_BASE})
	add_dependencies (${IDL_BASE} ${IDL_TARGET})

	if (IDL_MAKE_RELEASE)
		set (archive_files "")
		foreach (filename ${generated_files})
			file (RELATIVE_PATH relative "${CMAKE_BINARY_DIR}/Generated" ${filename})
			list (APPEND archive_files "${relative}")
		endforeach ()

		add_custom_target(MakeRelease_${IDL_TARGET}
			WORKING_DIRECTORY
				"${CMAKE_BINARY_DIR}/Generated"
			COMMAND
				${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/Releases"
			COMMAND
			    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_BINARY_DIR}/Releases/${lang_dir}_${IDL_TARGET}.zip" --format=zip ${archive_files}
		)
		set_property (TARGET MakeRelease_${IDL_TARGET} PROPERTY FOLDER Releases)
	endif ()
endfunction (cpf_idl_generator)
