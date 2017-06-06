#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iPipeline.hpp"
#include "NetworkSystem.hpp"
#include "RenderSystem.hpp"
#include "Resources/iConfiguration.hpp"
#include "Concurrency/iFence.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "IO/File.hpp"
#include "IO/Directory.hpp"
#include "SDL2/CIDs.hpp"
#include "Graphics/Driver.hpp"
#include "Threading/Thread.hpp"
#include "PluginHost/Registry.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Threading;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
Networked::Networked()
	: mpRegistry(nullptr)
	, mpWindowedApplication(nullptr)
{
	CPF_INIT_LOG(Networked);
}

Networked::~Networked()
{
	if (mpPython3)
		mpPython3->Shutdown();
	CPF_DROP_LOG(Networked);
}

GOM::Result CPF_STDCALL Networked::Initialize(Plugin::iRegistry* registry, GOM::ClassID* appCid)
{
	mpRegistry = registry;
	*appCid = SDL2::kWindowedApplicationCID;

	IOInitializer::Install();

	// Setup initial working directory.
	auto exePath = IO::File::GetExecutableFilePath();
	exePath += "../resources/";
	IO::Directory::SetWorkingDirectory(exePath);

	GetRegistry()->Load("plugins/Resources.cfp");
	GetRegistry()->Load("plugins/Concurrency.cfp");
	GetRegistry()->Load("plugins/Adapter_SDL2.cfp");
	GetRegistry()->Load("plugins/AdapterD3D12.cfp");
	GetRegistry()->Load("plugins/MultiCore.cfp");
	GetRegistry()->Load("plugins/DebugUI.cfp");
	if (Succeeded(GetRegistry()->Load("plugins/Python3.cfp")))
	{
		if (Succeeded(GetRegistry()->Create(nullptr, Tools::kPython3CID, Tools::iPython3::kIID, mpPython3.AsVoidPP())))
		{
			String basePath = exePath;
			mpPython3->Initialize(basePath.c_str(), &PluginHost::CreateRegistry);
		}
	}

	return GOM::kOK;
}

void CPF_STDCALL Networked::Shutdown()
{
	IOInitializer::Remove();
}

GOM::Result CPF_STDCALL Networked::Main(iApplication* application)
{
	application->Cast(iWindowedApplication::kIID, reinterpret_cast<void**>(&mpWindowedApplication));

	if (Succeeded(mpRegistry->Create(nullptr, Concurrency::kSchedulerCID, Concurrency::iScheduler::kIID, mpScheduler.AsVoidPP())))
	{
		if (_CreateWindow() && _Install() && _InitializeMultiCore())
		{
			if (_InitializeResources() && _InitializePipeline())
			{
				if (Succeeded(_ConfigurePipeline()))
				{
					_ConfigureDebugUI();

					// Semaphore to track when the last submitted queue of work has completed.
					IntrusivePtr<Concurrency::iFence> complete;
					GetRegistry()->Create(nullptr, Concurrency::kFenceCID, Concurrency::iFence::kIID, complete.AsVoidPP());

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

void Networked::_ConfigureDebugUI()
{
	Graphics::iDebugUI* debugUI = mpRenderSystem->GetDebugUI();
	debugUI->Add(&Networked::_PerformanceUI, this);
	mLastTime = Time::Now();
}

void Networked::_PerformanceUI(Graphics::iDebugUI* ui, void* context)
{
	Networked& self = *reinterpret_cast<Networked*>(context);

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

bool Networked::_CreateWindow()
{
	// Create the main window.
	Math::Vector2i mWindowSize(400, 400);
	WindowDesc windowDesc;
	windowDesc.mpTitle = "Network Test";
	windowDesc.mX = iWindow::Centered();
	windowDesc.mY = iWindow::Centered();
	windowDesc.mWidth = mWindowSize.x;
	windowDesc.mHeight = mWindowSize.y;
	windowDesc.mFlags = WindowFlags::eResizable | WindowFlags::eShown;
	mpWindowedApplication->Create(&windowDesc, mpWindow.AsTypePP());

	if (mpWindow)
	{
		// Bind the window events.
		mpWindow->GetEmitter()->On<iWindow::OnResize>(Bind(&Networked::_Resize, this, Placeholders::_1, Placeholders::_2));
		return true;
	}
	return false;
}

bool Networked::_Install()
{
	return (
		GOM::Succeeded(NetworkSystem::Install(GetRegistry())) &&
		GOM::Succeeded(RenderSystem::Install(GetRegistry()))
		);
}

bool Networked::_Remove()
{
	return (
		GOM::Succeeded(RenderSystem::Remove(GetRegistry())) &&
		GOM::Succeeded(NetworkSystem::Remove(GetRegistry()))
		);
}

bool Networked::_InitializeResources()
{
//	Resources::Configuration config;
//	config.Parse("./networked/resource_config.json");
	Resources::iConfiguration* pConfig = nullptr;
	GetRegistry()->Create(nullptr, Resources::kConfigurationCID, Resources::iConfiguration::kIID, reinterpret_cast<void**>(&pConfig));
	pConfig->Initialize(GetRegistry(), "./Experimental/resource_config.json");
	mpLocator.Adopt(pConfig->GetLocator());
//	mpLocator.Adopt(Resources::Configuration(GetRegistry(), "./networked/resource_config.json").GetLocator());
	return bool(mpLocator);
}

bool Networked::_ShutdownResources()
{
	if (mpLocator)
	{
		mpLocator.Adopt(nullptr);
		return true;
	}
	return false;
}

bool Networked::_InitializeMultiCore()
{
	GetRegistry()->Create(nullptr, kThreadPoolCID, iThreadPool::kIID, mpThreadPool.AsVoidPP());
	if (GOM::Succeeded(mpScheduler->Initialize(Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)) &&
		mpThreadPool->Initialize(GetRegistry(), Thread::GetHardwareThreadCount()))
	{
		GetRegistry()->Create(nullptr, Concurrency::kLoadBalancerCID, Concurrency::iLoadBalancer::kIID, mpLoadBalancer.AsVoidPP());
		Concurrency::iScheduler* schedulers[] = {mpScheduler, mpThreadPool->GetScheduler()};
		mpLoadBalancer->Initialize(GetRegistry(), 2, schedulers);
		return true;
	}
	return false;
}

bool Networked::_ShutdownMultiCore()
{
	mpThreadPool->Shutdown();
	mpScheduler->Shutdown();
	return true;
}

bool Networked::_InitializePipeline()
{
	if (GOM::Succeeded(GetRegistry()->Create(nullptr, MultiCore::kPipelineCID, MultiCore::iPipeline::kIID, mpPipeline.AsVoidPP())))
	{
		GetRegistry()->Create(nullptr, MultiCore::kTimerCID, MultiCore::iTimer::kIID, mpTimer.AsVoidPP());
		mpTimer->Initialize(GetRegistry(), "Game Time", nullptr);
		mpPipeline->Install(mpTimer);

		GetRegistry()->Create(nullptr, kNetworkSystemCID, NetworkSystem::kIID, mpNetworkSystem.AsVoidPP());
		mpNetworkSystem->Initialize(GetRegistry(), "Networking", nullptr);
		mpPipeline->Install(mpNetworkSystem);

		//////////////////////////////////////////////////////////////////////////
		// Find graphics driver implementations.
		int32_t typeCount = 0;
		GOM::ClassID selectedAPI;
		if (GOM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID, &typeCount, nullptr)))
		{
			Vector<GOM::ClassID> classes(typeCount);
			if (GOM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID, &typeCount, classes.data())))
			{
				if (typeCount > 0)
					selectedAPI = classes[0];
			}
		}

		RenderSystem::Desc renderDesc;
		renderDesc.mTimer = mpTimer->GetID();
		GetRegistry()->Create(nullptr, kRenderSystemCID, RenderSystem::kIID, mpRenderSystem.AsVoidPP());
		mpRenderSystem->Initialize(GetRegistry(), "Rendering", &renderDesc);
		mpPipeline->Install(mpRenderSystem);
		if (mpTimer && mpRenderSystem && mpRenderSystem->Initialize(GetRegistry(), selectedAPI, mpWindowedApplication->GetInputManager(), mpWindow, mpLocator))
		{
			return (
				mpTimer &&
				mpNetworkSystem &&
				mpRenderSystem
				);
		}
	}
	return false;
}

GOM::Result Networked::_ConfigurePipeline()
{
	if (mpPipeline)
		return mpPipeline->Configure(GetRegistry());
	return GOM::kInvalid;
}

bool Networked::_ShutdownPipeline()
{
	if (mpPipeline)
	{
		mpRenderSystem->Shutdown();
		mpNetworkSystem.Adopt(nullptr);
		mpRenderSystem.Adopt(nullptr);
		mpPipeline.Adopt(nullptr);
		return true;
	}
	return false;
}

void Networked::_Resize(int32_t width, int32_t height)
{
	mpRenderSystem->Resize(width, height);
}


//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPMAIN(Cpf::Networked);
