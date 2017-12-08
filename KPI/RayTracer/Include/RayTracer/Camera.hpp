#pragma once


#include "RayTracer/RayTracer.hpp"
#include <string>


// Forward references.
class JSONValue;


namespace RayTracer
{
	class Scene;

	class CPF_ALIGN(16) Camera
	{
	public:
		enum class ProjectionType : uint32_t
		{
			Orthographic,
			Perspective
		};

		Camera();

		bool					Parse( Scene& s, JSONValue* v );

		void					Type( const ProjectionType p )				{mType = p;}
		ProjectionType			Type() const								{return mType;}
		void					FOV( float fov )							{mFOV = fov;}
		float					FOV() const									{return mFOV;}

		Vector3					Position() const							{return mPosition;}
		Vector3					Target() const								{return mTarget;}
		Vector3					Up() const									{return mUp;}
		float					AspectRatio() const							{return mAspectRatio;}
		void					Recursion( uint32_t r )						{mRecursion = r;}
		uint32_t				Recursion() const							{return mRecursion;}

	private:
		Vector3					mPosition;
		Vector3					mTarget;
		Vector3					mUp;
		ProjectionType			mType;
		float					mFOV;
		float					mAspectRatio;
		uint32_t				mRecursion;
	};
}
