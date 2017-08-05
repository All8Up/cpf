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

set (IncludeFiles
	Include/Main.hpp
	Include/Visitor.hpp
	Include/Handlers.hpp
)
set (SourceFiles
	Source/Main.cpp
	Source/Visitor.cpp
	Source/Handlers.cpp
)
set (ASTIncludes
	Include/AST/Alias.hpp
	Include/AST/Const.hpp
	Include/AST/DataMember.hpp
	Include/AST/Enum.hpp
	Include/AST/ForwardRef.hpp
	Include/AST/Function.hpp
	Include/AST/Import.hpp
	Include/AST/Interface.hpp
	Include/AST/Namespace.hpp
	Include/AST/Parameter.hpp
	Include/AST/Path.hpp
	Include/AST/Struct.hpp
	Include/AST/Symbol.hpp
	Include/AST/SymbolTable.hpp
	Include/AST/Types.hpp
)
set (ASTSources
	Source/AST/Alias.cpp
	Source/AST/Const.cpp
	Source/AST/DataMember.cpp
	Source/AST/Enum.cpp
	Source/AST/ForwardRef.cpp
	Source/AST/Function.cpp
	Source/AST/Import.cpp
	Source/AST/Interface.cpp
	Source/AST/Namespace.cpp
	Source/AST/Parameter.cpp
	Source/AST/Path.cpp
	Source/AST/Struct.cpp
	Source/AST/Symbol.cpp
	Source/AST/SymbolTable.cpp
	Source/AST/Types.cpp
)
set (GeneratorsIncludes
	Include/Generators/Generator.hpp
)
set (GeneratorsSources
	Source/Generators/Generator.cpp
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

add_executable (IDL
	${IncludeFiles}
	${SourceFiles}
	${ASTIncludes}
	${ASTSources}
	${GeneratorsIncludes}
	${GeneratorsSources}
	${GeneratorsCppIncludes}
	${GeneratorsCppSources}
	${GeneratorsPython3Includes}
	${GeneratorsPython3Sources}
	${GeneratorsRustIncludes}
	${GeneratorsRustSources}
	${LexerFiles}
	${ParserFiles}
	${ListenerFiles}
	${VisitorFiles}
)
set_property (TARGET IDL PROPERTY FOLDER Tools)

source_group (Grammar\\Lexer FILES ${LexerFiles})
source_group (Grammar\\Parser FILES ${ParserFiles})
source_group (Grammar\\Listener FILES ${ListenerFiles})
source_group (Grammar\\Visitor FILES ${VisitorFiles})
source_group (Includes FILES ${IncludeFiles})
source_group (Sources FILES ${SourceFiles})
source_group (Includes\\AST FILES ${ASTIncludes})
source_group (Sources\\AST FILES ${ASTSources})
source_group (Includes\\Generators FILES ${GeneratorsIncludes})
source_group (Sources\\Generators FILES ${GeneratorsSources})
source_group (Includes\\Generators\\Cpp FILES ${GeneratorsCppIncludes})
source_group (Sources\\Generators\\Cpp FILES ${GeneratorsCppSources})
source_group (Includes\\Generators\\Python3 FILES ${GeneratorsPython3Includes})
source_group (Sources\\Generators\\Python3 FILES ${GeneratorsPython3Sources})
source_group (Includes\\Generators\\Rust FILES ${GeneratorsRustIncludes})
source_group (Sources\\Generators\\Rust FILES ${GeneratorsRustSources})

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
)

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
