add_executable (Example_MouseEvents WIN32
	Source/Main.cpp
)
target_link_libraries (Example_MouseEvents
	Core_s Application_s
)
set_property (TARGET Example_MouseEvents PROPERTY FOLDER Examples/Platform)
