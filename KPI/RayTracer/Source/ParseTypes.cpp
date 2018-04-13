#include "RayTracer/ParseTypes.hpp"
#include "RayTracer/JSON.h"



bool RayTracer::Parse( JSONValue* src, std::string attrName, uint32_t& out )
{
	if( src )
	{
		JSONValue*	fl	=	src->Child( string_cast< std::wstring >( attrName ).c_str() );
		if( fl && fl->IsNumber() )
		{
			out	=	(uint32_t)fl->AsNumber();
			return true;
		}
	}

	return false;
}


bool RayTracer::Parse( JSONValue* src, std::string attrName, float& out )
{
	if( src )
	{
		JSONValue*	fl	=	src->Child( string_cast< std::wstring >( attrName ).c_str() );
		if( fl && fl->IsNumber() )
		{
			out	=	(float)fl->AsNumber();
			return true;
		}
	}

	return false;
}


bool RayTracer::Parse( JSONValue* src, std::string attrName, std::string& out )
{
	if( src )
	{
		JSONValue*	str	=	src->Child( string_cast< std::wstring >( attrName ).c_str() );
		if( str && str->IsString() )
		{
			out		=	string_cast< std::string >( str->AsString() );
			return true;
		}
	}

	return false;
}


bool RayTracer::Parse( JSONValue* src, std::string attrName, Vector3& out )
{
	if( src )
	{
		out	=	Vector3(0.0f);

		JSONValue*	vec	=	src->Child( string_cast< std::wstring >( attrName ).c_str() );
		if( vec && vec->IsArray() )
		{
			const JSONArray&	vecElements	=	vec->AsArray();
			if( vecElements.size()!=3 )
				return false;

			for( int i = 0; i<3; ++i )
			{
				JSONValue*	value	=	vecElements[ i ];
				if( !value || !value->IsNumber() )
					return false;
				out[i] = (float)value->AsNumber();
			}
			return true;
		}
	}

	return false;
}


bool RayTracer::Parse( JSONValue* src, std::string attrName, Vector4& out )
{
	if( src )
	{
		JSONValue*	vec	=	src->Child( string_cast< std::wstring >( attrName ).c_str() );
		if( vec && vec->IsArray() )
		{
			const JSONArray&	vecElements	=	vec->AsArray();
			if( vecElements.size()!=4 )
				return false;

			for( int i = 0; i<4; ++i )
			{
				JSONValue*	value	=	vecElements[ i ];
				if( !value || !value->IsNumber() )
					return false;
				out[i] = (float)value->AsNumber();
			}
			return true;
		}
	}

	return false;
}
