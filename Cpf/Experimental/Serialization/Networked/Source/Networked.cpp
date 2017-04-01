#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/iPipeline.hpp"
#include "MultiCore/Stage.hpp"
#include "Adapter/D3D12.hpp"
#include "NetworkSystem.hpp"
#include "RenderSystem.hpp"
#include "Resources/ResourceConfig.hpp"
#include "Threading.hpp"
#include "Application/WindowFlags.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Threading;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
Networked::Networked()
{
	CPF_INIT_LOG(Networked);
}

Networked::~Networked()
{
	CPF_DROP_LOG(Networked);
}

int Networked::Start(const CommandLine&)
{
	// Initialize libraries.
	ScopedInitializer<TimeInitializer> timeInit;
	ScopedInitializer<ThreadingInitializer> threadingInit;
	ScopedInitializer<ConcurrencyInitializer> concurrencyInit;
	ScopedInitializer<IOInitializer> ioInit;
	ScopedInitializer<Resources::ResourcesInitializer> resourceInit;
	ScopedInitializer<MultiCoreInitializer, Plugin::iRegistry*> multicoreInit(static_cast<Plugin::iRegistry*>(GetRegistry()));
	ScopedInitializer<Adapter::D3D12Initializer> d3d12Init;

	if (_CreateWindow() && _Install() && _InitializeMultiCore())
	{
		if (_InitializeResources() && _InitializePipeline())
		{
			if (COM::Succeeded(_ConfigurePipeline()))
			{
				_ConfigureDebugUI();

				// Semaphore to track when the last submitted queue of work has completed.
				Concurrency::Scheduler::Semaphore complete;

				// Run the event loop for the window.
				while (IsRunning())
				{
					Poll();
					mpPipeline->Submit(&mLoopScheduler);
					mLoopScheduler.Submit(complete);
					complete.Acquire();

					// Keep balancing the threads.
					mLoadBalancer.Balance();
				}
			}
		}
		_ShutdownPipeline();
		_ShutdownResources();
	}

	_ShutdownMultiCore();
	_Remove();

	// Destroy the window and exit.
	mpWindow.Assign(nullptr);
	return 0;
}

void Networked::_ConfigureDebugUI()
{
	Graphics::DebugUI& debugUI = mpRenderSystem->GetDebugUI();
	debugUI.Add(&Networked::_PerformanceUI, this);
	mLastTime = Time::Now();
}

void Networked::_PerformanceUI(Graphics::DebugUI* ui, void* context)
{
	Networked& self = *reinterpret_cast<Networked*>(context);

	//////////////////////////////////////////////////////////////////////////
	ui->Begin("Performance");
	auto activeLoopThreads = self.mLoopScheduler.GetActiveThreads();
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
	mpWindow.Adopt(
		WindowDesc(this)
		.Title("Network Test")
		.Position(iWindow::Centered)
		.Size(mWindowSize)
		.Flags(WindowFlags::eResizable | WindowFlags::eShown)
	);

	if (mpWindow)
	{
		// Bind the window events.
		mpWindow->GetEmitter().On<iWindow::OnResized>(Bind(&Networked::_Resize, this, Placeholders::_1, Placeholders::_2));
		return true;
	}
	return false;
}

bool Networked::_Install()
{
	return (
		Timer::Install() &&
		SingleUpdateStage::Install() &&
		NetworkSystem::Install() &&
		RenderSystem::Install()
		);
}

bool Networked::_Remove()
{
	return (
		RenderSystem::Remove() &&
		NetworkSystem::Remove() &&
		SingleUpdateStage::Remove() &&
		Timer::Remove()
		);
}

bool Networked::_InitializeResources()
{
	mpLocator.Adopt(Resources::Configuration("./Networked/resource_config.json").GetLocator());
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
	if (mLoopScheduler.Initialize(Move(Thread::Group(Thread::GetHardwareThreadCount()))) &&
		mThreadPool.Initialize(Move(Thread::Group(Thread::GetHardwareThreadCount()))))
	{
		mLoadBalancer.SetSchedulers({&mLoopScheduler, &mThreadPool.GetScheduler()});
		return true;
	}
	return false;
}

bool Networked::_ShutdownMultiCore()
{
	mThreadPool.Shutdown();
	mLoopScheduler.Shutdown();
	return true;
}

bool Networked::_InitializePipeline()
{
	if (COM::Succeeded(GetRegistry()->Create(nullptr, MultiCore::kPipelineCID, MultiCore::iPipeline::kID, mpPipeline.AsVoidPP())))
	{
		mpTimer.Adopt(static_cast<Timer*>(mpPipeline->Install(System::Create<Timer>(mpPipeline, "Timer", nullptr))));
		mpNetworkSystem.Adopt(static_cast<NetworkSystem*>(mpPipeline->Install(System::Create<NetworkSystem>(mpPipeline, "Networking", nullptr))));

		RenderSystem::Desc renderDesc;
		renderDesc.mTimer = mpTimer->GetID();
		mpRenderSystem.Adopt(static_cast<RenderSystem*>(mpPipeline->Install(System::Create<RenderSystem>(mpPipeline, "Rendering", &renderDesc))));
		if (mpTimer && mpRenderSystem && mpRenderSystem->Initialize(mpWindow, mpLocator))
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
CPF_CREATE_APPLICATION(Cpf::Networked);
