//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"

/**
@cond CPF_INTERNAL
*/
#include "Test_All.hpp"
/**
@endcond
*/

using namespace CPF;

int CPF_CDECL main( int argc, char** argv )
{
# if defined(_WIN32)
	::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#   if defined(_MSC_VER)
	::_set_error_mode(_OUT_TO_STDERR);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#   endif
# endif

	auto found_gtest = false;
	for (auto i = 0; i < argc; ++i)
	{
		if (std::string(argv[i]).find("gtest_output") != std::string::npos)
		{
			found_gtest = true;
			break;
		}
	}

	if (found_gtest)
		::testing::InitGoogleTest(&argc, argv);
	else
	{
		auto _argc = argc + 1;
		auto ** _argv = new char*[_argc];
		// Copy original parameters.
		for (auto i = 0; i < argc; ++i)
			_argv[i] = ::strdup(argv[i]);
		// Add xml output param.
		char buffer[1024];
		strcpy(buffer, "--gtest_output=xml:");
		strcat(buffer, argv[0]);
		strcat(buffer, ".xml");
		_argv[argc] = buffer;
		::testing::InitGoogleTest(&_argc, _argv);
	}

	auto result = RUN_ALL_TESTS();
//	CPF_DEBUG_BREAK;
	return result;
}
