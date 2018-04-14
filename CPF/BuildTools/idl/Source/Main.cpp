//////////////////////////////////////////////////////////////////////////
#include "CPF/IO.hpp"
#include "CPF/IO/Path.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Application.hpp"
#include <gflags/gflags.h>
#include "CPF/BuildTools/iIDLParser.hpp"
#include "CPF/BuildTools/OutputLanguage.hpp"
#include "CPF/IO/File.hpp"

#ifdef _WIN32
#   include <Windows.h>
#endif

DEFINE_string(input, "", "Input file to process.");
DEFINE_string(output, "", "Output file.");
DEFINE_bool(cpp, false, "Output C++ targets.");
DEFINE_bool(rust, false, "Output rust targets.");
DEFINE_bool(csharp, false, "Output CSharp targets.");

using namespace CPF;

class IDLCommand : public GOM::tUnknown<iApplication>
{
public:
	IDLCommand(Plugin::iRegistry* registry)
		: mpRegistry(registry)
	{}

	int32_t Run() override
	{
		CPF_INSTALL_STATIC_PLUGIN(mpRegistry, IDLParser);

		if (FLAGS_input.empty())
		{
			printf("Error: no input file given.\n");
			return -1;
		}
		if (!IO::File::Exists(FLAGS_input.c_str()))
		{
			printf("Error: input file not found.\n");
			return -1;
		}

		if (FLAGS_output.empty())
		{
			printf("Error: no output file given.\n");
			return -1;
		}

		OutputLanguage language;
		if (FLAGS_cpp)
			language = OutputLanguage::eCPP;
		else if (FLAGS_rust)
			language = OutputLanguage::eRust;
		else if (FLAGS_csharp)
			language = OutputLanguage::eCSharp;
		else
		{
			printf("Error: no target language specified.\n");
			return -1;
		}

		// Verify the output directory exists.
		IO::Directory::Create(IO::Path::GetDirectory(FLAGS_output));

		IntrusivePtr<iIDLParser> parser;
		if (GOM::Succeeded(mpRegistry->Create(nullptr, iIDLParser::kCID, iIDLParser::kIID, parser.AsVoidPP())))
		{
			if (GOM::Succeeded(parser->Generate(language, FLAGS_input.c_str(), FLAGS_output.c_str())))
			{
				parser.Adopt(nullptr);
				return 0;
			}
		}

		return -1;
	}

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};

CPF_APPLICATION(IDLCommand);
