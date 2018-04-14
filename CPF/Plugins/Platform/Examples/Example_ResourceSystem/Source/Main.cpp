//////////////////////////////////////////////////////////////////////////
#define CPF_PLUGIN_STATIC
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/IO/File.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/Platform/ResourceSystem/iConfiguration.hpp"
#include "CPF/Platform/ResourceSystem/iLocator.hpp"

using namespace CPF;

class BasicWindowedApp : public GOM::tUnknown<iApplication>
{
public:
	BasicWindowedApp(Plugin::iRegistry* registry)
		: mpRegistry(registry)
	{}

	int32_t Run() override
	{
		// Setup initial working directory to be in the
		// resources directory.
		auto exePath = IO::File::GetExecutableFilePath();
		exePath += "../resources/";
		IO::Directory::SetWorkingDirectory(exePath);

		// Load the resource system plugin
		if (GOM::Succeeded(mpRegistry->Load("./plugins/ResourceSystem.cfp")))
		{
			ResourceSystem::iConfiguration* pConfig = nullptr;
			GetRegistry()->Create(nullptr, ResourceSystem::iConfiguration::kCID, ResourceSystem::iConfiguration::kIID, reinterpret_cast<void**>(&pConfig));
			pConfig->Load("./examples_resourcesapp/resource_config.json");
			if (pConfig->GetLocator().CheckOK(*mpLocator.AsTypePP()))
			{
			}

			// TODO: The resource system is going to move to a purely asynchronous model
			// eventually, this will need to change.
			// 
			// For the purposes here, we go directly to a synchronous stream for testing.
			// There are no loaders available that know what to do with a text file since
			// they are not used in any meaningful manner at this time.
			IO::Stream* testData = mpLocator->Open(mpLocator->CreateID("test_data/", "test.txt"), ResourceSystem::VariantID::eInvalid);
			if (testData)
			{
				STD::String testText = ReadText(testData).GetOK();
				// NOTE: Due to differences in line endings and file end
				// markers, this is cast to a cstring and back to a String
				// which has the effect of cleaning things up so it matches
				// the string literal here.
				if (STD::String(testText.c_str()) == "Hello Resources!")
				{
					return 0;
				}
			}
		}
		return -1;
	}

	Plugin::iRegistry* GetRegistry() { return mpRegistry; }

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
	IntrusivePtr<ResourceSystem::iLocator> mpLocator;
};

CPF_APPLICATION(BasicWindowedApp);
