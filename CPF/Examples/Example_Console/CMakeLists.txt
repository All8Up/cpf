add_executable (Example_Console
	${TEST_INCLUDES}
	Source/Main.cpp
)
target_link_libraries (Example_Console
	Core_s Application_s
)
set_property (TARGET Example_Console PROPERTY FOLDER Examples/Core)
