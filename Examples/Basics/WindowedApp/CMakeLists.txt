add_executable (WindowedApp WIN32
	Source/Main.cpp
)
target_link_libraries (WindowedApp
	Core_s Application_s
)
set_property (TARGET WindowedApp PROPERTY FOLDER CPF/Examples/Basics)
