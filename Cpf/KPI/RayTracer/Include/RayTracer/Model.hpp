//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RayTracer/RayTracer.hpp"
#include "Math/Ray3.hpp"
#include <vector>

// Forward references.
class JSONValue;

// Test difference between pass in register and normal stack.
#define TEST_PASS_IN_REGISTER 1
#if TEST_PASS_IN_REGISTER
#	define Vector3Param const typename Vector3::StorageType
#	define Vector3AsParam typename Vector3::StorageType
#else
#	define Vector3Param const Vector3&
#	define Vector3AsParam Vector3
#endif

namespace RayTracer
{
	// Forward references.
	class Scene;
	class Material;

	//////////////////////////////////////////////////////////////////////////
	class CPF_ALIGN(16) Model
	{
	public:
		Model();
		virtual ~Model();

		virtual bool Parse(Scene& s, JSONValue* v);
		virtual bool CPF_VECTORCALL Intersect(Vector3Param origin, Vector3Param dir, float& t) const = 0;
		virtual Vector3 CPF_VECTORCALL Normal(Vector3Param hp) const;
		Material* Material() const { return mpMaterial; }

		static Model* ParseModel(Scene& s, JSONValue* v);

	protected:
		RayTracer::Material* mpMaterial;
	};


	//////////////////////////////////////////////////////////////////////////
	class ModelSet
	{
	public:
		ModelSet();
		~ModelSet();

		bool Parse(Scene& s, JSONValue* v);

		Material* CPF_VECTORCALL Intersect(const Math::Ray3& r, Vector3& hp, Vector3& n, float& t) const;
		bool CPF_VECTORCALL Shadowed(const Math::Ray3& r, float dist) const;

		void Reset() { mTests = 0; }
		int64_t GetTests() const { return mTests; }

	private:
		typedef std::vector<Model*> ModelVector_t;

		mutable int64_t mTests;
		ModelVector_t mModels;
	};
}
