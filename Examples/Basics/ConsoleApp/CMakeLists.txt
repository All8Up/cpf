add_executable (ConsoleApp
	Source/Main.cpp
)
target_link_libraries (ConsoleApp
	Core_s Application_s
)
set_property (TARGET ConsoleApp PROPERTY FOLDER CPF/Examples/Basics)
