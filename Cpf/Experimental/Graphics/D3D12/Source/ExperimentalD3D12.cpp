//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"

#include "Adapter/WindowedApp.hpp"
#include "Logging/Logging.hpp"

#include "IntrusivePtr.hpp"
#include "Resources/ResourceConfig.hpp"
#include "Threading/Threading.hpp"
#include "Time/Time.hpp"

#include "Graphics/Driver.hpp"
#include "Graphics/DebugUI.hpp"

#include "Math/Vector4.hpp"

#include "Concurrency/Scheduler.hpp"
#include "Math/Constants.hpp"
#include "Math/Matrix33v.hpp"
#include "IO/IO.hpp"

#include "MovementSystem.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "RenderSystem.hpp"

#include "GO.hpp"
#include "Go/Object.hpp"
#include "GO/Systems/Timer.hpp"
#include "GO/Components/iTransformComponent.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;
using namespace Threading;
using namespace Concurrency;

//////////////////////////////////////////////////////////////////////////
#define GFX_INITIALIZER CPF_CONCAT(GFX_ADAPTER, Initializer)
#define INCLUDE_GFX Adapter/## CPF_CONCAT(GFX_ADAPTER, .hpp)
#include CPF_STRINGIZE(INCLUDE_GFX)
#define WINDOW_TITLE "Hello Triangle: " CPF_STRINGIZE(GFX_ADAPTER)


int ExperimentalD3D12::Start(const CommandLine&)
{
	// Initialize logging.
	CPF_INIT_LOG(Experimental);
	CPF_LOG_LEVEL(Experimental, Trace);

	// Initialize the gfx library.
	ScopedInitializer<TimeInitializer> timeInit;
	ScopedInitializer<ThreadingInitializer> threadingInit;
	ScopedInitializer<IOInitializer> ioInit;
	ScopedInitializer<Resources::ResourcesInitializer> resourceInit;
	ScopedInitializer<Adapter::GFX_INITIALIZER> gfxInit;
	ScopedInitializer<GOInitializer> goInit;

	// Hack: Setup the view all cheezy like.
	mViewportSize = 1.0f;
	mFOV = kDegToRad * 33.0f;
	float halfFov = tan(mFOV / 2.0f);
	mViewportSize = halfFov;
	mAspectRatio = 1.0f;

	//////////////////////////////////////////////////////////////////////////
	// Install object components.
	MoverSystem::MoverComponent::Install();
	
	//////////////////////////////////////////////////////////////////////////
	MultiCore::Pipeline::Create(mpMultiCore.AsTypePP());

	// Install the stage types.
	GO::ObjectStage::Install();
	MultiCore::SingleUpdateStage::Install();

	// Install the systems this will use.
	RenderSystem::Install();
	GO::Timer::Install();
	InstanceSystem::Install();
	MoverSystem::Install();

	//////////////////////////////////////////////////////////////////////////
	// Create the primary game timer.
	IntrusivePtr<GO::Timer> gameTime(MultiCore::System::Create<GO::Timer>("Game Time"));
	mpMultiCore->Install(gameTime);

	// Create the render system.
	RenderSystem::Desc renderDesc;
	renderDesc.mTimerID = gameTime->GetID();
	renderDesc.mpApplication = this;
	IntrusivePtr<RenderSystem> renderSystem(MultiCore::System::Create<RenderSystem>("Render System", &renderDesc));
	mpMultiCore->Install(renderSystem);

	// Create the instance management system.
	InstanceSystem::Desc instanceDesc;
	instanceDesc.mRenderSystemID = renderSystem->GetID();
	instanceDesc.mpApplication = this;
	IntrusivePtr<InstanceSystem> instanceSystem(MultiCore::System::Create<InstanceSystem>("Instance System", &instanceDesc, {
		// Add a dependency from this systems begin stage to the render systems begin frame stage.  It can run concurrently with the begin frame stage.
		{MultiCore::ExecutionMode::eConcurrent, MultiCore::StageID(InstanceSystem::kBegin.ID), renderSystem->GetID(), MultiCore::StageID(RenderSystem::kBeginFrame.ID) }
	}));
	mpMultiCore->Install(instanceSystem);

	// Create the mover system.
	MoverSystem::Desc moverDesc;
	moverDesc.mTimerID = gameTime->GetID();
	moverDesc.mInstanceID = instanceSystem->GetID();
	mpMoverSystem.Adopt(MultiCore::System::Create<MoverSystem>("Mover", &moverDesc, {
		{MultiCore::ExecutionMode::eSequencial, MultiCore::StageID(MoverSystem::kMoverStage.ID), instanceSystem->GetID(), MultiCore::StageID(InstanceSystem::kBegin.ID)}
	}));
	mpMultiCore->Install(mpMoverSystem);

	//////////////////////////////////////////////////////////////////////////
	// Everything is installed in the pipeline, configure it.
	mpMultiCore->Configure();

	// Create test objects.
	for (int i = 0; i<kInstanceCount; ++i)
	{
		IntrusivePtr<GO::iEntity> object(mGOService.CreateObject());
		object->CreateComponent<GO::iTransformComponent>(nullptr);
		object->CreateComponent<iMoverComponent>(mpMoverSystem);
	}

	//////////////////////////////////////////////////////////////////////////
	// Create the virtual file system locator.
	mpLocator.Adopt(Resources::Configuration("./Experimental/resource_config.json").GetLocator());
	if (!mpLocator)
	{
		// Do something with configuration error.
	}

	{
		_CreateWindow();

		//////////////////////////////////////////////////////////////////////////
		// Get an instance of the installed device from the graphics factory.
		{
			IntrusivePtr<iInstance> gfxInstance;
			Graphics::Create(1, gfxInstance.AsTypePP());
			if (gfxInstance)
			{
				IntrusivePtr<iAdapter> adapter;
				if (!_SelectAdapter(gfxInstance, adapter.AsTypePP()))
				{
					// Error...
				}
				// TODO: Should select an output and associate it during device creation for full screen modes.
				if (!_EnumerateOutputs(adapter))
				{
					// Error...
				}
				// Create a device on the desired adapter.
				gfxInstance->CreateDevice(adapter, mpDevice.AsTypePP());


				//////////////////////////////////////////////////////////////////////////
				if (!_CreateSwapChain(gfxInstance))
				{
					// Do something with the error.
				}

				//////////////////////////////////////////////////////////////////////////
				// Create command buffers for the 'overall' frame.  This sets up the rendering
				// and performs the presents as the first and last submitted command lists.
				for (int i = 0; i < mBackBufferCount; ++i)
				{
					mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP());
					mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP());
					mpDevice->CreateCommandBuffer(mpPreCommandPool[i], mpPreCommandBuffer[i].AsTypePP());
					mpDevice->CreateCommandBuffer(mpPostCommandPool[i], mpPostCommandBuffer[i].AsTypePP());
				}

				if (!_CreateResources())
				{
					// Do something with the error.
				}

				//////////////////////////////////////////////////////////////////////////
				// Start up the threading system.
				// Allocates a command pool and buffer per thread.
				Thread::Group workerThreads(Thread::GetHardwareThreadCount());
				mScheduler.Initialize(Move(workerThreads),
					SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_CreateWorkerData),
					SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_DestroyWorkerData),
					this
				);
				mThreadCountChanged = false;
				mThreadCount = mScheduler.ThreadCount();
				mQueue = Move(mScheduler.CreateQueue());

				//////////////////////////////////////////////////////////////////////////
				mStartTime = Time::Now();
				mCurrentTime = Time::Now() - mStartTime;

				// Currently only a single frame.  Will Eventually match the number of back buffers and other resources.
				Scheduler::Semaphore frameSemaphore(1);
				// Create a graphics fence to track back buffers.
				mpDevice->CreateFence(0, mpFence.AsTypePP());

				{
					if (!mDebugUI.Initialize(mpDevice, mpWindow, mpLocator))
					{
						CPF_LOG(Experimental, Info) << "Failed to initialize the debug UI.";
					}
					mDebugUI.SetWindowSize(mpWindow->GetClientArea().x, mpWindow->GetClientArea().y);
					AddRawInputHook(&DebugUI::HandleRawInput, &mDebugUI);

					//
					(*mpMultiCore)(mQueue);
					_UpdateStageList();
					mQueue.Discard();

					while (IsRunning())
					{
						//////////////////////////////////////////////////////////////////////////
						// Wait for the last frame of processing.
						frameSemaphore.Acquire();

						if (mThreadCountChanged)
						{
							mThreadCountChanged = false;
							mQueue.ActiveThreads(mThreadCount);
						}

						// Poll the application OS events.
						// TODO: this is done in between frames so resize doesn't conflict.
						// This will need to be overlap aware and that means that resize will need the ability
						// to flush the pipeline.
						Poll();

						// Handle any issued work from the scheduler side which needs to run in the main thread.
						for (; mReactor.RunOne();)
							;

						Atomic::Inc(mFrameIndex);
						Atomic::Store(mSubmissionIndex, Atomic::Load(mFrameIndex) * 3);
						Atomic::Store(mCurrentScheduledBuffer, 1);
						Atomic::Store(mCurrentBackbuffer, mpSwapChain->GetCurrentIndex());
						auto now = Time::Now() - mStartTime;
						mDeltaTime = now - mCurrentTime;
						mCurrentTime = now;

						//////////////////////////////////////////////////////////////////////////
						// Issue all the stages.
						(*mpMultiCore)(mQueue);

						//////////////////////////////////////////////////////////////////////////
						// Notify that the frame of processing is complete.
						mQueue.Submit(frameSemaphore);

						// And tell the scheduler to execute this work queue.
						mQueue.Execute(Scheduler::Queue::SubmissionType::eNormal);
					}

					// Guarantee last frame is complete before we tear everything down.
					frameSemaphore.Acquire();
					mDebugUI.Shutdown();
				}

				// Destroy all the resources.
				_DestroyResources();
			}
			gfxInstance.Assign(nullptr);
		}
	}
	return 0;
}

CPF_CREATE_APPLICATION(Cpf::ExperimentalD3D12);
