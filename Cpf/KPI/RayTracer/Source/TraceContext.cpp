#include "RayTracer/TraceContext.hpp"


using namespace RayTracer;

bool TraceContext::Parse( JSONValue* v )
{
	if( v && v->IsObject() )
	{
		if( !ValidateVersion( v->Child( L"Version" ) ) )
		{
			return false;
		}

		if( !mScene.Parse( v->Child( L"Scene" ) ) )
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}


Material* TraceContext::Intersect( const Math::Ray3& r, Vector3& hp, Vector3& n, float& t )
{
	return mScene.Models().Intersect( r, hp, n, t );
}


bool TraceContext::ValidateVersion( JSONValue* v )
{
	if( v )
	{
		JSONValue*	major	=	v->Child( L"Major" );
		JSONValue*	minor	=	v->Child( L"Minor" );

		if( major && major->IsNumber() && minor && minor->IsNumber() )
		{
			int	majorVersion	=	(int)major->AsNumber();
			int	minorVersion	=	(int)minor->AsNumber();

			if( majorVersion==1 && minorVersion==0 )
			{
				return true;
			}
		}
	}
	return false;
}
