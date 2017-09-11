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
set (IDLTreeIncludes
	Include/IDLTree/Const.hpp
	Include/IDLTree/Enum.hpp
	Include/IDLTree/Import.hpp
	Include/IDLTree/Interface.hpp
	Include/IDLTree/Namespace.hpp
	Include/IDLTree/Struct.hpp
	Include/IDLTree/Symbol.hpp
	Include/IDLTree/SymbolTable.hpp
	Include/IDLTree/Types.hpp
)
set (IDLTreeSources
	Source/IDLTree/Const.cpp
	Source/IDLTree/Enum.cpp
	Source/IDLTree/Import.cpp
	Source/IDLTree/Interface.cpp
	Source/IDLTree/Namespace.cpp
	Source/IDLTree/Struct.cpp
	Source/IDLTree/Symbol.cpp
	Source/IDLTree/SymbolTable.cpp
	Source/IDLTree/Types.cpp
)
set (GeneratorsIncludes
	Include/Generators/Generator.hpp
	Include/Generators/CodeWriter.hpp
)
set (GeneratorsSources
	Source/Generators/Generator.cpp
	Source/Generators/CodeWriter.cpp
)
set (GeneratorsCppIncludes
	Include/Generators/Cpp/Cpp.hpp
)
set (GeneratorsCppSources
	Source/Generators/Cpp/Cpp.cpp
)
set (GeneratorsPython3Includes
	Include/Generators/Python3/Python3.hpp
)
set (GeneratorsPython3Sources
	Source/Generators/Python3/Python3.cpp
)
set (GeneratorsRustIncludes
	Include/Generators/Rust/Rust.hpp
)
set (GeneratorsRustSources
	Source/Generators/Rust/Rust.cpp
)

set (Includes
	Include/Main.hpp
)
set (Sources
	Source/Main.cpp
)

set (IDLIncludes
	Include/IDL/Settings.hpp
	Include/IDL/SymbolTable.hpp
	Include/IDL/SyntaxTree.hpp
)
set (IDLSources
	Source/IDL/Settings.cpp
	Source/IDL/SymbolTable.cpp
	Source/IDL/SyntaxTree.cpp
)

set (IDLCodeGenIncludes
	Include/IDL/CodeGen/CodeWriter.hpp
	Include/IDL/CodeGen/Context.hpp
	Include/IDL/CodeGen/Generator.hpp
)
set (IDLCodeGenSources
	Source/IDL/CodeGen/CodeWriter.cpp
	Source/IDL/CodeGen/Context.cpp
	Source/IDL/CodeGen/Generator.cpp
)

set (IDLCodeGenCppIncludes
	Include/IDL/CodeGen/Cpp/CodeGen.hpp
)
set (IDLCodeGenCppSources
	Source/IDL/CodeGen/Cpp/CodeGen.cpp
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
	${IDLCodeGenCppIncludes}
	${IDLCodeGenCppSources}
	${IDLParseTreeIncludes}
	${IDLParseTreeSources}

	${LexerFiles}
	${ParserFiles}
	${ListenerFiles}
	${VisitorFiles}
#[[
	${VisitorIncludes}
	${VisitorSources}
	${IDLTreeIncludes}
	${IDLTreeSources}
	${GeneratorsIncludes}
	${GeneratorsSources}
	${GeneratorsCppIncludes}
	${GeneratorsCppSources}
	${GeneratorsPython3Includes}
	${GeneratorsPython3Sources}
	${GeneratorsRustIncludes}
	${GeneratorsRustSources}
#]]
)
set_property (TARGET IDL PROPERTY FOLDER Tools)

source_group (Includes FILES ${Includes})
source_group (Sources FILES ${Sources})
source_group (Includes\\IDL FILES ${IDLIncludes})
source_group (Sources\\IDL FILES ${IDLSources})
source_group (Includes\\IDL\\CodeGen FILES ${IDLCodeGenIncludes})
source_group (Sources\\IDL\\CodeGen FILES ${IDLCodeGenSources})
source_group (Includes\\IDL\\CodeGen\\Cpp FILES ${IDLCodeGenCppIncludes})
source_group (Sources\\IDL\\CodeGen\\Cpp FILES ${IDLCodeGenCppSources})
source_group (Includes\\IDL\\ParseTree FILES ${IDLParseTreeIncludes})
source_group (Sources\\IDL\\ParseTree FILES ${IDLParseTreeSources})

source_group (Grammar\\Lexer FILES ${LexerFiles})
source_group (Grammar\\Parser FILES ${ParserFiles})
source_group (Grammar\\Listener FILES ${ListenerFiles})
source_group (Grammar\\Visitor FILES ${VisitorFiles})

#[[
source_group (Includes\\Visitor FILES ${VisitorIncludes})
source_group (Sources\\Visitor FILES ${VisitorSources})
source_group (Includes\\IDLTree FILES ${IDLTreeIncludes})
source_group (Sources\\IDLTree FILES ${IDLTreeSources})
source_group (Includes\\Generators FILES ${GeneratorsIncludes})
source_group (Sources\\Generators FILES ${GeneratorsSources})
source_group (Includes\\Generators\\Cpp FILES ${GeneratorsCppIncludes})
source_group (Sources\\Generators\\Cpp FILES ${GeneratorsCppSources})
source_group (Includes\\Generators\\Python3 FILES ${GeneratorsPython3Includes})
source_group (Sources\\Generators\\Python3 FILES ${GeneratorsPython3Sources})
source_group (Includes\\Generators\\Rust FILES ${GeneratorsRustIncludes})
source_group (Sources\\Generators\\Rust FILES ${GeneratorsRustSources})
#]]

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
	Patterns
	Events
)

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

add_executable (Test_IDL
	UnitTest/Test_All.hpp
	../../Libraries/Core/Test/UnitTestMain.cpp
)
add_test (IDL Test_IDL COMMAND Test_IDL)
target_link_libraries (Test_IDL gmock Std antlr4_static)
target_include_directories (Test_IDL
	PUBLIC
		Include
		Generated
		${CMAKE_CURRENT_SOURCE_DIR}/Antlr4/Cpp/runtime/src
		UnitTest
)
set_property (TARGET Test_IDL PROPERTY FOLDER UnitTests/IDL)
