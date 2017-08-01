#set (WITH_DEMO OFF CACHE BOOL "" FORCE)
#cmake_policy (SET CMP0054 NEW)
#add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Antlr4/Cpp")
#set_property (TARGET antlr4_static PROPERTY FOLDER External/Antlr4)

file (GLOB_RECURSE antlr4_h "Antlr4/*.h")
file (GLOB_RECURSE antlr4_cpp "Antlr4/*.cpp")

add_executable (IDL
	Source/Main.cpp
	Generated/IDLLexer.h
	Generated/IDLLexer.cpp
	Generated/IDLLexer.tokens
	Generated/IDLParser.h
	Generated/IDLParser.cpp
	Generated/IDLParser.tokens
	Generated/IDLParserBaseListener.h
	Generated/IDLParserBaseListener.cpp
	Generated/IDLParserListener.h
	Generated/IDLParserListener.cpp
	${antlr4_h}
	${antlr4_cpp}
)
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

#target_link_libraries (IDL
#	antlr4_static
#)

target_compile_options (IDL
	PUBLIC "/GR"
)
#target_compile_options (antlr4_static
#	PUBLIC "/GR"
#)
#target_compile_definitions (antlr4_static
#	PUBLIC
#		ANTLR4CPP_STATIC
#		UNICODE
#		_UNICODE
#)
