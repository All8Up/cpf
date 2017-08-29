# ##########################################
SET( INCLUDE_DIRS
	${CMAKE_CURRENT_LIST_DIR}/Include
)
INCLUDE_DIRECTORIES( ${INCLUDE_DIRS} ${MATH_INCLUDE_DIRS} ${MATH_SIMD_INCLUDE_DIRS} )


# ##########################################
SET( INCLUDE_FILES
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
)


# ##########################################
SET( SOURCE_FILES
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
)

# ##########################################
# Let's make things pretty in IDE's.


# ##########################################

ADD_EXECUTABLE( RayTracer
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
TARGET_LINK_LIBRARIES( RayTracer
	Math
	${CMAKE_THREAD_LIBS_INIT}
)

# ##########################################
# Group the applications.
SET_PROPERTY( TARGET RayTracer PROPERTY FOLDER Experimental )
