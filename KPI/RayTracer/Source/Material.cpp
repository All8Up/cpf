#include "RayTracer/Material.hpp"
#include "RayTracer/ParseTypes.hpp"


using namespace RayTracer;

//////////////////////////////////////////////////////////////////////////
Material::Material()
:	mAmbient( Vector4( 0.1f, 0.1f, 0.1f, 0.0f ) )
,	mDiffuse( Vector4( 0.2f, 0.2f, 0.2f, 0.0f ) )
,	mSpecular( Vector4( 0.5f, 0.5f, 0.5f, 0.0f ) )
,	mReflection( Vector4(0.0f) )
,	mTranslucency( Vector4(0.0f) )
,	mSpecularPower( 1.0f )
,	mIOR( 1.0f )
,	mHasReflection( false )
,	mHasTranslucency( false )
{
}

bool Material::Parse( Scene& /* s */, JSONValue* v )
{
	if( v && v->IsObject() )
	{
		if( !::Parse( v, "Name", mName ) )
			return false;

		// Colors are optional.
		::Parse( v, "Ambient", mAmbient );
		::Parse( v, "Diffuse", mDiffuse );
		::Parse( v, "Specular", mSpecular );
		::Parse( v, "SpecularPower", mSpecularPower );
		::Parse( v, "IOR", mIOR );
		::Parse( v, "Reflection", mReflection );
		::Parse( v, "Translucency", mTranslucency );

		if( mReflection.x>0.0f || mReflection.y>0.0f || mReflection.z>0.0f )
			mHasReflection	=	true;
		if( mTranslucency.x>0.0f || mTranslucency.y>0.0f || mTranslucency.z>0.0f )
			mHasTranslucency	=	true;

		return true;
	}

	return false;
}


const Vector4 Material::Evaluate( float /* u */, float /* v */ )
{
	return mDiffuse;
}


//////////////////////////////////////////////////////////////////////////

MaterialSet::MaterialSet()
:	mCount( 0 )
,	mpMaterials( nullptr )
{
}


MaterialSet::~MaterialSet()
{
	delete[] mpMaterials;
}


bool MaterialSet::Parse( Scene& s, JSONValue* v )
{
	if( v && v->IsArray() )
	{
		const JSONArray&	mats	=	v->AsArray();

		if( !Allocate( mats.size() ) )
			return false;

		for( size_t i=0; i<mats.size(); ++i )
		{
			if( !mpMaterials[ i ].Parse( s, mats[ i ] ) )
				return false;
		}

		return true;
	}

	return false;
}


bool MaterialSet::Allocate( size_t size )
{
	mCount	=	size;
	CPF_ASSERT(mpMaterials == nullptr);
	mpMaterials		=	new Material[ size ];
	return mpMaterials!=nullptr;
}


Material* MaterialSet::Find( std::string& name ) const
{
	for( size_t i=0; i<mCount; ++i )
	{
		if( mpMaterials[ i ].Name()==name )
		{
			return mpMaterials+i;
		}
	}
	return nullptr;
}
