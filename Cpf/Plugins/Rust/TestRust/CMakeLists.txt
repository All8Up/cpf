
ExternalProject_Add (TestRust
	DOWNLOAD_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND cargo build COMMAND cargo build --release
	BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
	INSTALL_COMMAND ""
	LOG_BUILD ON
)
add_custom_command (
	TARGET TestRust POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/target/$<LOWER_CASE:$<CONFIG>>/test_rust.dll" "${CPF_COMMON_PLUGINS}/TestRust.cfp"
)
