# ##########################################
set (INCLUDE_FILES
	Include/RayTracer/RayTracer.hpp
	Include/RayTracer/Application.hpp
	Include/RayTracer/Output.hpp
	Include/RayTracer/Scene.hpp
	Include/RayTracer/Camera.hpp
	Include/RayTracer/Environment.hpp
	Include/RayTracer/Material.hpp
	Include/RayTracer/Model.hpp
	Include/RayTracer/Shapes/Sphere.hpp
	Include/RayTracer/Shapes/Plane.hpp
	Include/RayTracer/Light.hpp
	Include/RayTracer/TraceContext.hpp
	Include/RayTracer/ParseTypes.hpp
	Include/RayTracer/JSON.h
	Include/RayTracer/JSONValue.h

	Include/RayTracer/SceneReader.hpp
)


# ##########################################
set (SOURCE_FILES
	Source/Application.cpp
	Source/TraceContext.cpp
	Source/Output.cpp
	Source/Scene.cpp
	Source/Camera.cpp
	Source/Environment.cpp
	Source/Material.cpp
	Source/Model.cpp
	Source/Shapes/Sphere.cpp
	Source/Shapes/Plane.cpp
	Source/Light.cpp
	Source/ParseTypes.cpp
	Source/JSON.cpp
	Source/JSONValue.cpp
	Source/Main.cpp

	Source/SceneReader.cpp
)

# ##########################################

add_executable (RayTracer
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_link_libraries (RayTracer
	Math
	s_IO
	Patterns
	jsoncons
	s_ANSI_C_FileSystem
	${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories (RayTracer
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/Include
)


# ##########################################
# Group the applications.
set_property (TARGET RayTracer PROPERTY FOLDER Experimental)
