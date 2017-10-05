//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "RayTracer/Scene.hpp"
#include "RayTracer/Output.hpp"


// Forward references.
class JSONValue;


namespace RayTracer
{
	class TraceContext
	{
	public:
		bool							Parse( JSONValue* v );

		Material*						Intersect( const Ray3& r, Vector3& hp, Vector3& n, float& t );

		RayTracer::Scene&				Scene()						{return mScene;}

		void Reset() { mScene.Reset(); }
		int64_t GetTests() const { return mScene.GetTests(); }

	private:
		bool							ValidateVersion( JSONValue* );

		RayTracer::Scene				mScene;
	};
}
