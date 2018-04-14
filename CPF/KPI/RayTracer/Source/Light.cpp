#include "RayTracer/Light.hpp"
#include "RayTracer/JSON.h"
#include "RayTracer/ParseTypes.hpp"
#include "RayTracer/Material.hpp"
#include "RayTracer/Model.hpp"

using namespace RayTracer;

//////////////////////////////////////////////////////////////////////////

Light::Light()
:	mPosition( Vector3(0.0f) )
,	mColor( Vector4( 1.0f, 1.0f, 1.0f, 0.0f ) )
,	mPower( 1.0f )
{}

Vector4 Light::Evaluate( const Vector3& /*incidence*/, float dist )
{
	return mColor * Falloff( dist );
}


bool Light::Parse( Scene& /*s*/, JSONValue* v )
{
	if( !::Parse( v, "Position", mPosition ) )
		return false;

	if( !::Parse( v, "Color", mColor ) )
		return false;
	
	::Parse( v, "Power", mPower );

	return true;
}


//////////////////////////////////////////////////////////////////////////
LightSet::LightSet()
{
}


LightSet::~LightSet()
{
	for( auto it : mLights )
		delete it;
}


LightSet::LightVector_t& LightSet::Lights()
{
	return mLights;
}


bool LightSet::Parse( Scene& s, JSONValue* v )
{
	if( v && v->IsArray() )
	{
		const JSONArray&	lights		=	v->AsArray();

		for( JSONValue* light : lights )
		{
			Light*	l	=	new Light();
			if( !l->Parse( s, light ) )
				return false;

			mLights.push_back( l );
		}
	}
	return true;
}
