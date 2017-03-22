# ###############################################
set (INCLUDE_FILES
	Include/Adapter/SDL2.hpp
	Include/Adapter/ConsoleApp.hpp
	Include/Adapter/WindowedApp.hpp
	Include/Adapter/PowerManagement.hpp
	Include/Adapter/Window.hpp
	Include/Adapter/GLContext.hpp
)
set (SOURCE_FILES
	Source/SDL2.cpp
	Source/ConsoleApp.cpp
	Source/WindowedApp.cpp
	Source/PowerManagement.cpp
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
	s_Application
	MathX
	s_Time
	s_Threading
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

#[[
install (DIRECTORY Include/SDL2
	DESTINATION Include/SDL2
	PATTERN *
)

install (TARGETS s_SDL2
	EXPORT SDL2Config
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT SDL2Config DESTINATION CMake)
]]#

# ###############################################
MakeUnitTest (LIBRARY s_SDL2 GROUP Adapter
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Configuration
)
