# Utilities for dealing with potentially typed libraries.

function( GetLibraryType name type libName )
	string(REGEX MATCH "(.*):(static|shared|interface|both)" typeInfo ${libName} )
	if (typeInfo)
		set(${name} ${CMAKE_MATCH_1} PARENT_SCOPE)
		set(${type} ${CMAKE_MATCH_2} PARENT_SCOPE)
	else()
		set(${name} ${libName} PARENT_SCOPE)
		set(${type} "both" PARENT_SCOPE)
	endif()
endfunction()


function( GetTypedLibrary result targetType libraryName )
	GetLibraryType(name type ${libraryName})
	if (type STREQUAL interface)
		set(${result} ${name} PARENT_SCOPE)
	elseif (type STREQUAL static)
		set(${result} s_${name} PARENT_SCOPE)
		message ("${libraryName} : ${targetType}")
	elseif(type STREQUAL shared)
		set(${result} ${name} PARENT_SCOPE)
	elseif(type STREQUAL both)
		if(targetType STREQUAL static)
			set(${result} s_${name} PARENT_SCOPE)
		else()
			set(${result} ${name} PARENT_SCOPE)
		endif()
	endif()
endfunction( GetTypedLibrary )


function( GetTypedLibraries result targetType )
	set(${result} "" PARENT_SCOPE)
	set(results "")
	foreach(arg ${ARGN})
		GetTypedLibrary(res ${targetType} ${arg})
		list(APPEND results ${res})
	endforeach()
	set(${result} ${results} PARENT_SCOPE)
endfunction( GetTypedLibraries )
