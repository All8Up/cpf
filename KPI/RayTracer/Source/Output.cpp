#include "RayTracer/Output.hpp"
#include "RayTracer/RayTracer.hpp"
#include "RayTracer/JSON.h"
#include "RayTracer/ParseTypes.hpp"
#include <algorithm>
#include <fstream>


using namespace RayTracer;


Output::Output()
:	mWidth( 0 )
,	mHeight( 0 )
,	mpBuffer( nullptr )
{
}

bool Output::Parse( JSONValue* v )
{
	if( v )
	{
		if( !::Parse( v, "Width", mWidth ) )
			return false;
		if( !::Parse( v, "Height", mHeight ) )
			return false;
		if( !::Parse( v, "Name", mFilename ) )
			return false;
		if( !::Parse( v, "SuperSampling", mSuperSampling ) )
			return false;
		return true;
	}

	return false;
}


bool Output::Begin()
{
	mpBuffer	=	new Vector4[ mHeight*mWidth ];

	// Make it all white for now.
	for( size_t i=0; i<mHeight*mWidth; ++i )
	{
		mpBuffer[ i ]	=	Vector4( 1.0f, 1.0f, 1.0f, 0.0f );
	}

	return mpBuffer != nullptr;
}


bool Output::End()
{
	// Save the results.
	if( !mFilename.empty() )
	{
		// Horrible way to do this.....
		std::ofstream	out( mFilename, std::ios_base::binary );
		if( out )
		{
			// Output the tga header.
			out.put( 0 ).put( 0 );
			out.put( 2 );				// Uncompressed image format.

			out.put( 0 ).put( 0 );
			out.put( 0 ).put( 0 );
			out.put( 0 );

			out.put( 0 ).put( 0 );		// Origin X
			out.put( 0 ).put( 0 );		// Origin Y


			out.put( (uint8_t)(mWidth & 0x00FF) ).put( (uint8_t)( (mWidth & 0xFF00) >> 8 ));
			out.put( (uint8_t)(mHeight & 0x00FF) ).put( (uint8_t)( (mHeight & 0xFF00) >> 8 ));
			out.put( 24 );				// RGB 8 bits each.
			out.put( 0 );

			for( uint32_t y=0; y<mHeight; ++y )
			{
				for( uint32_t x=0; x<mWidth; ++x )
				{
					uint32_t	yy		=	(mHeight-y-1);
					Vector4&	pixel	=	mpBuffer[ x + (yy*mWidth) ];
					uint8_t		r		=	uint8_t( std::min( std::max( float(pixel.x), 0.0f ), 1.0f ) * 255.0f );
					uint8_t		g		=	uint8_t( std::min( std::max( float(pixel.y), 0.0f ), 1.0f ) * 255.0f );
					uint8_t		b		=	uint8_t( std::min( std::max( float(pixel.z), 0.0f ), 1.0f ) * 255.0f );

					out.put( b );
					out.put( g );
					out.put( r );
				}
			}
		}
	}

	if( mpBuffer )
	{
		delete[] mpBuffer;
		return true;
	}
	return false;
}

Vector4* Output::Buffer()
{
	return mpBuffer;
}


Vector4* Output::FindPixel( uint32_t x, uint32_t y )
{
	Vector4*	result	=	mpBuffer;
	result	+=	(y*mWidth) + x;
	return result;
}
