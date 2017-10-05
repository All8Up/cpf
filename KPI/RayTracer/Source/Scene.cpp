#include <RayTracer/Scene.hpp>
#include <RayTracer/TraceContext.hpp>
#include <RayTracer/Material.hpp>
#include <RayTracer/Light.hpp>
#include <Math/Constants.hpp>


//////////////////////////////////////////////////////////////////////////
using namespace RayTracer;


//////////////////////////////////////////////////////////////////////////
static Vector4		diffuseColor( 0.2f, 0.2f, 0.4f, 0.0f );


//////////////////////////////////////////////////////////////////////////
Scene::Scene()
:	mScreenX( Vector3(0.0f) )
,	mScreenY( Vector3(0.0f) )
,	mUpperLeft( Vector3(0.0f) )
{
}


void Scene::Render( TraceContext& ctx )
{
	uint32_t		width		=	ctx.Scene().Output().Width();
	uint32_t		height		=	ctx.Scene().Output().Height();
	uint32_t		recursions	=	ctx.Scene().Camera().Recursion() + 1;

	Initialize( ctx );

	// Always sample the center point +supersample samples on either side of
	// the center.
	uint32_t		supersample		=	ctx.Scene().Output().SuperSampling();
	uint32_t		samples			=	1 + (supersample * 2);
	float			sampleWeight	=	1.0f / float( samples*samples );
	float			sampleStepping	=	1.0f / float( samples );
	float			bounds			=	sampleStepping*supersample;

	// The super sampling is incorrect, but it works for now...

	for( uint32_t x=0; x<width; ++x )
	{
		Ray3 ray( ctx.Scene().Camera().Position(), Vector3(0.0f) );

		for( uint32_t y=0; y<height; ++y )
		{
			if( supersample>0 )
			{
				Vector4	color( Vector4(0.0f) );
				for( float xx = -bounds; xx<=bounds; xx += sampleStepping )
				{
					for( float yy = -bounds; yy<=bounds; yy += sampleStepping )
					{
						Vector3		xOffset	=	(float( x ) + xx )*mScreenX;
						Vector3		yOffset	=	(float( y ) + yy )*mScreenY;

						Vector3		dir	=	Normalize( mUpperLeft + xOffset - yOffset );
						ray.Direction = dir;

						color				+=	Trace( ctx, ray, recursions );
					}
				}
				color	*=	sampleWeight;
				*ctx.Scene().Output().FindPixel( x, y )	=	color;
			}
			else
			{
				Vector3		xOffset	=	float( x )*mScreenX;
				Vector3		yOffset	=	float( y )*mScreenY;

				Vector3		dir	=	Normalize( mUpperLeft + xOffset - yOffset );
				ray.Direction = dir;

				*ctx.Scene().Output().FindPixel( x, y )	=	Trace( ctx, ray, recursions );
			}
		}
	}
}


inline Vector3 Refract(const Vector3& i, const Vector3& n, float eta)
{
	float cosI = Dot(-n, i);
	float sinT2 = eta*eta * (1.0f - cosI * cosI);
	if (sinT2 > 1.0f)
		return Vector3(0.0f);
	return eta*i - (eta + std::sqrt(1.0f - sinT2)) * -n;
}


// NOTE: This is a quick hacked up item to get stuff on the screen, it is not "proper" in any
// manner.
Vector4 Scene::Trace( TraceContext& ctx, const Ray3& ray, uint32_t recursions, bool inside )
{
	if( recursions==0 )
	{
		return ctx.Scene().Environment().Color( ray );
	}

	Vector4	result;

	float	t	=	std::numeric_limits< float >::max();
	{
		Vector3		hitPoint;
		Vector3		normal;
		Material*	material	= ctx.Intersect(ray, hitPoint, normal, t);
		if(material)
		{
			Vector3		incident	=	Normalize( hitPoint - ray.Origin );

			result					=	material->Ambient();
			result					+=	Light( *material, hitPoint, incident, normal );

			if( material->HasReflection() )
			{
				Vector3 reflected	=	Reflect( -ray.Direction, normal );
				Ray3 refRay( hitPoint+reflected*0.001f, reflected );
				Vector4 refColor	=	Trace( ctx, refRay, recursions-1 );
				result				+=	material->Reflection() * refColor;
			}
			if( material->HasTranslucency() )
			{
				Vector3 refRay		=	inside
					?	Refract( ray.Direction, normal, material->IOR() )
					:	Refract( ray.Direction, normal, 1.0f/material->IOR() );

				if( MagnitudeSq( refRay ) > 0.0001f )
				{
					refRay				=	Normalize( refRay );
					Ray3 transRay( hitPoint+refRay*0.0001f, refRay );
					Vector4 transColor	=	Trace( ctx, transRay, recursions-1, inside ? false : true );
					result				+=	material->Translucency() * transColor;
				}
			}
		}
		else
		{
			result					=	ctx.Scene().Environment().Color( ray );
		}
	}

	return result;
}


Vector4 Scene::Light( Material& mat, const Vector3& hitPoint, const Vector3& incidence, const Vector3& normal )
{
	Vector4	result( Vector4(0.0f) );
	
	for( auto l : Lights().Lights() )
	{
		Vector3	incid	=	l->Position() - hitPoint;
		float	dist	=	Magnitude( incid );
		incid = Normalize(incid);
		
		Ray3 lightRay( hitPoint+incid*0.001f, incid );
		if( !Models().Shadowed( lightRay, dist ) )
		{
			result			+=	l->Evaluate( incid, dist ) * mat.Diffuse();
			
			// Diffuse.
			float	diff	=	Dot(normal, incid);
			diff			=	diff > 0.0f ? diff : 0.0f;
			result			*=	diff;
			
			// Specular.
			Vector3	refInc	=	Reflect( incid, normal );
			float	spec	=	Dot(-incidence, refInc);
			spec			=	spec > 0.0f ? spec : 0.0f;
			spec			=	std::pow( spec, mat.SpecularPower() ) * l->Falloff( dist );
			result			+=	mat.Specular() * spec;
		}
	}
	
	return result;
}

bool Scene::Parse( JSONValue* v )
{
	if( v )
	{
		JSONValue*	output	=	v->Child( L"Output" );
		if( !mOutput.Parse( output ) )
			return false;

		JSONValue*	camera	=	v->Child( L"Camera" );
		if( !mCamera.Parse( *this, camera ) )
			return false;

		JSONValue*	enviro	=	v->Child( L"Environment" );
		if( !mEnvironment.Parse( *this, enviro ) )
			return false;

		JSONValue*	mats	=	v->Child( L"Materials" );
		if( !mMaterials.Parse( *this, mats ) )
			return false;

		JSONValue*	models	=	v->Child( L"Models" );
		if( !mModels.Parse( *this, models ) )
			return false;

		JSONValue*	lights	=	v->Child( L"Lights" );
		if( !mLights.Parse( *this, lights ) )
			return false;

		return true;
	}
	return false;
}


void Scene::Initialize( TraceContext& ctx )
{
	float width			=	float( ctx.Scene().Output().Width() );
	float height		=	float( ctx.Scene().Output().Height() );

	Vector3 viewVector	=	ctx.Scene().Camera().Position() - ctx.Scene().Camera().Target();
	float viewDist		=	Magnitude( viewVector ) * 2.0f;
	viewVector = Normalize(viewVector);

	mScreenX			=	Normalize( Cross( ctx.Scene().Camera().Up(), viewVector ) );
	mScreenY			=	Cross( viewVector, mScreenX );

	float aspect		=	width / height;
	float halfFov		= CPF::Math::kDegToRad * (ctx.Scene().Camera().FOV() / 2.0f);

	float	mag			=	viewDist * std::tan( halfFov ) / width;
	mScreenX			*=	mag;

	mag					=	viewDist * std::tan( halfFov ) / height / aspect;
	mScreenY			*=	mag;

	float halfWidth		=	ctx.Scene().Output().Width() * 0.5f;
	float halfHeight	=	ctx.Scene().Output().Height() * 0.5f;

	mUpperLeft			=	ctx.Scene().Camera().Target() - ctx.Scene().Camera().Position();
	mUpperLeft			=	mUpperLeft + halfHeight * mScreenY - halfWidth * mScreenX;
}
