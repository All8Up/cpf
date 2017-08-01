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

set (INCLUDE_FILES
	Include/Main.hpp
	Include/Listener.hpp
	Include/Handlers.hpp
)
set (SOURCE_FILES
	Source/Main.cpp
	Source/Listener.cpp
	Source/Handlers.cpp
)

add_executable (IDL
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${LexerFiles}
	${ParserFiles}
	${ListenerFiles}
)
set_property (TARGET IDL PROPERTY FOLDER Tools)

source_group (Grammar\\Lexer FILES ${LexerFiles})
source_group (Grammar\\Parser FILES ${ParserFiles})
source_group (Grammar\\Listener FILES ${ListenerFiles})
source_group (Includes FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

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
