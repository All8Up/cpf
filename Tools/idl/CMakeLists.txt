find_package (Java COMPONENTS Runtime)

if (Java_JAVA_EXECUTABLE)
	set (GrammarDir "${CPF_GENERATED}/IDLGrammar")
	add_custom_target(GenerateIDLParser
		COMMAND
			${CMAKE_COMMAND} -E make_directory ${GrammarDir}
		COMMAND
			"${Java_JAVA_EXECUTABLE}" -jar "${CPF_BIN_DIR}/antlr-4.7-complete.jar" -Werror -Dlanguage=Cpp -o ${GrammarDir} -no-listener -visitor ${CMAKE_CURRENT_LIST_DIR}/IDLLexer.g4 ${CMAKE_CURRENT_LIST_DIR}/IDLParser.g4
	)
	set_property (TARGET GenerateIDLParser PROPERTY FOLDER Tools)

	FILE(GLOB GeneratedFiles ${CPF_GENERATED}/IDLGrammar/*.*)

	#
	set (WITH_DEMO OFF CACHE BOOL "" FORCE)
	cmake_policy (SET CMP0054 NEW)
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Antlr4/Cpp")
	set_property (TARGET antlr4_static PROPERTY FOLDER Tools/Antlr4)

	set (VisitorIncludes
		Include/Visitor/Visitor.hpp
		Include/Visitor/Literal.hpp
		Include/Visitor/QualifiedIdentifier.hpp
		Include/Visitor/Enum.hpp
		Include/Visitor/DataMember.hpp
	)
	set (VisitorSources
		Source/Visitor/Visitor.cpp
		Source/Visitor/Literal.cpp
		Source/Visitor/QualifiedIdentifier.cpp
		Source/Visitor/Enum.cpp
		Source/Visitor/DataMember.cpp
	)
	set (GeneratorsIncludes
		Include/Generators/Generator.hpp
		Include/Generators/CodeWriter.hpp
	)
	set (GeneratorsSources
		Source/Generators/Generator.cpp
		Source/Generators/CodeWriter.cpp
	)

	set (Includes
		Include/Main.hpp
	)
	set (Sources
		Source/Main.cpp
	)

	set (IDLIncludes
		Include/IDL/SymbolTable.hpp
	)
	set (IDLSources
		Source/IDL/SymbolTable.cpp
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
	set (IDLParseTreeIncludes
		Include/IDL/ParseTree/Visitor.hpp
	)
	set (IDLParseTreeSources
		Source/IDL/ParseTree/Visitor.cpp
	)

	add_executable (IDL
		${Includes}
		${Sources}
		${IDLIncludes}
		${IDLSources}
		${IDLCodeGenIncludes}
		${IDLCodeGenSources}
		${IDLParseTreeIncludes}
		${IDLParseTreeSources}

		${GeneratedFiles}
	)
	set_property (TARGET IDL PROPERTY FOLDER Tools)

	source_group (Includes FILES ${Includes})
	source_group (Sources FILES ${Sources})
	source_group (Includes\\IDL FILES ${IDLIncludes})
	source_group (Sources\\IDL FILES ${IDLSources})
	source_group (Includes\\IDL\\CodeGen FILES ${IDLCodeGenIncludes})
	source_group (Sources\\IDL\\CodeGen FILES ${IDLCodeGenSources})
	source_group (Includes\\IDL\\ParseTree FILES ${IDLParseTreeIncludes})
	source_group (Sources\\IDL\\ParseTree FILES ${IDLParseTreeSources})

	source_group (Generated FILES ${GeneratedFiles})

	target_include_directories (IDL
		PUBLIC
			Include
			${CPF_GENERATED}/IDLGrammar
			${CMAKE_CURRENT_SOURCE_DIR}/Antlr4/Cpp/runtime/src
	)
	target_compile_definitions (IDL
		PUBLIC
			ANTLR4CPP_STATIC
			UNICODE
			_UNICODE
	)
	target_link_libraries (IDL
		antlr4_static
		Core_s
		Application_s
		gflags_static
	)
	target_compile_options (IDL PRIVATE /wd4100)

	if (WIN32)
		target_compile_options (IDL
			PUBLIC "/GR"
		)
		target_compile_options (antlr4_static
			PUBLIC "/GR"
		)
		target_compile_definitions (antlr4_static
			PUBLIC
				ANTLR4CPP_STATIC
				UNICODE
				_UNICODE
		)
	endif ()

else ()
	message (WARNING "Must have the Java runtime in order to build the IDL tool.")
endif ()
