# Networking uses ASIO, so if only include this if found in external.
if (CPF_HAVE_ASIO)
	if (HAVE_D3D12)
		add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Networked")
	endif ()
endif ()
