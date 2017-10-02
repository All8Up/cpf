#pragma once


#include "RayTracer/RayTracer.hpp"
#include <vector>


// Forward reference.
class JSONValue;


namespace RayTracer
{
	class Scene;
	class Material;
	class ModelSet;

	//////////////////////////////////////////////////////////////////////////
	class CPF_ALIGN(16) Light
	{
	public:
		Light();
		virtual ~Light()															{}
		
		Vector4							Evaluate( const Vector3& incidence, float dist );
		virtual bool					Parse( Scene& s, JSONValue* v );

		const Vector3					Position() const					{return mPosition;}
		float							Falloff( float dist ) const			{dist/=mPower; return dist>0.001f ? 1.0f/dist : 0.0f;}

	private:
		Vector3							mPosition;
		Vector4							mColor;
		float							mPower;
	};


	//////////////////////////////////////////////////////////////////////////
	class LightSet
	{
	public:
		typedef std::vector< Light* >	LightVector_t;

		LightSet();
		~LightSet();

		LightVector_t&					Lights();
		bool							Parse( Scene& s, JSONValue* v );

	private:
		LightVector_t					mLights;
	};
}
