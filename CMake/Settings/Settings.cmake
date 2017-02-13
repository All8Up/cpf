#
include (CMake/Settings/General.cmake)
include (CMake/Settings/Dialect.cmake)
include (CMake/Settings/Optimize.cmake)
include (CMake/Settings/CompilerSimdFlags.cmake)

foreach(type ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${type} upper_type)
	message ("CMAKE_C_FLAGS_${upper_type}: ${CMAKE_C_FLAGS_${upper_type}}")
endforeach ()

foreach(type ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${type} upper_type)
	message ("CMAKE_CXX_FLAGS_${upper_type}: ${CMAKE_CXX_FLAGS_${upper_type}}")
endforeach ()
