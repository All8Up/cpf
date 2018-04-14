#include "RayTracer/Camera.hpp"
#include "RayTracer/ParseTypes.hpp"
#include "RayTracer/JSON.h"

using namespace RayTracer;


Camera::Camera()
:	mPosition( Vector3(0.0f) )
,	mTarget( Vector3(0, 0, -1) )
,	mUp( Vector3(0, 1, 0) )
,	mType( ProjectionType::Perspective )
,	mFOV( 90.0f )
,	mRecursion( 4 )
{}

bool Camera::Parse( Scene& /* s */, JSONValue* v )
{
	static const char*		ProjectionNames[]	=
	{
		"Orthographic",
		"Perspective"
	};

	// Process projection.
	std::string	projectionName;
	if( !::Parse( v, "Projection", projectionName ) )\
		return false;

	if( projectionName == ProjectionNames[ 0 ] )
		mType	=	ProjectionType::Orthographic;
	else if( projectionName == ProjectionNames[ 1 ] )
		mType	=	ProjectionType::Perspective;
	else
		return false;

	// Process field of view.
	if( !::Parse( v, "FieldOfView", mFOV ) )
		return false;

	if( !::Parse( v, "AspectRatio", mAspectRatio ) )
		return false;

	if( !::Parse( v, "Position", mPosition ) )
		return false;

	if( !::Parse( v, "Target", mTarget ) )
		return false;

	if( !::Parse( v, "Up", mUp ) )
		return false;

	if( !::Parse( v, "Recursion", mRecursion ) )
		return false;

	return true;
}
