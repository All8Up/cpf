# ###############################################
CPF_GEN_GOM(CppGOMFiles cpp
	hpp
	${CPF_GENERATED}/CPP/GOM
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/ResultCodes.idl
)
CPF_GEN_GOM(RustGOMFiles rust
	rs
	${CPF_GENERATED}/Rust/GOM
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/ResultCodes.idl
)
message ("RS: ${RustGOMFiles}")


# ###############################################
set (INCLUDE_FILES
	Include/GOM.hpp
	Include/GOM/Types.hpp
	Include/GOM/iUnknown.hpp
	Include/GOM/Result.hpp
	${CppGOMFiles}
)
set (RUST_FILES
	${RustGOMFiles}
)

add_library (GOM INTERFACE)
target_link_libraries (GOM INTERFACE Configuration RefCount)

target_include_directories (GOM INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)

add_custom_target (GOM_IDE SOURCES ${INCLUDE_FILES} ${RUST_FILES})
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Rust FILES ${RUST_FILES})
set_property (TARGET GOM_IDE PROPERTY FOLDER Libraries/Interface/Core)


# ###############################################
install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)

install (TARGETS GOM
	EXPORT GOMConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT GOMConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY GOM GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
