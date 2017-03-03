#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/Stage.hpp"
#include "Adapter/D3D12.hpp"
#include "NetworkSystem.hpp"
#include "RenderSystem.hpp"
#include "Resources/ResourceConfig.hpp"

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
	ScopedInitializer<IOInitializer> ioInit;
	ScopedInitializer<Resources::ResourcesInitializer> resourceInit;
	ScopedInitializer<MultiCoreInitializer> multicoreInit;
	ScopedInitializer<Adapter::D3D12Initializer> d3d12Init;

	if (_CreateWindow() && _Install() && _InitializeMultiCore())
	{
		if (_InitializeResources() && _InitializePipeline())
		{
			if (_ConfigurePipeline())
			{
				// Semaphore to track when the last submitted queue of work has completed.
				Concurrency::Scheduler::Semaphore complete;

				// Thread time information for tracking purposes.  Only updated every second.
				Time::Value lastTimeUpdate = Time::Now();
				Concurrency::Scheduler::ThreadTimeInfo loopThreadTimes;
				Concurrency::Scheduler::ThreadTimes loopThreadTimeQuery;

				// Run the event loop for the window.
				while (IsRunning())
				{
					Poll();
					(*mpPipeline)(mLoopScheduler);
					mLoopScheduler.Submit(complete);

					auto now = Time::Now();
					if (Time::Seconds(now - lastTimeUpdate) >= 1.0f)
					{
						mLoopScheduler.Submit(loopThreadTimeQuery);
						loopThreadTimes = loopThreadTimeQuery.GetResult();
						lastTimeUpdate = now;

						CPF_LOG(Networked, Info) << "------- Thread count: " << loopThreadTimes.mThreadCount << " - "
							<< float(Time::Seconds(loopThreadTimes.mDuration));
						for (int i=0; i<loopThreadTimes.mThreadCount; ++i)
						{
							CPF_LOG(Networked, Info) << "  Thread(" << i << ") User: "
								<< float(Time::Seconds(loopThreadTimes.mUserTime[i]))
								<< " Kernel: " << float(Time::Seconds(loopThreadTimes.mKernelTime[i]));
						}
					}

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


bool Networked::_CreateWindow()
{
	// Create the main window.
	Math::Vector2i mWindowSize(200, 200);
	mpWindow.Adopt(
		WindowDesc(this)
		.Title("Network Test")
		.Position(iWindow::Centered)
		.Size(mWindowSize)
		.Flags(iWindow::eResizable | iWindow::eShown)
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
		SingleUpdateStage::Remove()
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
	if(Pipeline::Create(mpPipeline.AsTypePP()))
	{
		mpNetworkSystem.Adopt(static_cast<NetworkSystem*>(mpPipeline->Install(System::Create<NetworkSystem>(mpPipeline, "Networking", nullptr))));
		mpRenderSystem.Adopt(static_cast<RenderSystem*>(mpPipeline->Install(System::Create<RenderSystem>(mpPipeline, "Rendering", nullptr))));
		if (mpRenderSystem && mpRenderSystem->Initialize(mpWindow))
		{
			return (
				mpNetworkSystem &&
				mpRenderSystem
				);
		}
	}
	return false;
}

bool Networked::_ConfigurePipeline()
{
	if (mpPipeline)
		return mpPipeline->Configure();
	return false;
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
