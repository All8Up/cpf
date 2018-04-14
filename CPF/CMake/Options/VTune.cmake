if (VTune_INCLUDE_DIRS)
	option(CPF_ENABLE_VTUNE "Enable embedded VTune analysis." OFF)

	if (CPF_ENABLE_VTUNE)
		set (CPF_VTUNE 1)
	endif ()
endif ()
