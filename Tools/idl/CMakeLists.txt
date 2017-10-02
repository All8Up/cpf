set (WITH_DEMO OFF CACHE BOOL "" FORCE)
cmake_policy (SET CMP0054 NEW)
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Antlr4/Cpp")
set_property (TARGET antlr4_static PROPERTY FOLDER External/Antlr4)

set (LexerFiles
	Generated/IDLLexer.h
	Generated/IDLLexer.tokens
	Generated/IDLLexer.cpp
)
set (ParserFiles
	Generated/IDLParser.h
	Generated/IDLParser.tokens
	Generated/IDLParser.cpp
)
set (ListenerFiles
	Generated/IDLParserBaseListener.h
	Generated/IDLParserBaseListener.cpp
	Generated/IDLParserListener.h
	Generated/IDLParserListener.cpp
)
set (VisitorFiles
	Generated/IDLParserBaseVisitor.h
	Generated/IDLParserBaseVisitor.cpp
	Generated/IDLParserVisitor.h
	Generated/IDLParserVisitor.cpp
)

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
)
set (IDLCodeGenSources
	Source/IDL/CodeGen/CodeWriter.cpp
	Source/IDL/CodeGen/Context.cpp
	Source/IDL/CodeGen/Generator.cpp
	Source/IDL/CodeGen/CppGenerator.cpp
	Source/IDL/CodeGen/RustGenerator.cpp
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

	${LexerFiles}
	${ParserFiles}
	${ListenerFiles}
	${VisitorFiles}
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

source_group (Grammar\\Lexer FILES ${LexerFiles})
source_group (Grammar\\Parser FILES ${ParserFiles})
source_group (Grammar\\Listener FILES ${ListenerFiles})
source_group (Grammar\\Visitor FILES ${VisitorFiles})

target_include_directories (IDL
	PUBLIC
		Include
		Generated
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
	s_Collections
	s_IO
	s_ANSI_C_FileSystem
	GOM
	Events
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
