INCLUDE( InstallRequiredSystemLibraries )

SET( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Cpf Sdk" )
SET( CPACK_PACKAGE_VENDOR "" )
SET( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Readme.txt" )
SET( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt" )
SET( CPACK_PACKAGE_VERSION_MAJOR "0" )
SET( CPACK_PACKAGE_VERSION_MINOR "1" )
SET( CPACK_PACKAGE_VERSION_PATCH "0" )
SET( CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}" )

IF( WIN32 AND NOT UNIX )
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET( CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp" )
  SET( CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe" )
  SET( CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project" )
  SET( CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org" )
  SET( CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com" )
  SET( CPACK_NSIS_CONTACT "me@my-personal-home-page.com" )
  SET( CPACK_NSIS_MODIFY_PATH ON )
ELSE()
  SET( CPACK_STRIP_FILES "bin/MyExecutable" )
  SET( CPACK_SOURCE_STRIP_FILES "" )
ENDIF()

SET( CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable" )

INCLUDE( CPack )
