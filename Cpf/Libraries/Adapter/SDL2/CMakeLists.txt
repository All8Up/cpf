# ###############################################
set (INCLUDE_FILES
	Include/Adapter/SDL2.hpp
	Include/Adapter/ConsoleApp.hpp
	Include/Adapter/WindowedApp.hpp
	Include/Adapter/Window.hpp
	Include/Adapter/GLContext.hpp
)
set (SOURCE_FILES
	Source/SDL2.cpp
	Source/ConsoleApp.cpp
	Source/WindowedApp.cpp
	Source/Window.cpp
	Source/GLContext.cpp
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

# ###############################################
set (PLUGIN_INCLUDES
	Include/Window.hpp
	Include/SDL2.hpp
)
set (PLUGIN_SOURCES
	Source/Windowx.cpp
	Source/SDL2.cpp
)

add_library (SDL2_plugin SHARED
	${PLUGIN_INCLUDES}
	${PLUGIN_SOURCES}
)
target_compile_definitions (SDL2_plugin
	PRIVATE CPF_BUILD_SDL2
)
target_link_libraries (SDL2_plugin
	Configuration
	Logging
	SDL2-static
	i_Application
)
set_property (TARGET SDL2_plugin
	PROPERTY FOLDER Plugins/Adapter
)
