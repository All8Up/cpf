set (HEADER_FILES
	Include/Networked.hpp
)
set (SOURCE_FILES
	Source/Networked.cpp
)

add_executable (Networked WIN32
	${HEADER_FILES}
	${SOURCE_FILES}
	${DataFiles}
)
target_include_directories (Networked
	PUBLIC Include
)
target_link_libraries (Networked
	s_Concurrency
	s_SDL2
	Logging
	s_ANSI_C_FileSystem
	cereal
	asio
)

set_property (TARGET Networked PROPERTY FOLDER Experimental/Serialization/Networked)
