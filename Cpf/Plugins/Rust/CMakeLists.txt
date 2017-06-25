find_program (rustc "rustc")
find_program (cargo "cargo")

if (rustc AND cargo)
	message ("Found rust")
	include (ExternalProject)
	set_directory_properties (PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/Rust)

	add_subdirectory (TestRust)
endif ()
