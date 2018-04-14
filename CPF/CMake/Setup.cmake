#
include (CMakeParseArguments)
include (CMakeDependentOption)

#
include (${CMAKE_CURRENT_LIST_DIR}/Detection.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Version.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Naming.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/InstallLocations.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/InstallInformation.cmake)

include (${CMAKE_CURRENT_LIST_DIR}/Utilities/AddLibrary.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/TypedLibrary.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/CheckValue.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/PreferredInclude.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/GenGOM.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/cpf_idl_generator.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/cpf_binary_plugin.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/UnitTesting/UnitTesting.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Utilities/PropertyUtils.cmake)

include (${CMAKE_CURRENT_LIST_DIR}/Doxygen/BuildDocs.cmake)

# ###############################################
find_package (Threads)

# ###############################################
# Detect utilities and software.
include (${CMAKE_CURRENT_LIST_DIR}/Modules/FindVTune.cmake)


# ###############################################
# Setup options.
include (${CMAKE_CURRENT_LIST_DIR}/Options/VTune.cmake)

# ###############################################
set (CPF_TEMPLATES ${CMAKE_CURRENT_LIST_DIR}/Templates)

# ###############################################
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing ()
set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../CpfSdk" CACHE PATH "Sdk installation location." FORCE)


include (${CMAKE_CURRENT_LIST_DIR}/Settings/Settings.cmake)

# ###############################################
# Check for needed headers and libraries.
include (${CMAKE_CURRENT_LIST_DIR}/Checks/All.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Checks/${CMAKE_SYSTEM_NAME}.cmake)


# ###############################################
option (CPF_ENABLE_UNITTESTS "Enable unit testing projects." ON)
option (CPF_ENABLE_BENCHMARKS "Enable benchmark projects." OFF)
option (CPF_FINAL_BUILD "Build as a final release build." OFF)
