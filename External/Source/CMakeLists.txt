if (NOT EXTERN_INLINE_GMOCK)
	# Detect that the binaries exist.
else ()
	if (IS_DIRECTORY "${GMOCK_SRC_DIR}")
		message ("Inlining gmock project.")
		add_library (gmock STATIC ${GMOCK_SRC_DIR}/fused-src/gmock-gtest-all.cc)
		target_include_directories (gmock PUBLIC ${GMOCK_SRC_DIR}/fused-src)
	endif ()
endif ()
