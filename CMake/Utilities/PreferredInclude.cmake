macro (preferred_include preferred defaulted)
	if (EXISTS "${preferred}")
		include (${preferred})
	else ()
		include (${defaulted})
		message (WARNING "Using default include: ${defaulted}")
	endif ()
endmacro (preferred_include)