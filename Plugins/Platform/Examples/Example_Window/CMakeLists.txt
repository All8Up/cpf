add_executable (Example_WindowedApp WIN32
	Source/Main.cpp
)
target_link_libraries (Example_WindowedApp
	Core_s Application_s
)
set_property (TARGET Example_WindowedApp PROPERTY FOLDER Examples/Platform)
