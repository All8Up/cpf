#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iPipeline.hpp"
#include "NetworkSystem.hpp"
#include "RenderSystem.hpp"
#include "Resources/ResourceConfig.hpp"
#include "Threading.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "IO/File.hpp"
#include "IO/Directory.hpp"
#include "SDL2/CIDs.hpp"
#include "Graphics/Driver.hpp"

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
	CPF_DROP_LOG(Networked);
}

COM::Result CPF_STDCALL Networked::Initialize(Plugin::iRegistry* registry, COM::ClassID* appCid)
{
	mpRegistry = registry;
	*appCid = SDL2::kWindowedApplicationCID;

	IOInitializer::Install();
	ConcurrencyInitializer::Install();
	Resources::ResourcesInitializer::Install();

	// Setup initial working directory.
	auto exePath = IO::File::GetExecutableFilePath();
	exePath += "../resources/";
	IO::Directory::SetWorkingDirectory(exePath);

	GetRegistry()->Load("plugins/Concurrency.cfp");
	// TODO: Temporary work around for concurrency *not* being a plugin yet.
	Concurrency::Scheduler::Install(GetRegistry());
	GetRegistry()->Load("plugins/Adapter_SDL2.cfp");
	GetRegistry()->Load("plugins/AdapterD3D12.cfp");
	GetRegistry()->Load("plugins/MultiCore.cfp");
	GetRegistry()->Load("plugins/DebugUI.cfp");

	return COM::kOK;
}

void CPF_STDCALL Networked::Shutdown()
{
	Resources::ResourcesInitializer::Remove();
	ConcurrencyInitializer::Remove();
	IOInitializer::Remove();
}

COM::Result CPF_STDCALL Networked::Main(iApplication* application)
{
	application->QueryInterface(iWindowedApplication::kIID, reinterpret_cast<void**>(&mpWindowedApplication));

	if (Succeeded(mpRegistry->Create(nullptr, Concurrency::kSchedulerCID, Concurrency::iScheduler::kIID, mpScheduler.AsVoidPP())))
	{
		if (_CreateWindow() && _Install() && _InitializeMultiCore())
		{
			if (_InitializeResources() && _InitializePipeline())
			{
				if (COM::Succeeded(_ConfigurePipeline()))
				{
					_ConfigureDebugUI();

					// Semaphore to track when the last submitted queue of work has completed.
					Concurrency::Semaphore complete;

					// Run the event loop for the window.
					while (mpWindowedApplication->IsRunning())
					{
						mpWindowedApplication->Poll();
						mpPipeline->Submit(mpScheduler);
						mpScheduler->Submit(&complete);
						complete.Acquire();

						// Keep balancing the threads.
						mLoadBalancer.Balance();
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
	return COM::kOK;
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
	auto activePoolThreads = self.mThreadPool.GetActiveThreads();

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
		COM::Succeeded(NetworkSystem::Install(GetRegistry())) &&
		COM::Succeeded(RenderSystem::Install(GetRegistry()))
		);
}

bool Networked::_Remove()
{
	return (
		COM::Succeeded(RenderSystem::Remove(GetRegistry())) &&
		COM::Succeeded(NetworkSystem::Remove(GetRegistry()))
		);
}

bool Networked::_InitializeResources()
{
	mpLocator.Adopt(Resources::Configuration("./networked/resource_config.json").GetLocator());
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
	if (COM::Succeeded(mpScheduler->Initialize(Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)) &&
		mThreadPool.Initialize(Thread::GetHardwareThreadCount()))
	{
		Concurrency::LoadBalancer::Schedulers schedulers(2);
		schedulers[0] = static_cast<Concurrency::Scheduler*>(mpScheduler.Ptr());
		schedulers[1] = &mThreadPool.GetScheduler();

		mLoadBalancer.SetSchedulers(&schedulers);
		return true;
	}
	return false;
}

bool Networked::_ShutdownMultiCore()
{
	mThreadPool.Shutdown();
	mpScheduler->Shutdown();
	return true;
}

bool Networked::_InitializePipeline()
{
	if (COM::Succeeded(GetRegistry()->Create(nullptr, MultiCore::kPipelineCID, MultiCore::iPipeline::kIID, mpPipeline.AsVoidPP())))
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
		COM::ClassID selectedAPI;
		if (COM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID, &typeCount, nullptr)))
		{
			Vector<COM::ClassID> classes(typeCount);
			if (COM::Succeeded(GetRegistry()->GetClasses(Graphics::iInstance::kIID, &typeCount, classes.data())))
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

COM::Result Networked::_ConfigurePipeline()
{
	if (mpPipeline)
		return mpPipeline->Configure();
	return COM::kInvalid;
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
