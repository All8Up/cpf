//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <string>
#include "RayTracer/Camera.hpp"
#include "RayTracer/Environment.hpp"
#include "RayTracer/Material.hpp"
#include "RayTracer/Model.hpp"
#include "RayTracer/Light.hpp"
#include "RayTracer/Output.hpp"


// Forward references.
class JSONValue;


namespace RayTracer
{
	class Material;
	class TraceContext;

	class Scene
	{
	public:
		Scene();

		void							Render( TraceContext& ctx );
		bool							Parse( JSONValue* v );

		RayTracer::Output&				Output()								{return mOutput;}
		RayTracer::Camera&				Camera()								{return mCamera;}
		RayTracer::Environment&			Environment()							{return mEnvironment;}
		RayTracer::MaterialSet&			Materials()								{return mMaterials;}
		RayTracer::ModelSet&			Models()								{return mModels;}
		RayTracer::LightSet&			Lights()								{return mLights;}

		void Reset() { mModels.Reset(); }
		int64_t GetTests() const { return mModels.GetTests(); }

	private:
		//////////////////////////////////////////////////////////////////////////
		void							Initialize( TraceContext& ctx );
		Vector4							Trace( TraceContext& ctx, const Ray3& ray, uint32_t recursions, bool inside=false );
		Vector4							Light( Material& mat, const Vector3& hitPoint, const Vector3& incidence, const Vector3& normal );

		//////////////////////////////////////////////////////////////////////////
		Vector3							mScreenX;
		Vector3							mScreenY;

		Vector3							mUpperLeft;

		//////////////////////////////////////////////////////////////////////////
		RayTracer::Output				mOutput;
		RayTracer::Camera				mCamera;
		RayTracer::Environment			mEnvironment;
		RayTracer::MaterialSet			mMaterials;
		RayTracer::ModelSet				mModels;
		RayTracer::LightSet				mLights;
	};
}
