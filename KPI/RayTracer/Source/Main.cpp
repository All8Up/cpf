#include <iostream>
#include "RayTracer/Application.hpp"
#include <gflags/gflags.h>
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/iApplication.hpp"
#include "CPF/Application.hpp"

DEFINE_string(input, "", "Input scene.");

using namespace CPF;

class RayTracerApp : public GOM::tUnknown<iApplication>
{
public:
	int32_t Run() override
	{
		if (FLAGS_input.empty())
		{
			printf("Error: no input file given.\n");
			return -1;
		}

		RayTracer::Application app(FLAGS_input);
		return app.Run();
	}
};
CPF_APPLICATION(RayTracerApp);
