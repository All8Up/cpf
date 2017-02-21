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
#include "Math/Matrix33v.hpp"
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

class InstanceSystem : public MultiCore::System
{
public:
	static constexpr int64_t kID = "Instance Manager"_crc64;
	static constexpr int64_t kBeginID = "Instance Begin"_crc64;
	static constexpr int64_t kEndID = ""_crc64;

	InstanceSystem(MultiCore::Pipeline* pipeline, const String& name)
		: System(pipeline, name)
		, mpApp(nullptr)
		, mpInstances(nullptr)
	{
		{
			MultiCore::SingleUpdateStage* stage = MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, "Instance End");
			stage->SetUpdate(&InstanceSystem::_End, this);
			stage->SetDependencies({ { GetID(), kBeginID } });
			AddStage(stage);
		}
	}

	// Need a better way to handle variable initializations.
	void SetRenderSystem(const String& name)
	{
		mRenderID = Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1));
		{
			MultiCore::SingleUpdateStage* stage = MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, "Instance Begin");
			stage->SetUpdate(&InstanceSystem::_Begin, this);
			stage->SetDependencies({ { mRenderID, "Begin Frame"_crc64 } });
			AddStage(stage);
		}
	}
	void SetApplication(ExperimentalD3D12* app) { mpApp = app; }
	ExperimentalD3D12::Instance* GetInstances() const { return mpInstances; }

	static bool Install()
	{
		return System::Install(kID, &InstanceSystem::_Creator);
	}
	static bool Remove()
	{
		return System::Remove(kID);
	}

private:
	static System* _Creator(MultiCore::Pipeline* pipeline, const String& name)
	{
		return new InstanceSystem(pipeline, name);
	}

	static void _Begin(Concurrency::ThreadContext&, void* context)
	{
		InstanceSystem* system = static_cast<InstanceSystem*>(context);
		system->mpApp->GetCurrentInstanceBuffer()->Map(reinterpret_cast<void**>(&system->mpInstances));
	}
	static void _End(Concurrency::ThreadContext&, void* context)
	{
		InstanceSystem* system = static_cast<InstanceSystem*>(context);
		system->mpApp->GetCurrentInstanceBuffer()->Unmap();
	}

	ExperimentalD3D12* mpApp;
	uint64_t mRenderID;
	ExperimentalD3D12::Instance* mpInstances;
};

class MoverSystem : public MultiCore::System
{
public:
	static constexpr int64_t kID = "Mover System"_crc64;

	// Component(s) supplied.
	class MoverComponent;


	MoverSystem(MultiCore::Pipeline* pipeline, const String& name)
		: System(pipeline, name)
		, mpApp(nullptr)
		, mpInstances(nullptr)
		, mpTime (nullptr)
		, mClockID(-1)
		, mInstanceID(-1)
	{
	}

	InstanceSystem* GetInstanceSystem() const { return mpInstances; }
	void SetTimer(const String& name) { mClockID = Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1)); }
	void SetInstancing(const String& name)
	{
		mInstanceID = Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1));
		mpMoverStage = MultiCore::Stage::Create<GO::ObjectStage>(this, "Mover");
		mpMoverStage->SetDependencies({ { mInstanceID, InstanceSystem::kBeginID } });
		AddStage(mpMoverStage);
	}

	bool Configure() override
	{
		mpTime = static_cast<GO::Timer*>(GetOwner()->GetSystem(mClockID));
		mpInstances = static_cast<InstanceSystem*>(GetOwner()->GetSystem(mInstanceID));

		return mpTime && mpInstances;
	}

	static bool Install()
	{
		return System::Install(kID, &MoverSystem::_Creator);
	}
	static bool Remove()
	{
		return System::Remove(kID);
	}

private:
	static System* _Creator(MultiCore::Pipeline* pipeline, const String& name)
	{
		return new MoverSystem(pipeline, name);
	}

	ExperimentalD3D12* mpApp;

	// system interdependencies.
	InstanceSystem* mpInstances;
	const GO::Timer* mpTime;	// The clock this mover is attached to.
	GO::ObjectStage* mpMoverStage;
	GO::SystemID mClockID;
	GO::SystemID mInstanceID;
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
		mpMover->mpMoverStage->AddUpdate(mpMover, GetObject(), &MoverComponent::_Update);
	}

	void Deactivate() override
	{
		mpMover->mpMoverStage->RemoveUpdate(mpMover, GetObject(), &MoverComponent::_Update);
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

		Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time);

		ExperimentalD3D12::Instance* instances = mover->GetInstanceSystem()->GetInstances();
		instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
		instances[i].mOrientation0 = orientation[0].xyz;
		instances[i].mOrientation1 = orientation[1].xyz;
		instances[i].mOrientation2 = orientation[2].xyz;
		instances[i].mTranslation = Vector3f(pos.xyz);
	}

	MoverSystem* mpMover;
};

class RenderSystem : public MultiCore::System
{
public:
	//
	static constexpr int64_t kID = "Render System"_crc64;

	// Registration.
	static bool Install()
	{
		return System::Install(kID, &RenderSystem::Creator);
	}
	static bool Remove()
	{
		return System::Remove(kID);
	}

	void SetApplication(ExperimentalD3D12* app)
	{
		mpApp = app;
	}

private:
	// Construction/Destruction.
	RenderSystem(MultiCore::Pipeline* owner, const String& name)
		: System(owner, name)
		, mpApp(nullptr)
	{
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Begin Frame")));
			ptr->SetUpdate(&RenderSystem::_BeginFrame, this);
			AddStage(ptr);
		}
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Clear Buffers")));
			ptr->SetUpdate(&RenderSystem::_Clear, this);
			ptr->SetDependencies({ {GetID(), "Begin Frame"_crc64} });
			AddStage(ptr);
		}
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Draw Instances")));
			ptr->SetUpdate(&RenderSystem::_Draw, this);
			ptr->SetDependencies({ { GetID(), "Begin Frame"_crc64 } });
			AddStage(ptr);
		}
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Debug UI")));
			ptr->SetUpdate(&RenderSystem::_DebugUI, this, true, false);
			ptr->SetDependencies({
				{ GetID(), "Begin Frame"_crc64 },
				{ GetID(), "Clear Buffers"_crc64 },
				{ GetID(), "Draw Instances"_crc64 }
			});
			AddStage(ptr);
		}
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Prepare Present")));
			ptr->SetUpdate(&RenderSystem::_PreparePresent, this);
			ptr->SetDependencies({
				{ GetID(), "Debug UI"_crc64 }
			});
			AddStage(ptr);
		}
		{
			IntrusivePtr<MultiCore::SingleUpdateStage>
				ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("End Frame")));
			ptr->SetUpdate(&RenderSystem::_EndFrame, this, true, false);
			ptr->SetDependencies({
				{ GetID(), "Clear Buffers"_crc64 },
				{ GetID(), "Prepare Present"_crc64 }
			});
			AddStage(ptr);
		}
	}
	~RenderSystem() override
	{}

	static void _BeginFrame(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_BeginFrame(tc);
	}
	static void _Clear(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_ClearBuffers(tc);
	}
	static void _Draw(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_Draw(tc);
	}
	static void _DebugUI(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_DebugUI(tc);
	}
	static void _PreparePresent(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_PreparePresent(tc);
	}
	static void _EndFrame(ThreadContext& tc, void* context)
	{
		RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
		self->mpApp->_EndFrame(tc);
	}

	//
	static System* Creator(MultiCore::Pipeline* owner, const String& name)
	{
		return new RenderSystem(owner, name);
	}

	ExperimentalD3D12* mpApp;
};


//////////////////////////////////////////////////////////////////////////
#define GFX_INITIALIZER CPF_CONCAT(GFX_ADAPTER, Initializer)
#define INCLUDE_GFX Adapter/## CPF_CONCAT(GFX_ADAPTER, .hpp)
#include CPF_STRINGIZE(INCLUDE_GFX)
#define WINDOW_TITLE "Hello Triangle: " CPF_STRINGIZE(GFX_ADAPTER)


void ExperimentalD3D12::_UpdateStageList()
{
	{
		if (mpStageList)
		{
			for (int i = 0; i < mStageListCount; ++i)
			{
				delete[] mpStageList[i];
			}
			delete[] mpStageList;
		}

		mStageListCount = int(mpMultiCore->GetStages().size());
		mpStageList = new char*[mStageListCount];
		int i = 0;
		for (auto& stage : mpMultiCore->GetStages())
		{
			if (stage)
			{
				mpStageList[i] = new char[stage->GetName().size() + 1];
				strcpy(mpStageList[i++], stage->GetName().c_str());
			}
			else
			{
				static const String barrier("-- barrier --");
				mpStageList[i] = new char[barrier.size() + 1];
				strcpy(mpStageList[i++], barrier.c_str());
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	{
		if (mpInstructionList)
		{
			for (int i = 0; i < mInstructionCount; ++i)
			{
				delete[] mpInstructionList[i];
			}
			delete[] mpInstructionList;
		}

		auto instructions = mQueue.Dissassemble();
		mInstructionCount = int(instructions.size());

		mpInstructionList = new char*[mInstructionCount];
		int i = 0;
		for (auto& instruction : instructions)
		{
			String description = mQueue.GetOpName(instruction.mOp);
			description += " : " + std::to_string(intptr_t(instruction.mpPayload)) + " : " + std::to_string(intptr_t(instruction.mpContext));
			mpInstructionList[i] = new char[description.size() + 1];
			strcpy(mpInstructionList[i++], description.c_str());
		}
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
	MultiCore::Pipeline::Create(mpMultiCore.AsTypePP());

	// Install the stage types.
	GO::ObjectStage::Install();
	MultiCore::SingleUpdateStage::Install();

	// Install the systems this will use.
	RenderSystem::Install();
	GO::Timer::Install();
	InstanceSystem::Install();
	MoverSystem::Install();

	// TODO: Setting dependencies currently sucks..
	// Create the systems.
	{
		IntrusivePtr<RenderSystem> renderSystem(MultiCore::System::Create<RenderSystem>(mpMultiCore, "Render System"));
		renderSystem->SetApplication(this);
		mpMultiCore->Install(renderSystem);
	}
	{
		IntrusivePtr<GO::Timer> timer(MultiCore::System::Create<GO::Timer>(mpMultiCore, "Game Time"));
		mpMultiCore->Install(timer);
	}
	{
		IntrusivePtr<InstanceSystem> instanceSystem(MultiCore::System::Create<InstanceSystem>(mpMultiCore, "Instance System"));
		instanceSystem->SetRenderSystem("Render System");
		instanceSystem->SetApplication(this);
		mpMultiCore->Install(instanceSystem);
	}
	{
		IntrusivePtr<MoverSystem> moverSystem(MultiCore::System::Create<MoverSystem>(mpMultiCore, "Mover"));
		moverSystem->SetTimer("Game Time");
		moverSystem->SetInstancing("Instance System");
		mpMultiCore->Install(moverSystem);
	}
	mpMultiCore->Configure();

	for (int i = 0; i<kInstanceCount; ++i)
	{
		IntrusivePtr<GO::Object> object(mGOService.CreateObject());
		object->CreateComponent<GO::TransformComponent>();
		object->CreateComponent<MoverSystem::MoverComponent>(mpMultiCore->GetSystem<MoverSystem>("Mover"));
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
