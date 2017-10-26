# ###############################################
set (IDL_INTERFACES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iDirectory.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iExecutor.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iFile.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iFileStream.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iStream.idl
)
CPF_GEN_GOM(CPP_IO_INTERFACES cpp
	hpp
	${CPF_GENERATED}/CPP/CPF/IO
	${IDL_INTERFACES}
)
set (IDL_FLAGS
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/Attributes.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/Access.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/StreamAccess.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/StreamOrigin.idl
)
CPF_GEN_GOM(CPP_IO_FLAGS cpp
	hpp
	${CPF_GENERATED}/CPP/CPF/IO
	${IDL_FLAGS}
)

# ###############################################
set (IO_INCLUDE_FILES
	Include/CPF/IO/Default.hpp
	Include/CPF/IO/File.hpp
)
set (IO_DETAIL_INCLUDE_FILES
	Include/CPF/IO/Detail/DefaultDirectory.hpp
	Include/CPF/IO/Detail/DefaultExecutor.hpp
	Include/CPF/IO/Detail/DefaultFile.hpp
	Include/CPF/IO/Detail/DefaultFileStream.hpp
)

# ###############################################
add_library (IO INTERFACE)
target_include_directories (IO
	INTERFACE
		${CPF_GENERATED}/CPP
		${CMAKE_CURRENT_SOURCE_DIR}/Include
)
target_link_libraries (IO
	INTERFACE
		GOM
		Future
)
add_custom_target (IO_IDE
	SOURCES
		${IDL_INTERFACES}
		${CPP_IO_INTERFACES}
		${IDL_FLAGS}
		${CPP_IO_FLAGS}
		Include/CPF/IO.hpp
		${IO_INCLUDE_FILES}
		${IO_DETAIL_INCLUDE_FILES}
)
add_dependencies (IO IO_IDE)
set_property (TARGET IO_IDE PROPERTY FOLDER Libraries/Interface/Platform)

source_group (Headers FILES Include/CPF/IO.hpp)
source_group (Headers\\IO FILES ${IO_INCLUDE_FILES})
source_group (Headers\\IO\\Detail FILES ${IO_DETAIL_INCLUDE_FILES})

# ###############################################
MakeUnitTest (LIBRARY IO GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_PluginHost
)


# ###############################################
set( INCLUDE_FILES
	Include/IO/IO.hpp
	Include/IO/File.hpp
	Include/IO/Directory.hpp
	Include/IO/Stream.hpp
	Include/IO/Path.hpp
	Include/IO/Globbing.hpp
	Include/IO/BinaryReader.hpp
	Include/IO/BinaryWriter.hpp
	Include/IO/TextReader.hpp
	Include/IO/TextWriter.hpp
	Include/IO/FileSystem.hpp
	Include/IO/Result.hpp
)
set( SOURCE_FILES
	Source/IO.cpp
	Source/Stream.cpp
	Source/File.cpp
	Source/Path.cpp
	Source/BinaryReader.cpp
	Source/BinaryWriter.cpp
	Source/Globbing.cpp
	Source/Directory.cpp
	Source/${CPF_TARGET_OS}/OsFile.cpp
	Source/${CPF_TARGET_OS}/OsDirectory.cpp
	Source/FileSystem.cpp
	Source/TextReader.cpp
	Source/TextWriter.cpp
)

add_library( s_IO STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${IDL_FLAGS}
	${CPP_IO_FLAGS}
	${IDL_INTERFACES}
	${CPP_IO_INTERFACES}
)
target_compile_definitions( s_IO
	PUBLIC CPF_STATIC_IO
	PRIVATE CPF_BUILD_IO
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (IO FILES ${CPP_IO_INTERFACES} ${CPP_IO_FLAGS})
source_group (Sources FILES ${SOURCE_FILES})
source_group (IDL\\Interfaces FILES ${IDL_INTERFACES})
source_group (IDL\\Flags FILES ${IDL_FLAGS})

target_link_libraries (s_IO Configuration Std s_Collections RefCount GOM)

target_include_directories (s_IO
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)

set_property( TARGET s_IO PROPERTY FOLDER Libraries/Static/Platform )

install( DIRECTORY Include/IO
	DESTINATION Include/IO
	PATTERN *
)

install( TARGETS s_IO
	EXPORT IOConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT IOConfig DESTINATION CMake )


# ###############################################
#[[
MakeUnitTests( LIBRARY IO:static GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_BinaryReader.hpp
		UnitTest/Test_BinaryWriter.hpp
		UnitTest/Test_Directory.hpp
		UnitTest/Test_File.hpp
		UnitTest/Test_Globbing.hpp
		UnitTest/Test_Path.hpp
		UnitTest/Test_TextReader.hpp
		UnitTest/Test_TextWriter.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		ANSI_C_FileSystem:static
)
#]]
