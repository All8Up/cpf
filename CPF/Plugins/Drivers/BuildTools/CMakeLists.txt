if (NOT CPF_PLUGIN_BINARY_IDLParser)
	# Build external antrl4 library.
	set (WITH_DEMO OFF CACHE BOOL "" FORCE)
	cmake_policy (SET CMP0054 NEW)
	add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/External/Antlr4/Cpp")
	set_property (TARGET antlr4_static PROPERTY FOLDER CPF/External)

	find_package (Java COMPONENTS Runtime)

	if (Java_JAVA_EXECUTABLE)
		set (GrammarDir "${CPF_GENERATED}/IDLGrammar")
		set (ParserFiles
			${GrammarDir}/IDLLexer.cpp
			${GrammarDir}/IDLLexer.h
			${GrammarDir}/IDLLexer.tokens
			${GrammarDir}/IDLParser.cpp
			${GrammarDir}/IDLParser.h
			${GrammarDir}/IDLParser.tokens
			${GrammarDir}/IDLParserBaseVisitor.cpp
			${GrammarDir}/IDLParserBaseVisitor.h
			${GrammarDir}/IDLParserVisitor.cpp
			${GrammarDir}/IDLParserVisitor.h
		)
		foreach (f ${ParserFiles})
			set_source_files_properties (${f} PROPERTIES GENERATED TRUE)
		endforeach ()

		add_library (IDLParser_Gen STATIC
			${ParserFiles}
			${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLLexer.g4
			${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLParser.g4
		)
		target_include_directories (IDLParser_Gen
			PUBLIC
				${CPF_GENERATED}/IDLGrammar
				${CMAKE_CURRENT_LIST_DIR}/External/Antlr4/Cpp/runtime/src
		)
		target_compile_definitions (IDLParser_Gen
			PUBLIC
				ANTLR4CPP_STATIC
				UNICODE
				_UNICODE
		)
		add_custom_command (
			TARGET IDLParser_Gen
			PRE_BUILD
			DEPENDS
				${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLLexer.g4
				${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLParser.g4
			COMMAND
				${CMAKE_COMMAND} -E make_directory ${GrammarDir}
			COMMAND
				"${Java_JAVA_EXECUTABLE}" -jar "${CPF_BIN_DIR}/antlr-4.7-complete.jar" -Werror -Dlanguage=Cpp -o ${GrammarDir} -no-listener -visitor ${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLLexer.g4 ${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLParser.g4
		)


		# ###############################################
		set (INCLUDE_FILES
			${CMAKE_CURRENT_LIST_DIR}/Include/IDLVisitor.hpp
			${CMAKE_CURRENT_LIST_DIR}/Include/SymbolTable.hpp
			${CMAKE_CURRENT_LIST_DIR}/Include/IDLParser.hpp
		)
		set (SOURCE_FILES
			${CMAKE_CURRENT_LIST_DIR}/Source/IDLVisitor.cpp
			${CMAKE_CURRENT_LIST_DIR}/Source/IDLParser.cpp
			${CMAKE_CURRENT_LIST_DIR}/Source/Plugin.cpp
			${CMAKE_CURRENT_LIST_DIR}/Source/SymbolTable.cpp
		)

		set (IDLCodeGenIncludes
			Include/IDL/CodeGen/CodeWriter.hpp
			Include/IDL/CodeGen/Context.hpp
			Include/IDL/CodeGen/Generator.hpp
			Include/IDL/CodeGen/CppGenerator.hpp
			Include/IDL/CodeGen/RustGenerator.hpp
			Include/IDL/CodeGen/CSharpGenerator.hpp
		)
		set (IDLCodeGenSources
			Source/IDL/CodeGen/CodeWriter.cpp
			Source/IDL/CodeGen/Context.cpp
			Source/IDL/CodeGen/Generator.cpp
			Source/IDL/CodeGen/CppGenerator.cpp
			Source/IDL/CodeGen/RustGenerator.cpp
			Source/IDL/CodeGen/CSharpGenerator.cpp
		)

		add_library (IDLParser SHARED
			${INCLUDE_FILES}
			${SOURCE_FILES}
			${IDLCodeGenIncludes}
			${IDLCodeGenSources}
		)
		target_include_directories (IDLParser
			PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		)
		target_compile_definitions (IDLParser
			PUBLIC
				ANTLR4CPP_STATIC
		)
		target_compile_definitions (IDLParser PUBLIC CPF_STATIC_IO)
		target_link_libraries (IDLParser
			LINK_PUBLIC
				Core_s
				antlr4_static
				IDLParser_Gen
		)
		target_compile_options (IDLParser PRIVATE /wd4100)

		add_library (IDLParser_s STATIC
			${INCLUDE_FILES}
			${SOURCE_FILES}
			${IDLCodeGenIncludes}
			${IDLCodeGenSources}
		)
		target_include_directories (IDLParser_s
			PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		)
		target_compile_definitions (IDLParser_s
			PUBLIC
				ANTLR4CPP_STATIC
				UNICODE
				_UNICODE
		)
		target_compile_definitions (IDLParser_s PUBLIC CPF_STATIC_IO CPF_PLUGIN_STATIC)
		target_link_libraries (IDLParser_s
			LINK_PUBLIC
				Core_s
				antlr4_static
				IDLParser_Gen
		)
		target_compile_options (IDLParser_s PRIVATE /wd4100)

		if (WIN32)
			target_compile_options (IDLParser
				PUBLIC "/GR"
			)
			target_compile_options (antlr4_static
				PUBLIC "/GR"
			)
			target_compile_definitions (antlr4_static
				PUBLIC
					UNICODE
					_UNICODE
			)
			target_compile_options (IDLParser_s
				PUBLIC "/GR"
			)
		endif ()

		set_property (TARGET IDLParser PROPERTY FOLDER Plugins/Drivers/BuildTools)
		set_property (TARGET IDLParser_s PROPERTY FOLDER Plugins/Drivers/BuildTools)
		set_property (TARGET IDLParser_Gen PROPERTY FOLDER Plugins/Drivers/BuildTools)

		if (MSVC)
			target_compile_options (IDLParser_Gen PRIVATE /wd4100)
		endif ()

		# ###############################################
		source_group (IDL FILES ${IDL_FILES})
		source_group (Include FILES ${INCLUDE_FILES} ${CPP_IDL_FILES})
		source_group (Include\\IDL FILES ${IDLIncludes})
		source_group (Include\\IDL\\CodeGen FILES ${IDLCodeGenIncludes})
		source_group (Source FILES ${SOURCE_FILES})
		source_group (Source\\IDL FILES ${IDLSources})
		source_group (Source\\IDL\\CodeGen FILES ${IDLCodeGenSources})
		source_group (Grammar FILES ${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLLexer.g4 ${CMAKE_CURRENT_LIST_DIR}/Grammar/IDLParser.g4)
		source_group (Generated FILES ${ParserFiles})

		add_library (i_IDLParser INTERFACE)
		target_include_directories (i_IDLParser
			INTERFACE
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
				$<INSTALL_INTERFACE:Interface>
		)

		add_custom_command (
			TARGET IDLParser POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:IDLParser> ${CPF_COMMON_PLUGINS}/IDLParser.cfp
		)

		# ###############################################
		cpf_binary_plugin(
			SHARED
			STATIC
			NAME
				IDLParser
			DEPENDENCIES
				antlr4_static
				IDLParser_Gen
		)
	else ()
		message (WARNING "Must have the Java runtime in order to build the IDL tool.")
	endif ()
endif ()
