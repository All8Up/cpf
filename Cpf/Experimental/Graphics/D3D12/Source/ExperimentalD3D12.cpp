//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"

#include "Application/iWindowedApplication.hpp"
#include "Logging/Logging.hpp"

#include "Atomic/Atomic.hpp"
#include "IntrusivePtr.hpp"
#include "Resources/iConfiguration.hpp"
#include "Threading.hpp"
#include "Threading/Thread.hpp"

#include "Graphics/Driver.hpp"
#include "iDebugUI.hpp"

#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iFence.hpp"

#include "Math/Constants.hpp"
#include "Math/Matrix33v.hpp"
#include "IO/IO.hpp"
#include "IO/File.hpp"
#include "IO/Directory.hpp"

#include "MovementSystem.hpp"
#include "RenderSystem.hpp"

#include "EntityService.hpp"
#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "MultiCore.hpp"

#include "SDL2/CIDs.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;
using namespace Threading;
using namespace Concurrency;

//////////////////////////////////////////////////////////////////////////
#define WINDOW_TITLE "Hello Triangle: D3D12"


void ExperimentalD3D12::ReconfigurePipeline()
{
	mpMultiCore->Configure(GetRegistry());
}

COM::Result CPF_STDCALL ExperimentalD3D12::Initialize(Plugin::iRegistry* registry, COM::ClassID* appCid)
{
	mpRegistry = registry;
	*appCid = SDL2::kWindowedApplicationCID;

	// Setup initial working directory.
	auto exePath = IO::File::GetExecutableFilePath();
	exePath += "../resources/";
	IO::Directory::SetWorkingDirectory(exePath);

	GetRegistry()->Load("plugins/Resources.cfp");
	GetRegistry()->Load("plugins/Adapter_SDL2.cfp");
	GetRegistry()->Load("plugins/AdapterD3D12.cfp");
	GetRegistry()->Load("plugins/Concurrency.cfp");
	return COM::kOK;
}

void CPF_STDCALL ExperimentalD3D12::Shutdown()
{

}

COM::Result ExperimentalD3D12::Main(iApplication* application)
{
	application->QueryInterface(iWindowedApplication::kIID, reinterpret_cast<void**>(&mpApplication));

	// Initialize logging.
	CPF_INIT_LOG(Experimental);
	CPF_LOG_LEVEL(Experimental, Trace);

	// Initialize the io library.
	ScopedInitializer<IOInitializer> ioInit;

	CPF_INIT_MULTICORE(GetRegistry(), "plugins");
	CPF_INIT_ENTITYSERVICE(GetRegistry(), "plugins");
	GetRegistry()->Load("plugins/DebugUI.cfp");

	// Hack: Setup the view all cheezy like.
	mViewportSize = 1.0f;
	mFOV = kDegToRad * 33.0f;
	float halfFov = tan(mFOV / 2.0f);
	mViewportSize = halfFov;
	mAspectRatio = 1.0f;

	//////////////////////////////////////////////////////////////////////////
	GetRegistry()->Create(nullptr, EntityService::kManagerCID, EntityService::iManager::kIID, mpEntityManager.AsVoidPP());

	//////////////////////////////////////////////////////////////////////////
	// Install object components.
	MoverSystem::MoverComponent::Install(GetRegistry());
	
	//////////////////////////////////////////////////////////////////////////
	GetRegistry()->Create(nullptr, MultiCore::kPipelineCID, MultiCore::iPipeline::kIID, mpMultiCore.AsVoidPP());

	// Install the systems this will use.
	RenderSystem::Install(GetRegistry());
	InstanceSystem::Install(GetRegistry());
	MoverSystem::Install(GetRegistry());

	//////////////////////////////////////////////////////////////////////////
	// Create the primary game timer.
	IntrusivePtr<MultiCore::iTimer> gameTime;
	GetRegistry()->Create(nullptr, MultiCore::kTimerCID, MultiCore::iTimer::kIID, gameTime.AsVoidPP());
	gameTime->Initialize(GetRegistry(), "Game Time", nullptr);

	mpMultiCore->Install(gameTime);

	// Create the render system.
	RenderSystem::Desc renderDesc;
	renderDesc.mTimerID = gameTime->GetID();
	renderDesc.mpApplication = this;
	IntrusivePtr<RenderSystem> renderSystem;
	GetRegistry()->Create(nullptr, kRenderSystemCID, RenderSystem::kIID, renderSystem.AsVoidPP());
	renderSystem->Initialize(GetRegistry(), "Render System", &renderDesc);
	mpMultiCore->Install(renderSystem);

	// Create the instance management system.
	InstanceSystem::Desc instanceDesc;
	instanceDesc.mRenderSystemID = renderSystem->GetID();
	instanceDesc.mpApplication = this;
	IntrusivePtr<InstanceSystem> instanceSystem;
	GetRegistry()->Create(nullptr, kInstanceSystemCID, InstanceSystem::kIID, instanceSystem.AsVoidPP());
	instanceSystem->Initialize(GetRegistry(), "Instance System", &instanceDesc);
	mpMultiCore->Install(instanceSystem);

	// Create the mover system.
	MoverSystem::Desc moverDesc;
	moverDesc.mpApplication = this;
	moverDesc.mTimerID = gameTime->GetID();
	moverDesc.mInstanceID = instanceSystem->GetID();
	GetRegistry()->Create(nullptr, kMoverSystemCID, MoverSystem::kIID, mpMoverSystem.AsVoidPP());
	mpMoverSystem->Initialize(GetRegistry(), "Mover", &moverDesc);
	mpMultiCore->Install(mpMoverSystem);

	//////////////////////////////////////////////////////////////////////////
	// Add the required inter-system dependencies.
	// Render system needs to draw after instancing is complete.
	renderSystem->AddDependency({
		{ renderSystem->GetID(), RenderSystem::kDrawInstances, MultiCore::iStage::kExecute },
		{ instanceSystem->GetID(), InstanceSystem::kEnd, MultiCore::iStage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});

	// Instance system needs to begin after render system begin.
	// Instance system needs to end after movement update.
	instanceSystem->AddDependency({
		{ instanceSystem->GetID(), InstanceSystem::kBegin, MultiCore::iStage::kExecute },
		{ renderSystem->GetID(), RenderSystem::kBeginFrame, MultiCore::iStage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
	instanceSystem->AddDependency({
		{ instanceSystem->GetID(), InstanceSystem::kEnd, MultiCore::iStage::kExecute },
		{ mpMoverSystem->GetID(), MoverSystem::kUpdate, MultiCore::iStage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});

	// Mover updates must happen after game time update and instance begin.
	mpMoverSystem->AddDependency({
		{ mpMoverSystem->GetID(), MoverSystem::kUpdate, MultiCore::iStage::kExecute },
		{ gameTime->GetID(), MultiCore::iStage::kStageID, MultiCore::iStage::kExecute },
		MultiCore::DependencyPolicy::eBarrier
	});
	mpMoverSystem->AddDependency({
		{ mpMoverSystem->GetID(), MoverSystem::kUpdate, MultiCore::iStage::kExecute },
		{ instanceSystem->GetID(), InstanceSystem::kBegin, MultiCore::iStage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});


	//////////////////////////////////////////////////////////////////////////
	// Everything is installed in the pipeline, configure it.
	ReconfigurePipeline();

	// Create test objects.
	for (int i = 0; i<kInstanceCount; ++i)
	{
		IntrusivePtr<EntityService::iEntity> entity(mpEntityManager->CreateEntity());
		entity->CreateComponent<EntityService::iTransformComponent>(GetRegistry(), EntityService::kTransformComponentCID, nullptr);
		entity->CreateComponent<iMoverComponent>(GetRegistry(), kMoverComponentCID, mpMoverSystem);
	}

	//////////////////////////////////////////////////////////////////////////
	// Create the virtual file system locator.
	Resources::iConfiguration* pConfig = nullptr;
	GetRegistry()->Create(nullptr, Resources::kConfigurationCID, Resources::iConfiguration::kIID, reinterpret_cast<void**>(&pConfig));
	pConfig->Initialize(GetRegistry(), "./Experimental/resource_config.json");
	mpLocator.Adopt(pConfig->GetLocator());

//	mpLocator.Adopt(Resources::Configuration(GetRegistry(), "./Experimental/resource_config.json").GetLocator());
	if (!mpLocator)
	{
		// Do something with configuration error.
	}

	{
		_CreateWindow();

		//////////////////////////////////////////////////////////////////////////
		// Get an instance of the installed device from the graphics factory.
		{
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

			IntrusivePtr<iInstance> gfxInstance;
			GetRegistry()->Create(nullptr, selectedAPI, Graphics::iInstance::kIID, gfxInstance.AsVoidPP());
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
					mpDevice->CreateCommandBuffer(mpPreCommandPool[i], CommandBufferType::kPrimary, mpPreCommandBuffer[i].AsTypePP());
				}

				if (!_CreateResources())
				{
					// Do something with the error.
				}

				//
				GetRegistry()->Create(nullptr, kDebugUICID, iDebugUI::kIID, mpDebugUI.AsVoidPP());

				//////////////////////////////////////////////////////////////////////////
				// Start up the threading system.
				// Allocates a command pool and buffer per thread.
				GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, mpScheduler.AsVoidPP());
				mpScheduler->Initialize(Thread::GetHardwareThreadCount(),
					SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_CreateWorkerData),
					SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_DestroyWorkerData),
					this
				);
				mThreadCountChanged = false;
				mThreadCount = mpScheduler->GetMaxThreads();
				
				//////////////////////////////////////////////////////////////////////////
				mStartTime = Time::Now();
				mCurrentTime = Time::Now() - mStartTime;

				// Currently only a single frame.  Will Eventually match the number of back buffers and other resources.
				IntrusivePtr<Concurrency::iFence> concurrencyFence;
				GetRegistry()->Create(nullptr, Concurrency::kFenceCID, Concurrency::iFence::kIID, concurrencyFence.AsVoidPP());
				concurrencyFence->Signal();

				// Create a graphics fence to track back buffers.
				mpDevice->CreateFence(0, mpFence.AsTypePP());

				{
					if (!mpDebugUI->Initialize(mpDevice, mpApplication->GetInputManager(), mpWindow, mpLocator))
					{
						CPF_LOG(Experimental, Info) << "Failed to initialize the debug UI.";
					}
					int32_t w, h;
					mpWindow->GetClientAreaSize(&w, &h);
					mpDebugUI->SetWindowSize(w, h);

					//
					_UpdatePipelineDisplay();

					while (mpApplication->IsRunning())
					{
						//////////////////////////////////////////////////////////////////////////
						// Wait for the last frame of processing.
						concurrencyFence->Wait();

						if (mThreadCountChanged)
						{
							mThreadCountChanged = false;
							mpScheduler->SetActiveThreads(mThreadCount);
						}

						// Poll the application OS events.
						// TODO: this is done in between frames so resize doesn't conflict.
						// This will need to be overlap aware and that means that resize will need the ability
						// to flush the pipeline.
						mpApplication->Poll();

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
						mpMultiCore->Submit(mpScheduler);

						//////////////////////////////////////////////////////////////////////////
						// Notify that the frame of processing is complete.
						mpScheduler->Submit(concurrencyFence);
					}

					// Guarantee last frame is complete before we tear everything down.
					concurrencyFence->Wait();
					mpDebugUI->Shutdown();
				}

				// Destroy all the resources.
				_DestroyResources();
			}
			gfxInstance.Assign(nullptr);
		}
	}
	return COM::kOK;
}

CPF_CREATE_APPMAIN(Cpf::ExperimentalD3D12);
