set (HEADER_FILES
	Include/Integration.hpp
)
set (SOURCE_FILES
	Source/Integration.cpp
)

add_executable (BgfxIntegration WIN32
	${HEADER_FILES}
	${SOURCE_FILES}
)
target_include_directories (BgfxIntegration
	PUBLIC Include
)
target_link_libraries (BgfxIntegration
	s_Concurrency
	s_SDL2
	Logging
	s_ANSI_C_FileSystem
	s_EntityService
	s_Resources
	bx
	bgfx
)
target_compile_definitions (BgfxIntegration PUBLIC)

set_property (TARGET BgfxIntegration PROPERTY FOLDER Experimental/Bgfx)
