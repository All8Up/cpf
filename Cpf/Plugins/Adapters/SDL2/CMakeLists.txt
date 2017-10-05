# ###############################################
set (INTERFACE_FILES
	Interface/SDL2/CIDs.hpp
)
set (INCLUDE_FILES
	Include/SDL2.hpp
	Include/Window.hpp
	Include/WindowedApplication.hpp
	Include/InputManager.hpp
	Include/InputDevice.hpp
	Include/MouseDevice.hpp
	Include/KeyboardDevice.hpp
	Include/JoystickDevice.hpp
	Include/Clipboard.hpp
)
set (SOURCE_FILES
	Source/SDL2.cpp
	Source/Window.cpp
	Source/WindowedApplication.cpp
	Source/InputDevice.cpp
	Source/InputManager.cpp
	Source/JoystickDevice.cpp
	Source/KeyboardDevice.cpp
	Source/MouseDevice.cpp
	Source/Clipboard.cpp
)

add_library (AdapterSDL2 SHARED
	${INTERFACE_FILES}
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (AdapterSDL2
	PRIVATE CPF_BUILD_AdapterSDL2
)
target_link_libraries (AdapterSDL2
	Configuration
	Logging
	i_Application
	Math
	SDL2
)
target_include_directories (AdapterSDL2
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

set_property (TARGET AdapterSDL2 PROPERTY FOLDER Plugins/Adapters)

# ###############################################
add_library (i_AdapterSDL2 INTERFACE)
target_include_directories (i_AdapterSDL2
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET AdapterSDL2 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AdapterSDL2> ${CPF_COMMON_PLUGINS}/AdapterSDL2.cfp
)
