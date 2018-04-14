set (Includes
	Include/Main.hpp
)
set (Sources
	Source/Main.cpp
)
add_executable (IDL
	${Includes}
	${Sources}
)
set_property (TARGET IDL PROPERTY FOLDER BuildTools)

source_group (Includes FILES ${Includes})
source_group (Sources FILES ${Sources})

target_include_directories (IDL
	PUBLIC
		Include
)
target_link_libraries (IDL
	Core_s
	Application_s
	IDLParser_s
	gflags_static
)
