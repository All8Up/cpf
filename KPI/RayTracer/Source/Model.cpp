#include "RayTracer/Model.hpp"
#include "RayTracer/JSON.h"
#include "RayTracer/ParseTypes.hpp"
#include "RayTracer/Shapes/Sphere.hpp"
#include "RayTracer/Shapes/Plane.hpp"
#include "RayTracer/Scene.hpp"


using namespace RayTracer;

//////////////////////////////////////////////////////////////////////////

Model::Model()
:	mpMaterial( nullptr )
{
}


Model::~Model()
{
}


bool Model::Parse( Scene& s, JSONValue* v )
{
	std::string	matName;
	if( !::Parse( v, "Material", matName ) )
		return false;
	mpMaterial	=	s.Materials().Find( matName );
	if( mpMaterial==nullptr )
		return false;

	return true;
}


Vector3 CPF_VECTORCALL Model::Normal(Vector3Param /* hp */) const
{
	return Vector3(0.0f);
}


Model* Model::ParseModel( Scene& s, JSONValue* v )
{
	if( v && v->IsObject() )
	{
		// Have to figure out what to allocate first thing.
		JSONValue*		type		=	v->Child( L"Type" );
		if( type && type->IsString() )
		{
			std::string		typeName	=	string_cast< std::string >( type->AsString() );

			// Factory time....
			if( typeName=="Sphere" )
			{
				Model*	mod	=	new Sphere();
				if( mod )
					mod->Parse( s, v );
				return mod;
			}
			else if( typeName=="Plane" )
			{
				Model*	mod	=	new Plane();
				if( mod )
					mod->Parse( s, v );
				return mod;
			}
			else
				return nullptr;
		}
	}

	return nullptr;
}



//////////////////////////////////////////////////////////////////////////

ModelSet::ModelSet()
	: mTests(0)
{
}


ModelSet::~ModelSet()
{
}


bool ModelSet::Parse( Scene& s, JSONValue* v )
{
	if( v && v->IsArray() )
	{
		const JSONArray&	models		=	v->AsArray();

		for( JSONValue* model : models )
		{
			Model*	mod	=	Model::ParseModel( s, model );
			if( !mod )
				return false;

			mModels.push_back( mod );
		}
	}
	return true;
}


Material* CPF_VECTORCALL ModelSet::Intersect(const Ray3& r, Vector3& hp, Vector3& n, float& t) const
{
	Model* hitModel = nullptr;
	for (auto it : mModels)
	{
		++mTests;
		float d = std::numeric_limits< float >::max();
		if (it->Intersect(r, d))
		{
			if (d < t)
			{
				t = d;
				hitModel = it;
			}
		}
	}
	if (hitModel)
	{
		hp = r.Origin + r.Direction * t;
		n = hitModel->Normal(Vector3AsParam(hp));
	}

	return (hitModel != nullptr) ? hitModel->Material() : nullptr;
}


bool CPF_VECTORCALL ModelSet::Shadowed( const Ray3& r, float dist ) const
{
	for( auto it : mModels )
	{
		float d	= std::numeric_limits< float >::max();
		++mTests;
		if( it->Intersect(r, d) )
		{
			if( d>0 && d<dist )
				return true;
		}
	}
	return false;
}
