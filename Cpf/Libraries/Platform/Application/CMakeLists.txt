# ###############################################
set (IDL_INTERFACES
#	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iApplication.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iClipboard.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iInputDevice.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iJoystickDevice.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iKeyboardDevice.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iMouseDevice.idl
#	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iWindow.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iWindowedApplication.idl
)

CPF_GEN_GOM (CPP_INTERFACES cpp
	hpp
	${CPF_GENERATED}/CPP/Application
	${IDL_INTERFACES}
)

set (IDL_DESCRIPTORS
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/WindowDesc.idl
)
CPF_GEN_GOM (CPP_DESCRIPTORS cpp
	hpp
	${CPF_GENERATED}/CPP/Application
	${IDL_DESCRIPTORS}
)

set (IDL_FLAGS
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/KeyCode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/KeyModifiers.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/MouseButton.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ScanCode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/WindowFlags.idl
)
CPF_GEN_GOM (CPP_FLAGS cpp
	hpp
	${CPF_GENERATED}/CPP/Application
	${IDL_FLAGS}
)

set (IDL_STRUCTURES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/OSWindowData.idl
)
CPF_GEN_GOM (CPP_STRUCTURES cpp
	hpp
	${CPF_GENERATED}/CPP/Application
	${IDL_STRUCTURES}
)

# ###############################################
set (INTERFACE_FILES
	Interface/Application/iWindow.hpp
	Interface/Application/iApplication.hpp
	Interface/Application/iApplicationMain.hpp
	Interface/Application/iInputManager.hpp
)
add_library (i_Application INTERFACE)
target_link_libraries (
	i_Application
	INTERFACE Configuration Events Plugin
)
target_include_directories (i_Application
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
		${CPF_GENERATED}/CPP
)

# ###############################################
set( INCLUDE_FILES
	Include/Platform/Platform.hpp
)
set( SOURCE_FILES
	Source/${CMAKE_SYSTEM_NAME}/Main.cpp
)

add_library (s_Application STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${CPP_DESCRIPTORS}
	${IDL_DESCRIPTORS}
	${CPP_STRUCTURES}
	${IDL_STRUCTURES}
	${CPP_INTERFACES}
	${IDL_INTERFACES}
	${INTERFACE_FILES}
	${CPP_FLAGS}
	${IDL_FLAGS}
)
target_compile_definitions (s_Application
	PUBLIC
		CPF_STATIC_APPLICATION
		CPF_STATIC_PLATFORM
	PRIVATE
		CPF_BUILD_PLATFORM
)

source_group (IDL\\Interfaces FILES ${IDL_INTERFACES})
source_group (IDL\\Descriptors FILES ${IDL_DESCRIPTORS})
source_group (IDL\\Flags FILES ${IDL_FLAGS})
source_group (IDL\\Structures FILES ${IDL_STRUCTURES})

source_group (Interface FILES ${INTERFACE_FILES})
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Descriptors FILES ${CPP_DESCRIPTORS})
source_group (Headers\\Interfaces FILES ${CPP_INTERFACES})
source_group (Headers\\Flags FILES ${CPP_FLAGS})
source_group (Headers\\Structures FILES ${CPP_STRUCTURES})
source_group (Sources FILES ${SOURCE_FILES})

target_link_libraries (s_Application
	s_Memory
	s_Collections
	Math
	Events
	s_PluginHost
	Logging
)

target_include_directories (s_Application
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CMAKE_SYSTEM_NAME}>
		$<INSTALL_INTERFACE:Include/${CMAKE_SYSTEM_NAME}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}/${CPF_TARGET_CPU_DIR}>
		${CPF_GENERATED}/CPP
)

set_property (TARGET s_Application PROPERTY FOLDER Libraries/Static/Platform)

add_dependencies (i_Application s_Application)

#[[
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
]]#


# ###############################################
MakeUnitTests( LIBRARY Application:static GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
