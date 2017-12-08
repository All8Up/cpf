#pragma once


#include "RayTracer/RayTracer.hpp"
#include <string>
#include <vector>

// Temp till moved to cpp file.
#include "RayTracer/JSON.h"
class JSONValue;


namespace RayTracer
{
	class Scene;

	//////////////////////////////////////////////////////////////////////////
	class CPF_ALIGN(16) Material
	{
	public:
		Material();

		bool					Parse( Scene& s, JSONValue* v );
		const std::string&		Name() const						{return mName;}
		const Vector4			Evaluate( float u, float v );

		Vector4					Ambient() const						{return mAmbient;}
		Vector4					Diffuse() const						{return mDiffuse;}
		Vector4					Specular() const					{return mSpecular;}
		Vector4					Reflection() const					{return mReflection;}
		Vector4					Translucency() const				{return mTranslucency;}

		float					SpecularPower() const				{return mSpecularPower;}
		float					IOR() const							{return mIOR;}

		bool					HasReflection() const				{return mHasReflection;}
		bool					HasTranslucency() const				{return mHasTranslucency;}

	private:
		Vector4					mAmbient;
		Vector4					mDiffuse;
		Vector4					mSpecular;
		Vector4					mReflection;
		Vector4					mTranslucency;
		float					mSpecularPower;
		float					mIOR;
		bool					mHasReflection;
		bool					mHasTranslucency;

		std::string				mName;
	};


	//////////////////////////////////////////////////////////////////////////
	class MaterialSet
	{
	public:
		MaterialSet();
		~MaterialSet();

		bool					Parse( Scene& s, JSONValue* v );
		Material*				Find( std::string& name ) const;

	private:
		//
		bool					Allocate( size_t size );

		//
		size_t					mCount;
		Material*				mpMaterials;
	};
}
