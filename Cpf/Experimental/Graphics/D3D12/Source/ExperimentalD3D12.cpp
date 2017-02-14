//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"

#include "Adapter/WindowedApp.hpp"
#include "Logging/Logging.hpp"

#include "IntrusivePtr.hpp"
#include "Resources/ResourceConfig.hpp"
#include "Threading/Threading.hpp"
#include "Time/Time.hpp"

#include "Graphics/Driver.hpp"
#include "Graphics/Descriptors/PipelineStateDesc.hpp"

#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix33v.hpp"
#include "Math/Matrix44v.hpp"

#include "Concurrency/Scheduler.hpp"
#include "Math/Constants.hpp"
#include <math.h>
#include "IO/IO.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;
using namespace Threading;
using namespace Concurrency;

#define GFX_INITIALIZER CPF_CONCAT(GFX_ADAPTER, Initializer)
#define INCLUDE_GFX Adapter/## CPF_CONCAT(GFX_ADAPTER, .hpp)
#include CPF_STRINGIZE(INCLUDE_GFX)
#define WINDOW_TITLE "Hello Triangle: " CPF_STRINGIZE(GFX_ADAPTER)


void ExperimentalD3D12::_ObjectUpdate(ThreadContext& tc)
{
	// Quick do nothing version.
	int32_t threadIndex = tc.ThreadId();
	int32_t threadCount = tc.ThreadCount();
	int32_t partitionSize = kInstanceCount / threadCount;
	int32_t start = threadIndex * partitionSize;
	int32_t end = start + partitionSize;

	if (threadIndex == threadCount - 1)
	{
		int32_t rollover = kInstanceCount - (threadCount * partitionSize);
		end += rollover;
	}

	Instance* instances = nullptr;
	if (mpInstanceBuffer[mCurrentBackbuffer]->Map(0, 0, reinterpret_cast<void**>(&instances)))
	{
		for (int i = start; i < end; ++i)
		{
			int count = kInstancesPerDimension;
			int xc = (i % count);
			int yc = (i / count) % count;
			int zc = (i / (count * count)) % count;
			instances[i].mTranslation = Vector3f((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
			instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
			instances[i].mOrientation0 = Vector3f(1.0f, 0.0f, 0.0f);
			instances[i].mOrientation1 = Vector3f(0.0f, 1.0f, 0.0f);
			instances[i].mOrientation2 = Vector3f(0.0f, 0.0f, 1.0f);

			float magnitude = Magnitude(instances[i].mTranslation + Vector3f(0.0f, 50.0f, 0.0f)) * 0.03f;
			magnitude *= magnitude;
			float time = float(Time::Seconds(mCurrentTime));
			float angle = sinf(0.25f * time);
			instances[i].mTranslation.x = sinf(angle * magnitude) * instances[i].mTranslation.x - cosf(angle * magnitude) * instances[i].mTranslation.z;
			instances[i].mTranslation.y = (sinf(angle) + 0.5f) * instances[i].mTranslation.y * magnitude;
			instances[i].mTranslation.z = cosf(angle * magnitude) * instances[i].mTranslation.x + sinf(angle * magnitude) * instances[i].mTranslation.z;
		}
	}
	mpInstanceBuffer[mCurrentBackbuffer]->Unmap();
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
					SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_CreateWorkerData),
					SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_DestroyWorkerData),
					this
				);
				mQueue = Move(mScheduler.CreateQueue());

				//////////////////////////////////////////////////////////////////////////
				mStartTime = Time::Now();
				mCurrentTime = Time::Now() - mStartTime;
				Time::Value pollingTime = Time::Seconds(0);
				Time::Value renderingTime = Time::Seconds(0);

				// Currently only a single frame.  Will Eventually match the number of back buffers and other resources.
				Scheduler::Semaphore frameSemaphore(1);
				// Create a graphics fence to track back buffers.
				mpDevice->CreateFence(0, mpFence.AsTypePP());

				while (IsRunning())
				{
					pollingTime += Time::Now() - mCurrentTime;

					//////////////////////////////////////////////////////////////////////////
					// Wait for the last frame of processing.
					frameSemaphore.Acquire();
					renderingTime += Time::Now() - mCurrentTime;

					// Poll the application OS events.
					// TODO: this is done in between frames so resize doesn't conflict.
					// This will need to be overlap aware and that means that resize will need the ability
					// to flush the pipeline.
					Poll();

					Atomic::Inc(mFrameIndex);
					Atomic::Store(mSubmissionIndex, Atomic::Load(mFrameIndex) * 3);
					Atomic::Store(mCurrentScheduledBuffer, 1);
					Atomic::Store(mCurrentBackbuffer, mpSwapChain->GetCurrentIndex());
					auto now = Time::Now() - mStartTime;
					mDeltaTime = now - mCurrentTime;
					mCurrentTime = now;

					static int count = 0;
					static Time::Value accumulation;
					accumulation += mDeltaTime;
					if (++count % 1000 == 0)
					{
						float avg = float(Time::Seconds(accumulation / 1000));
						CPF_LOG(Experimental, Info) << "Avg: " << avg << " FPS avg: " << 1.0f / avg;
						CPF_LOG(Experimental, Info) << " Poll: "
							<< float(Time::Seconds(pollingTime)) / float(Time::Seconds(accumulation)) << " - "
							<< float(Time::Seconds(renderingTime)) / float(Time::Seconds(accumulation));
						accumulation = Time::Seconds(0);
						pollingTime = Time::Seconds(0);
						renderingTime = Time::Seconds(0);
					}

					//////////////////////////////////////////////////////////////////////////
					// The threaded execution loop.
					mQueue.FirstOneBarrier(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_BeginFrame), this);
					// Update the instance buffer.
					mQueue.AllBarrier(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_ObjectUpdate), this);
					// The following build command buffers in parallel.
					mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_ClearBuffers), this);
					// Draw everything.  This would be an All instruction but right now everything is a single instanced draw call.
					mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_Draw), this);
					mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_PreparePresent), this);
					// Issue the command buffers in proper order.
					// Because the last thread to enter the instruction performs the work and the other threads wait till completion,
					// this guarantee's everything above is complete and no other works is being performed.
					mQueue.LastOneBarrier(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_EndFrame), this);

					//////////////////////////////////////////////////////////////////////////
					// Notify that the frame of processing is complete.  TODO: Should find a better name for this or the next call.
					mQueue.Submit(frameSemaphore);

					// And submit all the work to the thread system for processing.
					mQueue.Submit(Scheduler::Queue::SubmissionType::eNormal);
				}

				// Guarantee last frame is complete.
				frameSemaphore.Acquire();

				// Destroy all the resources.
				_DestroyResources();
			}
			gfxInstance.Assign(nullptr);
		}
	}
	return 0;
}

CPF_CREATE_APPLICATION(Cpf::ExperimentalD3D12);
