//
#include "RayTracer/Application.hpp"
#include "RayTracer/JSON.h"
#include <fstream>
#include <streambuf>
#include <chrono>


using namespace RayTracer;
typedef std::chrono::high_resolution_clock	Clock_t;


Application::Application( const std::string& scene )
:	mSceneFilename( scene )
,	mLog( "Log.txt" )
{
}


Application::~Application()
{
	mLog.close();
}


int Application::Run()
{
	if( OpenScene() && OpenOutput() )
	{
		// Separation of ray tracing from saving for performance measurements.

		// Initialize the output frame buffer.
		mContext.Scene().Output().Begin();

		// Run the ray tracer.
#define PERFORM_TEST 5

		auto start = Clock_t::now();

#if defined( PERFORM_TEST )
		for (int i = 0; i < PERFORM_TEST; ++i)
#endif
		{
			auto currentStart = Clock_t::now();
			mContext.Scene().Render(mContext);
			auto currentEnd = Clock_t::now();
			std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentEnd - currentStart);
#if defined( PERFORM_TEST )
			Log() << "Run: " << i << "\n";
#endif
			Log() << " Render time milliseconds: " << delta.count() << "\n";
			Log() << " Intersection tests      : " << mContext.GetTests() << "\n";
			mContext.Reset();
		}

		auto end = Clock_t::now();
		std::chrono::milliseconds total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
#if defined( PERFORM_TEST )
		Log() << "Render time milliseconds: " << total.count()/PERFORM_TEST << "\n";
		Log() << "Render time milliseconds: " << total.count() << " x" << PERFORM_TEST << " total.\n";
#endif

		// Shutdown/save the output frame buffer.
		mContext.Scene().Output().End();

		return 0;
	}
	return -1;
}


std::ostream& Application::Log()
{
	return mLog;
}


bool Application::OpenScene()
{
	std::ifstream	inStream( mSceneFilename );

	if( inStream.bad() )
	{
		return false;
	}
	std::string	sceneTxt(	(std::istreambuf_iterator< char >( inStream )),
							std::istreambuf_iterator< char >()				);

	JSONValue*	root	=	JSON::Parse( sceneTxt.c_str() );

	if( mContext.Parse( root ) )
		return true;
	return false;
}


bool Application::OpenOutput()
{
	return true;
}
