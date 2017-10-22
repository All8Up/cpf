#include "StarterApp.hpp"
#include "CPF/Logging.hpp"
#include "MultiCore.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "RenderSystem.hpp"
#include "Resources/iConfiguration.hpp"
#include "Concurrency/iFence.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "Application/iWindow.hpp"
#include "IO/File.hpp"
#include "IO/Directory.hpp"
#include "SDL2/CIDs.hpp"
#include "Graphics.hpp"
#include "Threading/Thread.hpp"
#include "PluginHost/Registry.hpp"

using namespace CPF;
using namespace Threading;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
StarterApp::StarterApp()
	: mpRegistry(nullptr)
	, mpWindowedApplication(nullptr)
{
	CPF_INIT_LOG(StarterApp);
}

StarterApp::~StarterApp()
{
	CPF_DROP_LOG(StarterApp);
}

namespace
{
	const char* kFileSystemPlugin = "plugins/BasicFilesystem.cfp";
	const char* kResourcePlugin = "plugins/Resources.cfp";
	const char* kConcurrencyPlugin = "plugins/Concurrency.cfp";
	const char* kAdapterSDL2Plugin = "plugins/AdapterSDL2.cfp";
	const char* kAdapterD3D12Plugin = "plugins/AdapterD3D12.cfp";
	const char* kMultiCorePlugin = "plugins/MultiCore.cfp";
	const char* kDebugUIPlugin = "plugins/DebugUI.cfp";
	const char* kPythonPlugin = "plugins/Python3.cfp";
	const char* kRustPlugin = "plugins/TestRust.cfp";
}

struct iTestRust : GOM::iUnknown
{
	virtual uint32_t CPF_STDCALL Test(uint32_t value) = 0;
};

GOM::Result CPF_STDCALL StarterApp::Initialize(Plugin::iRegistry* registry, GOM::ClassID* appCid)
{
	mpRegistry = registry;
	*appCid = SDL2::kWindowedApplicationCID;

	IOInitializer::Install();

	// Setup initial working directory.
	auto exePath = IO::File::GetExecutableFilePath();
	exePath += "../resources/";
	IO::Directory::SetWorkingDirectory(exePath);

	GetRegistry()->Load(kResourcePlugin);
	GetRegistry()->Load(kConcurrencyPlugin);
	GetRegistry()->Load(kAdapterSDL2Plugin);
	GetRegistry()->Load(kAdapterD3D12Plugin);
	GetRegistry()->Load(kMultiCorePlugin);
	GetRegistry()->Load(kDebugUIPlugin);
	/*
	if (GOM::Succeeded(GetRegistry()->Load(kPythonPlugin)))
	{
		if (GOM::Succeeded(GetRegistry()->Create(nullptr, Tools::kPython3CID.GetID(), Tools::iPython3::kIID.GetID(), mpPython3.AsVoidPP())))
		{
			String basePath = exePath;
			mpPython3->Initialize(basePath.c_str(), &PluginHost::CreateRegistry);
		}
	}
	*/
	if (GOM::Succeeded(GetRegistry()->Load(kRustPlugin)))
	{
		printf("Loaded rust plugin.");
		// Attempt to create Rust plugin.
		IntrusivePtr<iTestRust> testRust;
		if (GOM::Succeeded(GetRegistry()->Create(nullptr, 1, 1, testRust.AsVoidPP())))
		{
			static volatile int a = 0;
			++a;
			testRust->Test(1);
		}
	}

	return GOM::kOK;
}

void CPF_STDCALL StarterApp::Shutdown()
{
	// TODO: Need a solution to allow these pointers to be scoped such that
	// they don't end up dangling when the plugins are unloaded.
	/*
	if (mpPython3) mpPython3->Shutdown();
	mpPython3.Adopt(nullptr);
	*/
	mpRenderSystem.Adopt(nullptr);
	mpTimer.Adopt(nullptr);
	mpPipeline.Adopt(nullptr);
	mpLocator.Adopt(nullptr);
	mpLoadBalancer.Adopt(nullptr);
	mpThreadPool.Adopt(nullptr);
	mpScheduler.Adopt(nullptr);
	mpWindow.Adopt(nullptr);

	GetRegistry()->Unload(kRustPlugin);
	GetRegistry()->Unload(kPythonPlugin);
	GetRegistry()->Unload(kDebugUIPlugin);
	GetRegistry()->Unload(kMultiCorePlugin);
	GetRegistry()->Unload(kAdapterD3D12Plugin);
	GetRegistry()->Unload(kAdapterSDL2Plugin);
	GetRegistry()->Unload(kConcurrencyPlugin);
	GetRegistry()->Unload(kResourcePlugin);
	IOInitializer::Remove();
}

GOM::Result CPF_STDCALL StarterApp::Main(iApplication* application)
{
	application->QueryInterface(iWindowedApplication::kIID.GetID(), reinterpret_cast<void**>(&mpWindowedApplication));

	if (GOM::Succeeded(mpRegistry->Create(nullptr, Concurrency::kSchedulerCID.GetID(), Concurrency::iScheduler::kIID.GetID(), mpScheduler.AsVoidPP())))
	{
		if (_CreateWindow() && _Install() && _InitializeMultiCore())
		{
			if (_InitializeResources() && _InitializePipeline())
			{
				if (GOM::Succeeded(_ConfigurePipeline()))
				{
					_ConfigureDebugUI();

					// Semaphore to track when the last submitted queue of work has completed.
					IntrusivePtr<Concurrency::iFence> complete;
					GetRegistry()->Create(nullptr, Concurrency::kFenceCID.GetID(), Concurrency::iFence::kIID.GetID(), complete.AsVoidPP());

					// Run the event loop for the window.
					while (mpWindowedApplication->IsRunning())
					{
						mpWindowedApplication->Poll();
						mpPipeline->Submit(mpScheduler);
						mpScheduler->Submit(complete);
						complete->Wait();

						// Keep balancing the threads.
						mpLoadBalancer->Balance();
					}
				}
			}
			_ShutdownPipeline();
			_ShutdownResources();
		}
	}

	_ShutdownMultiCore();
	_Remove();

	// Destroy the window and exit.
	mpWindow.Assign(nullptr);
	return GOM::kOK;
}

void StarterApp::_ConfigureDebugUI()
{
	Graphics::iDebugUI* debugUI = mpRenderSystem->GetDebugUI();
	debugUI->Add(&StarterApp::_PerformanceUI, this);
	mLastTime = Time::Now();
}

void StarterApp::_PerformanceUI(Graphics::iDebugUI* ui, void* context)
{
	StarterApp& self = *reinterpret_cast<StarterApp*>(context);

	//////////////////////////////////////////////////////////////////////////
	ui->Begin("Performance");
	auto activeLoopThreads = self.mpScheduler->GetActiveThreads();
	auto activePoolThreads = self.mpThreadPool->GetActiveThreads();

	auto now = Time::Now();
	auto delta = now - self.mLastTime;
	self.mLastTime = now;
	int fps = int(float(Time::Seconds(1)) / float(Time::Seconds(delta)));

	ui->Text("           FPS: %d", fps);
	ui->Text("Worker threads: %d", activeLoopThreads);
	ui->Text("  Pool threads: %d", activePoolThreads);

	//////////////////////////////////////////////////////////////////////////
	ui->End();
}

bool StarterApp::_CreateWindow()
{
	// Create the main window.
	Math::Vector2i mWindowSize(400, 400);
	WindowDesc windowDesc;
	windowDesc.mpTitle = "Starter app";
	windowDesc.mX = iWindow::Centered();
	windowDesc.mY = iWindow::Centered();
	windowDesc.mWidth = mWindowSize.x;
	windowDesc.mHeight = mWindowSize.y;
	windowDesc.mFlags = WindowFlags::eResizable | WindowFlags::eShown;
	mpWindowedApplication->Create(&windowDesc, mpWindow.AsTypePP());

	if (mpWindow)
	{
		// Bind the window events.
		mpWindow->GetEmitter()->On<iWindow::OnResize>(Bind(&StarterApp::_Resize, this, Placeholders::_1, Placeholders::_2));
		return true;
	}
	return false;
}

bool StarterApp::_Install()
{
	return (
		GOM::Succeeded(RenderSystem::Install(GetRegistry()))
		);
}

bool StarterApp::_Remove()
{
	return (
		GOM::Succeeded(RenderSystem::Remove(GetRegistry()))
		);
}

bool StarterApp::_InitializeResources()
{
//	Resources::Configuration config;
//	config.Parse("./starterapp/resource_config.json");
	Resources::iConfiguration* pConfig = nullptr;
	GetRegistry()->Create(nullptr, Resources::kConfigurationCID.GetID(), Resources::iConfiguration::kIID.GetID(), reinterpret_cast<void**>(&pConfig));
	pConfig->Initialize(GetRegistry(), "./Experimental/resource_config.json");
	mpLocator.Adopt(pConfig->GetLocator());
//	mpLocator.Adopt(Resources::Configuration(GetRegistry(), "./starterapp/resource_config.json").GetLocator());
	return bool(mpLocator);
}

bool StarterApp::_ShutdownResources()
{
	if (mpLocator)
	{
		mpLocator.Adopt(nullptr);
		return true;
	}
	return false;
}

bool StarterApp::_InitializeMultiCore()
{
	GetRegistry()->Create(nullptr, kThreadPoolCID.GetID(), iThreadPool::kIID.GetID(), mpThreadPool.AsVoidPP());
	if (GOM::Succeeded(mpScheduler->Initialize(Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)) &&
		mpThreadPool->Initialize(GetRegistry(), Thread::GetHardwareThreadCount()))
	{
		GetRegistry()->Create(nullptr, Concurrency::kLoadBalancerCID.GetID(), Concurrency::iLoadBalancer::kIID.GetID(), mpLoadBalancer.AsVoidPP());
		Concurrency::iScheduler* schedulers[] = {mpScheduler, mpThreadPool->GetScheduler()};
		mpLoadBalancer->Initialize(GetRegistry(), 2, schedulers);
		return true;
	}
	return false;
}

bool StarterApp::_ShutdownMultiCore()
{
	mpThreadPool->Shutdown();
	mpScheduler->Shutdown();
	return true;
}

bool StarterApp::_InitializePipeline()
{
	if (GOM::Succeeded(GetRegistry()->Create(nullptr, MultiCore::kExecutionPlanCID.GetID(), MultiCore::iExecutionPlan::kIID.GetID(), mpPipeline.AsVoidPP())))
	{
		GetRegistry()->Create(nullptr, MultiCore::kTimerCID.GetID(), MultiCore::iTimer::kIID.GetID(), mpTimer.AsVoidPP());
		mpTimer->Initialize(GetRegistry(), "Game Time", nullptr);
		mpPipeline->Install(mpTimer);

		//////////////////////////////////////////////////////////////////////////
		// Find graphics driver implementations.
		int32_t typeCount = 0;
		GOM::ClassID selectedAPI;
		if (GOM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID.GetID(), &typeCount, nullptr)))
		{
			Vector<uint64_t> classes(typeCount);
			if (GOM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID.GetID(), &typeCount, classes.data())))
			{
				if (typeCount > 0)
					selectedAPI = GOM::ClassID(classes[0]);
			}
		}

		RenderSystem::Desc renderDesc;
		renderDesc.mTimer = mpTimer->GetID();
		GetRegistry()->Create(nullptr, kRenderSystemCID.GetID(), RenderSystem::kIID.GetID(), mpRenderSystem.AsVoidPP());
		mpRenderSystem->Initialize(GetRegistry(), "Rendering", &renderDesc);
		mpPipeline->Install(mpRenderSystem);
		if (mpTimer && mpRenderSystem && mpRenderSystem->Initialize(GetRegistry(), selectedAPI, mpWindowedApplication->GetInputManager(), mpWindow, mpLocator))
		{
			return (
				mpTimer &&
				mpRenderSystem
				);
		}
	}
	return false;
}

GOM::Result StarterApp::_ConfigurePipeline()
{
	if (mpPipeline)
		return mpPipeline->Configure(GetRegistry());
	return GOM::kInvalid;
}

bool StarterApp::_ShutdownPipeline()
{
	if (mpPipeline)
	{
		mpRenderSystem->Shutdown();
		mpRenderSystem.Adopt(nullptr);
		mpPipeline.Adopt(nullptr);
		return true;
	}
	return false;
}

void StarterApp::_Resize(int32_t width, int32_t height)
{
	mpRenderSystem->Resize(width, height);
}


//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPMAIN(CPF::StarterApp);
