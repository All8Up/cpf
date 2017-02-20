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

#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#include "Concurrency/Scheduler.hpp"
#include "Math/Constants.hpp"
#include <math.h>
#include "IO/IO.hpp"

#include "GO.hpp"
#include "GO/Components/TransformComponent.hpp"
#include "GO/Systems/Timer.hpp"
#include "Adapter/D3D12/Instance.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;
using namespace Threading;
using namespace Concurrency;

//////////////////////////////////////////////////////////////////////////
// Some temporary work to get the system/service organization stood up at
// least somewhat correctly.

/*
Stage notes:
	Stages should likely just be a container for a dispatch method which
	handles appropriate multicore dispatch.  General types would be:
		Stage<Single> = Single thread of execution.
		Stage<EvenPartions> = Partitioned multicore.  Simple divide and conquer approach.
		Stage<SmallPartitions> = Each thread takes small slices until all work is complete.
				Balances better than Partitioning but with a bit more overhead.
	Question: should stages include information about barriers?  Probably leave that
		up to the container, i.e. System.
*/

// NOTE: TODO: The start and end will be a single system with two stages
// when the stage sort is functional.
class InstanceStartSystem : public GO::System
{
public:
	InstanceStartSystem(ExperimentalD3D12* app, GO::Service* service)
		: System(service)
		, mpApp(app)
		, mpInstances(nullptr)
	{
		GO::Stage* stage = new GO::Stage(service, this, "Instances Begin");
		stage->AddUpdate(this, nullptr, &InstanceStartSystem::Update);
		Add(stage);
	}

	ExperimentalD3D12::Instance* GetInstances() const { return mpInstances; }

private:
	static void Update(System* s, GO::Object*)
	{
		InstanceStartSystem* system = static_cast<InstanceStartSystem*>(s);
		system->mpApp->GetCurrentInstanceBuffer()->Map(reinterpret_cast<void**>(&system->mpInstances));
	}

	ExperimentalD3D12* mpApp;
	ExperimentalD3D12::Instance* mpInstances;
};

class InstanceEndSystem : public GO::System
{
public:
	InstanceEndSystem(ExperimentalD3D12* app, GO::Service* service)
		: System(service)
		, mpApp(app)
	{
		MultiCore::Stage::Dependency dependency(""_crc64, "Instances Begin"_crc64);

		GO::Stage* stage = new GO::Stage(service, this, "Instances End", {dependency});
		stage->AddUpdate(this, nullptr, &InstanceEndSystem::Update);
		Add(stage);
	}

private:
	static void Update(System* s, GO::Object*)
	{
		InstanceEndSystem* system = static_cast<InstanceEndSystem*>(s);
		system->mpApp->GetCurrentInstanceBuffer()->Unmap();
	}

	ExperimentalD3D12* mpApp;
};

class MoverSystem : public GO::System
{
public:
	// Component(s) supplied.
	class MoverComponent;

	// Stages.
	class MoverStage : public GO::Stage
	{
	public:
		MoverStage(GO::Service* serv, System* s, Dependencies&& dependencies) : Stage(serv, s, "Mover", dependencies) {}

		bool ResolveDependencies(GO::Service* service, System* system) override
		{
			MoverSystem* mover = static_cast<MoverSystem*>(system);
			mover->mpTime = service->GetSystem<GO::Timer>("Game Time"_crc64);
			mover->mpInstances = service->GetSystem<InstanceStartSystem>("Start Instancing"_crc64);
			return mover->mpTime != nullptr;
		}
	};

	MoverSystem(ExperimentalD3D12* app, GO::Service* service)
		: System(service)
		, mpApp(app)
		, mpInstances(nullptr)
		, mpTime (nullptr)
	{
		MultiCore::Stage::Dependency timeDep(""_crc64, "Timer"_crc64);
		MultiCore::Stage::Dependency dependency(""_crc64, "Instances Begin"_crc64);

		mpMover = new MoverStage(service, this, {timeDep, dependency});
		Add(mpMover);
	}

	InstanceStartSystem* GetInstanceSystem() const { return mpInstances; }

	MoverStage* GetMoverStage() const { return mpMover; }

private:
	ExperimentalD3D12* mpApp;

	// system interdependencies.
	InstanceStartSystem* mpInstances;
	const GO::Timer* mpTime;	// The clock this mover is attached to.
	MoverStage* mpMover;
};

class MoverSystem::MoverComponent : public GO::Component
{
public:
	//////////////////////////////////////////////////////////////////////////
	static const GO::ComponentID kID = "Mover Component"_crc64;

	//////////////////////////////////////////////////////////////////////////
	MoverComponent(MoverSystem* mover)
		: mpMover(mover)
	{}

	//////////////////////////////////////////////////////////////////////////
	GO::ComponentID GetID() const override { return kID; }

	void Activate() override
	{
		mpMover->GetMoverStage()->AddUpdate(mpMover, GetObject(), &MoverComponent::_Update);
	}

	void Deactivate() override
	{
		mpMover->GetMoverStage()->RemoveUpdate(mpMover, GetObject(), &MoverComponent::_Update);
	}

private:
	static void _Update(System* system, GO::Object* object)
	{
		MoverSystem* mover = static_cast<MoverSystem*>(system);
		const GO::Timer* timer = mover->mpTime;

		int i = int(object->GetID());
		int count = ExperimentalD3D12::kInstancesPerDimension;
		int xc = (i % count);
		int yc = (i / count) % count;
		int zc = (i / (count * count)) % count;

		Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
		float magnitude = Magnitude(pos + Vector3f(0.0f, 50.0f, 0.0f)) * 0.03f;
		magnitude *= magnitude;
		float time = float(Time::Seconds(timer->GetTime()));
		float angle = sinf(0.25f * time);
		pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
		pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
		pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;
		object->GetComponent<GO::TransformComponent>()->GetTransform().SetTranslation(pos);

		ExperimentalD3D12::Instance* instances = mover->GetInstanceSystem()->GetInstances();
		instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
		instances[i].mOrientation0 = Vector3f(1.0f, 0.0f, 0.0f);
		instances[i].mOrientation1 = Vector3f(0.0f, 1.0f, 0.0f);
		instances[i].mOrientation2 = Vector3f(0.0f, 0.0f, 1.0f);
		instances[i].mTranslation = Vector3f(pos.xyz);
	}

	MoverSystem* mpMover;
};


//////////////////////////////////////////////////////////////////////////
#define GFX_INITIALIZER CPF_CONCAT(GFX_ADAPTER, Initializer)
#define INCLUDE_GFX Adapter/## CPF_CONCAT(GFX_ADAPTER, .hpp)
#include CPF_STRINGIZE(INCLUDE_GFX)
#define WINDOW_TITLE "Hello Triangle: " CPF_STRINGIZE(GFX_ADAPTER)


void ExperimentalD3D12::_UpdateStageList()
{
	if (mpStageList)
	{
		for (int i=0; i<mStageListCount; ++i)
		{
			delete[] mpStageList[i];
		}
		delete[] mpStageList;
	}

	mStageListCount = int(mGOService.GetStages().size());
	mpStageList = new char*[mStageListCount];
	int i = 0;
	for (auto& stage : mGOService.GetStages())
	{
		mpStageList[i] = new char[stage->GetName().size() + 1];
		strcpy(mpStageList[i++], stage->GetName().c_str());
	}
}

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

	// Hack: Setup the view all cheezy like.
	mViewportSize = 1.0f;
	mFOV = kDegToRad * 33.0f;
	float halfFov = tan(mFOV / 2.0f);
	mViewportSize = halfFov;
	mAspectRatio = 1.0f;

	//////////////////////////////////////////////////////////////////////////
	mGOService.Install("Game Time"_crc64, new GO::Timer(&mGOService));
	mGOService.Install("Start Instancing"_crc64, new InstanceStartSystem(this, &mGOService));
	mGOService.Install("Mover"_crc64, new MoverSystem(this, &mGOService));
	mGOService.Install("End Instancing"_crc64, new InstanceEndSystem(this, &mGOService));

	for (int i = 0; i<kInstanceCount; ++i)
	{
		IntrusivePtr<GO::Object> object(mGOService.CreateObject());
		object->CreateComponent<GO::TransformComponent>();
		object->CreateComponent<MoverSystem::MoverComponent>(mGOService.GetSystem<MoverSystem>("Mover"_crc64));
	}

	//////////////////////////////////////////////////////////////////////////
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
					mGOService.Activate();
					_UpdateStageList();

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

						// Handle any issued work from the threaded side.
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
						// The threaded execution loop.
						mQueue.FirstOneBarrier(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_BeginFrame), this);
						// Update the GO::Service.
						mGOService.Submit(mQueue);
						// The following build command buffers in parallel.
						mQueue.FirstOne(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_ClearBuffers), this);
						// Draw everything.  This would be an All instruction but right now everything is a single instanced draw call.
						mQueue.FirstOne(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_Draw), this);
						// Single threaded debug GUI rendering.
						mQueue.LastOneBarrier(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_DebugUI), this);
						mQueue.FirstOne(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_PreparePresent), this);
						// Issue the command buffers in proper order.
						// Because the last thread to enter the instruction performs the work and the other threads wait till completion,
						// this guarantee's everything above is complete and no other work is being performed.
						mQueue.LastOneBarrier(SCHEDULED_CALL(ExperimentalD3D12, &ExperimentalD3D12::_EndFrame), this);

						//////////////////////////////////////////////////////////////////////////
						// Notify that the frame of processing is complete.
						mQueue.Submit(frameSemaphore);

						// And tell the scheduler to execute this work queue.
						mQueue.Execute(Scheduler::Queue::SubmissionType::eNormal);
					}

					// Guarantee last frame is complete before we tear everything down.
					frameSemaphore.Acquire();
					mDebugUI.Shutdown();

					mGOService.Deactivate();
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
