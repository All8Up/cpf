add_executable (Example_EventDriven
	${TEST_INCLUDES}
	Source/Main.cpp
)
target_link_libraries (Example_EventDriven
	Core_s Application_s
)
set_property (TARGET Example_EventDriven PROPERTY FOLDER Examples/Core)

if (CPF_BUILD_STATIC_VARIANTS)
	add_executable (Example_EventDriven_s
		${TEST_INCLUDES}
		Source/Main.cpp
	)
	target_link_libraries (Example_EventDriven_s
		Core_s Application_s PlatformConcurrency_s
	)
	set_property (TARGET Example_EventDriven PROPERTY FOLDER Examples/Core)
endif ()
