# ###############################################
set (INTERFACE_FILES
	Interface/Application/iWindow.hpp
	Interface/Application/KeyCode.hpp
	Interface/Application/ScanCode.hpp
	Interface/Application/KeyModifier.hpp
	Interface/Application/MouseButton.hpp
	Interface/Application/OSWindowData.hpp
	Interface/Application/WindowDesc.hpp
	Interface/Application/WindowFlags.hpp
	Interface/Application/iApplication.hpp
	Interface/Application/iApplicationMain.hpp
	Interface/Application/iWindowedApplication.hpp
	Interface/Application/iInputManager.hpp
	Interface/Application/iInputDevice.hpp
	Interface/Application/iMouseDevice.hpp
	Interface/Application/iKeyboardDevice.hpp
	Interface/Application/iJoystickDevice.hpp
	Interface/Application/iClipboard.hpp
)
add_library (i_Application INTERFACE)
target_link_libraries (i_Application INTERFACE Configuration s_Events Plugin)
target_include_directories (i_Application INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
	$<INSTALL_INTERFACE:Interface>
)

# ###############################################
set( INCLUDE_FILES
	Include/Application/Arguments.hpp
	Include/Application/ConsoleCommands.hpp

	Include/Platform/Platform.hpp
	Include/Platform/ConsoleApp.hpp
)
set( SOURCE_FILES
	Source/Application.cpp
	Source/ConsoleCommands.cpp
	Source/${CMAKE_SYSTEM_NAME}/Main.cpp
)

add_library( s_Application STATIC
	${INTERFACE_FILES}
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Application
	PUBLIC CPF_STATIC_APPLICATION CPF_STATIC_PLATFORM
	PRIVATE CPF_BUILD_PLATFORM
)
source_group (Interface FILES ${INTERFACE_FILES})
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( s_Application i_Application s_Memory s_Collections Math s_Events s_PluginHost )

target_include_directories( s_Application PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
	$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}>
)

set_property( TARGET s_Application PROPERTY FOLDER Libraries/Static/Platform )

install( DIRECTORY Include/Application
	DESTINATION Include/Application
	PATTERN *
)
install( DIRECTORY Include/${CMAKE_SYSTEM_NAME}/Platform/Application
	DESTINATION ${CPF_PLATFORM_INCLUDE_DIR}/Platform
	PATTERN *
)


install( TARGETS s_Application
	EXPORT ApplicationConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS i_Application
	EXPORT ApplicationConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT ApplicationConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Application:static GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
