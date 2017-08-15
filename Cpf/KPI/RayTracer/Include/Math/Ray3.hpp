#pragma once

#include "RayTracer/RayTracer.hpp"


// NOTE: This is a temporary helper, it will be moved
// into the proper math libraries once everything is
// further along.
namespace Math
{
	class CPF_ALIGN(16) Ray3
	{
	public:
		Ray3( const RayTracer::Vector3& o, const RayTracer::Vector3& d )
		:	mOrigin( o )
		,	mDirection( d )
		{
		}

		const RayTracer::Vector3&	Origin() const						{return mOrigin;}
		void						Origin( RayTracer::Vector3& r )		{mOrigin = r;}
		const RayTracer::Vector3&	Direction() const					{return mDirection;}
		void						Direction( RayTracer::Vector3& d )	{mDirection = d;}

	private:
		RayTracer::Vector3			mOrigin;
		RayTracer::Vector3			mDirection;
	};
}
