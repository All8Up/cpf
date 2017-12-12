#
include (${CMAKE_CURRENT_LIST_DIR}/General.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Dialect.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Optimize.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/CompilerSimdFlags.cmake)

foreach(type ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${type} upper_type)
	message ("CMAKE_C_FLAGS_${upper_type}: ${CMAKE_C_FLAGS_${upper_type}}")
endforeach ()

foreach(type ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${type} upper_type)
	message ("CMAKE_CXX_FLAGS_${upper_type}: ${CMAKE_CXX_FLAGS_${upper_type}}")
endforeach ()
