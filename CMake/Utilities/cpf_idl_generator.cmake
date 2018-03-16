function (cpf_idl_generator)
	set (options REQUIRED)
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
endfunction (cpf_idl_generator)
