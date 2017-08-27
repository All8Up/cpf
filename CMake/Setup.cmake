#
include (CMakeParseArguments)
include (CMakeDependentOption)

#
include (CMake/Detection.cmake)
include (CMake/Version.cmake)
include (CMake/Naming.cmake)
include (CMake/InstallLocations.cmake)
include (CMake/InstallInformation.cmake)

include (CMake/Utilities/AddLibrary.cmake)
include (CMake/Utilities/TypedLibrary.cmake)
include (CMake/Utilities/CheckValue.cmake)
include (CMake/Utilities/PreferredInclude.cmake)
include (CMake/UnitTesting/UnitTesting.cmake)

include (CMake/Doxygen/BuildDocs.cmake)

# ###############################################
find_package (Threads)

# ###############################################
# Setup for Qt
set (CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/5.8/msvc2015_64;D:/Qt/5.8/msvc2015_64")
set (CMAKE_AUTOMOC ON)

# ###############################################
# Detect utilities and software.
include (CMake/Modules/FindVTune.cmake)


# ###############################################
# Setup options.
include (CMake/Options/VTune.cmake)


# ###############################################
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
enable_testing ()
set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../CpfSdk" CACHE PATH "Sdk installation location." FORCE)


include (CMake/Settings/Settings.cmake)

# ###############################################
# Setup extra tools.
include (CMake/Tools/FindFlexBison.cmake)

# ###############################################
# Check for needed headers and libraries.
include (CMake/Checks/All.cmake)
include (CMake/Checks/${CMAKE_SYSTEM_NAME}.cmake)
