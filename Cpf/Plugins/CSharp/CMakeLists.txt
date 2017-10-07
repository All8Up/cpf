option (CPF_ENABLE_CSHARP "Enable C# integration." OFF)

if (CPF_ENABLE_CSHARP)
	if (WIN32)
		add_subdirectory (CSharpBinding)
		add_subdirectory (TestCSharp)
	endif ()
endif ()
