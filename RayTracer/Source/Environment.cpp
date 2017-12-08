#include "RayTracer/Environment.hpp"
#include "RayTracer/ParseTypes.hpp"
#include "RayTracer/JSON.h"


using namespace RayTracer;


Environment::Environment()
:	mType( EnvironmentType::Solid )
,	mColor( Vector4(0.0f) )
{
}


bool Environment::Parse( Scene& /*s*/, JSONValue* v )
{
	JSONValue*	type	=	v->Child( L"Type" );
	if( !type || !type->IsString() )
		return false;

	if( type->AsString() == std::wstring( L"Solid" ) )
		mType	=	EnvironmentType::Solid;
//	else if( type->AsString() == std::wstring( L"Unimplemented" ) )
	else
		return false;

	if( !::Parse( v, "Color", mColor ) )
		return false;

	return true;
}

Vector4 Environment::Color( const Ray3& /* r */ )
{
	return mColor;
}
