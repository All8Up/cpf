#include <iostream>
#include "RayTracer/Application.hpp"


int main( int argc, char** argv )
{
	using namespace RayTracer;

	if( argc!=2 )
	{
		std::cout << "Usage: Raytracer <in scene>\n";
		return -1;
	}

	std::string		inScene( argv[ 1 ] );
	Application		app( inScene );

	return app.Run();
}
