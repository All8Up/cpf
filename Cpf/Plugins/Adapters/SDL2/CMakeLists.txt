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

add_library (Adapter_SDL2 SHARED
	${INTERFACE_FILES}
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (Adapter_SDL2
	PRIVATE CPF_BUILD_ADAPTER_SDL2
)
target_link_libraries (Adapter_SDL2
	Configuration
	Logging
	i_Application
	Math
	SDL2
)
target_include_directories (Adapter_SDL2
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

set_property (TARGET Adapter_SDL2 PROPERTY FOLDER Plugins/Adapters)

# ###############################################
add_library (i_Adapter_SDL2 INTERFACE)
target_include_directories (i_Adapter_SDL2
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Adapter_SDL2 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Adapter_SDL2> ${CPF_COMMON_PLUGINS}/Adapter_SDL2.cfp
)
