if (NOT CPF_PLUGIN_BINARY_PlatformDesktopSDL2)
	set (BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)
	set (SDL_SHARED OFF CACHE BOOL "" FORCE)
	set (SDL_STATIC ON CACHE BOOL "" FORCE)
	set (SDL_RENDER OFF CACHE BOOL "" FORCE)
	set (SDL_THREADS OFF CACHE BOOL "" FORCE)
	set (SDL_TIMERS OFF CACHE BOOL "" FORCE)
	set (SDL_FILE ON CACHE BOOL "" FORCE)
	set (SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
	add_subdirectory (External/SDL2-2.0.7)
	set_property (TARGET SDL2main PROPERTY FOLDER Plugins/Drivers/Platform/External/SDL2)
	set_property (TARGET SDL2-static PROPERTY FOLDER Plugins/Drivers/Platform/External/SDL2)
	set_property (TARGET uninstall PROPERTY FOLDER Plugins/Drivers/Platform/External/SDL2)
	target_compile_options (SDL2-static PRIVATE /wd4267 /wd4018 /wd4311 /wd4996 /wd4312)

	set (INCLUDE_FILES
		Include/Platform.hpp
		Include/EventLoop.hpp
		Include/Window.hpp
		Include/MouseDevice.hpp
		Include/KeyboardDevice.hpp
		Include/Clipboard.hpp
	)
	set (SOURCE_FILES
		Source/Platform.cpp
		Source/Plugin.cpp
		Source/EventLoop.cpp
		Source/Window.cpp
		Source/MouseDevice.cpp
		Source/KeyboardDevice.cpp
		Source/Clipboard.cpp
	)

	add_library (PlatformDesktopSDL2 SHARED
		${INCLUDE_FILES}
		${SOURCE_FILES}
	)

	target_include_directories (PlatformDesktopSDL2
		PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/External/SDL2-2.0.7/include>
	)
	if (WIN32)
		set (WIN32_LIBS
			debug vcruntimed.lib ucrtd.lib
			optimized vcruntime.lib ucrt.lib
		)
	endif ()

	target_link_libraries (PlatformDesktopSDL2
		PRIVATE
			Core_s SDL2-static ${WIN32_LIBS}
	)

	set_property (TARGET PlatformDesktopSDL2
		PROPERTY FOLDER Plugins/Drivers/Platform
	)

	if (CPF_BUILD_STATIC_VARIANTS)
		add_library (PlatformDesktopSDL2_s STATIC
			${INCLUDE_FILES}
			${SOURCE_FILES}
		)

		target_include_directories (PlatformDesktopSDL2_s
			PRIVATE
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
				$<INSTALL_INTERFACE:Include>
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/External/SDL2-2.0.7/include>
		)
		target_compile_definitions (PlatformDesktopSDL2_s
			PUBLIC
				PlatformDesktopSDL2_STATIC=1
				CPF_PLUGIN_STATIC
		)

		target_link_libraries (PlatformDesktopSDL2_s
			PRIVATE
				Core_s SDL2-static ${WIN32_LIBS}
		)
		set_property (TARGET PlatformDesktopSDL2_s
			PROPERTY FOLDER Plugins/Drivers/Platform
		)
	endif ()

	add_custom_command (
		TARGET PlatformDesktopSDL2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlatformDesktopSDL2> ${CPF_COMMON_PLUGINS}/PlatformDesktopSDL2.cfp
	)

	cpf_binary_plugin(
		SHARED
		STATIC
		NAME
			PlatformDesktopSDL2
		DEPENDENCIES
			SDL2-static
		WIN32_LIBS
			Imm32 Winmm Mincore Version
		VCRUNTIME
	)
endif ()
