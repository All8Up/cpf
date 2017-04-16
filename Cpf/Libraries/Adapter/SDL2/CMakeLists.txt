#[[
# ###############################################
set (INCLUDE_FILES
	Include/Adapter/WindowedApp.hpp
)
set (SOURCE_FILES
	Source/WindowedApp.cpp
)

add_library (s_SDL2 STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (s_SDL2
	PUBLIC CPF_STATIC_SDL2
	PRIVATE CPF_BUILD_SDL2
)
target_compile_definitions (s_SDL2
	PRIVATE CPF_BUILD_SDL2
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries (s_SDL2
	Configuration
	Logging
	s_Application
	Math
	SDL2-static
)

target_include_directories (s_SDL2
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories (s_SDL2
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

set_property (TARGET s_SDL2 PROPERTY FOLDER Libraries/Static/Adapter)
]]#
