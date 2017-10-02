#pragma once

#include "RayTracer/RayTracer.hpp"
#include <string>
#include <fstream>


class JSONValue;

namespace RayTracer
{
	class Output
	{
	public:
		//
		Output();

		//
		bool				Parse( JSONValue* v );
		void				Filename( const std::string name )				{mFilename = name;}
		std::string			Filename() const								{return mFilename;}
		void				Width( uint32_t w )								{mWidth = w;}
		uint32_t			Width() const									{return mWidth;}
		void				Height( uint32_t h )							{mHeight = h;}
		uint32_t			Height() const									{return mHeight;}
		void				SuperSampling( uint32_t ss )					{mSuperSampling = ss;}
		uint32_t			SuperSampling() const							{return mSuperSampling;}

		bool				Begin();
		bool				End();

		// TODO: Convert to a proper type.
		Vector4*			FindPixel( uint32_t x, uint32_t y );
		Vector4*			Buffer();

	private:
		std::string			mFilename;
		uint32_t			mWidth;
		uint32_t			mHeight;
		uint32_t			mSuperSampling;

		Vector4*			mpBuffer;
	};
}
