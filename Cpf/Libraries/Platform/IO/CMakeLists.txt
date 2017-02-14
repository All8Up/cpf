# ###############################################
set( INCLUDE_FILES
	Include/IO/IO.hpp
	Include/IO/File.hpp
	Include/IO/Directory.hpp
	Include/IO/Stream.hpp
	Include/IO/Path.hpp
	Include/IO/Globbing.hpp
	Include/IO/Reader.hpp
	Include/IO/Writer.hpp
	Include/IO/BinaryReader.hpp
	Include/IO/BinaryWriter.hpp
	Include/IO/TextReader.hpp
	Include/IO/TextWriter.hpp
	Include/IO/FileSystem.hpp
	Include/IO/Archive.hpp
	Include/IO/JsonArchive.hpp
	Include/IO/BinaryArchive.hpp
	Include/IO/Serializer.hpp
)
set( SOURCE_FILES
	Source/Archive.cpp
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
)
target_compile_definitions( s_IO
	PUBLIC CPF_STATIC_IO
	PRIVATE CPF_BUILD_IO
)
#[[
add_library( IO SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( IO
	PRIVATE CPF_BUILD_IO
)
#]]
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

#target_link_libraries( IO Configuration Collections RefCount )
target_link_libraries( s_IO Configuration s_Std s_Collections s_RefCount )

#[[
target_include_directories( IO
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
#]]
target_include_directories( s_IO
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_IO PROPERTY FOLDER Libraries/Static/Platform )
#set_property( TARGET IO PROPERTY FOLDER Libraries/Shared/Platform )

install( DIRECTORY Include/IO
	DESTINATION Include/IO
	PATTERN *
)

#[[
install( TARGETS IO
	EXPORT IOConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
#]]
install( TARGETS s_IO
	EXPORT IOConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT IOConfig DESTINATION CMake )


# ###############################################
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
		UnitTest/Test_Archive.hpp
		UnitTest/Test_Serializer.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		PlatformLib
		ANSI_C_FileSystem:static
)
