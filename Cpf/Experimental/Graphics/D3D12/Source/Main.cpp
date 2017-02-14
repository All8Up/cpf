//////////////////////////////////////////////////////////////////////////
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

namespace Cpf
{
	class ExperimentalD3D12 : public Adapter::WindowedApp
	{
	public:
		ExperimentalD3D12()
			: mScheduler(this)
			, mFenceTarget(1)
		{}

		static const int32_t mBackBufferCount = 3;

		IntrusivePtr<iWindow> mpWindow;
		IntrusivePtr<iDevice> mpDevice;
		IntrusivePtr<iSwapChain> mpSwapChain;
		Vector<IntrusivePtr<iImage>> mpDepthBufferImages;
		Vector<IntrusivePtr<iImageView>> mpDepthBufferImageViews;
		IntrusivePtr<iResourceBinding> mpResourceBinding;
		IntrusivePtr<iConstantBuffer> mpModelTransform;
		IntrusivePtr<iConstantBuffer> mpViewProj;

		IntrusivePtr<iVertexBuffer> mpVertexBuffer;
		IntrusivePtr<iVertexBuffer> mpInstanceBuffer[mBackBufferCount];
		IntrusivePtr<iIndexBuffer> mpIndexBuffer;

		IntrusivePtr<iCommandPool> mpPreCommandPool[mBackBufferCount];
		IntrusivePtr<iCommandBuffer> mpPreCommandBuffer[mBackBufferCount];
		IntrusivePtr<iCommandPool> mpPostCommandPool[mBackBufferCount];
		IntrusivePtr<iCommandBuffer> mpPostCommandBuffer[mBackBufferCount];
		IntrusivePtr<iPipeline> mpPipeline;
		IntrusivePtr<iFence> mpFence;
		Scheduler mScheduler;
		Scheduler::Queue mQueue;

		int32_t mCurrentScheduledBuffer = 0;
		iCommandBuffer* mpScheduledBuffers[Scheduler::kMaxThreads * 4];

		int32_t mCurrentBackbuffer = 0;
		uint64_t mFenceTarget = 1;
		uint64_t mFrameIndex = 0;
		uint64_t mSubmissionIndex = 0;

		Time::Value mStartTime;
		Time::Value mCurrentTime;
		Time::Value mDeltaTime;

		float mFOV;
		float mViewportSize;
		float mAspectRatio;

		// Per thread data.
		struct ThreadData
		{
			IntrusivePtr<iCommandPool> mpCommandPool[mBackBufferCount];
			IntrusivePtr<iCommandBuffer> mpCommandBuffer[mBackBufferCount];
		};
		ThreadData mWorkerData[Scheduler::kMaxThreads];

		struct ModelTransform
		{
			Matrix33fv mOrientation;
			Vector3fv mScale;
			Vector3fv mTranslation;
		};
		struct Instance
		{
			Vector3f mTranslation;
			Vector3f mScale;
			Vector3f mOrientation0;
			Vector3f mOrientation1;
			Vector3f mOrientation2;
		};

		void _InitThreadsForRendering(ThreadContext& tc)
		{
			ThreadData& td = mWorkerData[tc.ThreadId()];
			tc.UserData(&td);

			for (int i = 0; i < mBackBufferCount; ++i)
			{
				mpDevice->CreateCommandPool(td.mpCommandPool[i].AsTypePP());
				mpDevice->CreateCommandBuffer(td.mpCommandPool[i], td.mpCommandBuffer[i].AsTypePP());
			}
		}

		void _ShutdownThreadsForRendering(ThreadContext& tc)
		{
			ThreadData& td = mWorkerData[tc.ThreadId()];

			for (int i = 0; i < mBackBufferCount; ++i)
			{
				td.mpCommandBuffer[i].Assign(nullptr);
				td.mpCommandPool[i].Assign(nullptr);
			}
		}

		void _BeginFrame(ThreadContext&)
		{
			// Issue on the shared command buffers.
			mpPreCommandPool[mCurrentBackbuffer]->Reset();
			mpPreCommandBuffer[mCurrentBackbuffer]->Reset(mpPreCommandPool[mCurrentBackbuffer]);
			mpPreCommandBuffer[mCurrentBackbuffer]->Begin();

			// TODO: This will move into the render pass abstraction when it is ready.
			mpDevice->BeginFrame(mpPreCommandBuffer[mCurrentBackbuffer]);

			// Update the scene data.
			ModelTransform tempModelData =
			{
				Transpose(Matrix33fv::Identity()),
				Vector3fv(1.0f, 1.0f, 1.0f),
				Vector3fv(0.0f, 0.0f, 100.0f)
			};
			mpModelTransform->Update(0, sizeof(ModelTransform), &tempModelData);
		}

		void _ClearBuffers(ThreadContext&)
		{
			// Setup the frame.
			int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);

			// Transition the current back buffer and depth buffers to render targets.
			// TODO: This will go away with the render pass abstraction.
			mpPreCommandBuffer[mCurrentBackbuffer]->ImageTransition(
				mpSwapChain->GetImage(backBuffer),
				ResourceState::ePresent,
				ResourceState::eRenderTarget,
				SubResource::eAll);
			mpPreCommandBuffer[mCurrentBackbuffer]->ImageTransition(
				mpDepthBufferImages[backBuffer],
				ResourceState::ePresent,
				ResourceState::eDepthWrite,
				SubResource::eAll
			);

			// Cycle the colors to make sure things are working.
			Color4f color(0.0f, 0.0f, 0.0f, 1.0f);

			// Clear the color and depth buffers.
			iImageView* imageViews[] = { mpSwapChain->GetImageView(mCurrentBackbuffer) };
			mpPreCommandBuffer[mCurrentBackbuffer]->SetRenderTargets(1, imageViews, mpDepthBufferImageViews[backBuffer]);
			mpPreCommandBuffer[mCurrentBackbuffer]->ClearRenderTargetView(mpSwapChain->GetImageView(backBuffer), color, 0, nullptr);
			mpPreCommandBuffer[mCurrentBackbuffer]->ClearDepthStencilView(mpDepthBufferImageViews[backBuffer], DepthStencilClearFlag::eDepth, 1.0f, 0, 0, nullptr);

			// End the command buffer prior to submission.
			mpPreCommandBuffer[mCurrentBackbuffer]->End();

			// Always the first to issue.
			mpScheduledBuffers[0] = mpPreCommandBuffer[mCurrentBackbuffer];
		}

		static const int32_t kInstancesPerDimension = 50;
		static const int32_t kInstanceCount = kInstancesPerDimension*kInstancesPerDimension*kInstancesPerDimension;

		void _ObjectUpdate(ThreadContext& tc)
		{
			// Quick do nothing version.
			int32_t threadIndex = tc.ThreadId();
			int32_t threadCount = tc.ThreadCount();
			int32_t partitionSize = kInstanceCount / threadCount;
			int32_t start = threadIndex * partitionSize;
			int32_t end = start + partitionSize;

			if (threadIndex==threadCount-1)
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

		void _Draw(ThreadContext& tc)
		{
			ThreadData& threadData = *reinterpret_cast<ThreadData*>(tc.UserData());

			// Start issuing commands.
			threadData.mpCommandPool[mCurrentBackbuffer]->Reset();
			threadData.mpCommandBuffer[mCurrentBackbuffer]->Reset(threadData.mpCommandPool[mCurrentBackbuffer]);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->Begin();

			//////////////////////////////////////////////////////////////////////////
			/* Do some drawing...
			*/
			int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);
			iImageView* imageViews[] = { mpSwapChain->GetImageView(backBuffer) };
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetRenderTargets(1, imageViews, mpDepthBufferImageViews[backBuffer]);

			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetResourceBinding(mpResourceBinding);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetPipeline(mpPipeline);

			Viewport viewport{
				0.0f, 0.0f,
				float(mpWindow->GetClientArea().x), float(mpWindow->GetClientArea().y),
				0.0f, 1.0f
			};
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetViewports(1, &viewport);
			Rectanglei scissor(0, mpWindow->GetClientArea().x, 0, mpWindow->GetClientArea().y);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetScissorRects(1, &scissor);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetTopology(PrimitiveTopology::eTriangleList);

			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetConstantBuffer(0, mpViewProj);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetConstantBuffer(1, mpModelTransform);
			iVertexBuffer* vbs[2] = {mpVertexBuffer, mpInstanceBuffer[mCurrentBackbuffer] };
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetVertexBuffers(0, 2, vbs);
			threadData.mpCommandBuffer[mCurrentBackbuffer]->SetIndexBuffer(mpIndexBuffer);

			threadData.mpCommandBuffer[mCurrentBackbuffer]->DrawIndexedInstanced(3, kInstanceCount, 0, 0, 0);

			// End the command buffer prior to submission.
			threadData.mpCommandBuffer[mCurrentBackbuffer]->End();
			mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpCommandBuffer[mCurrentBackbuffer];
		}

		void _PreparePresent(ThreadContext&)
		{
			// This is not split out to be parallel with the above as it must always be the last submitted buffer.
			// Issue on the shared command buffers.
			mpPostCommandPool[mCurrentBackbuffer]->Reset();
			mpPostCommandBuffer[mCurrentBackbuffer]->Reset(mpPostCommandPool[mCurrentBackbuffer]);
			mpPostCommandBuffer[mCurrentBackbuffer]->Begin();

			// Transition the back buffer and depth buffer to present.
			int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);
			mpPostCommandBuffer[mCurrentBackbuffer]->ImageTransition(mpSwapChain->GetImage(backBuffer), ResourceState::eRenderTarget, ResourceState::ePresent, SubResource::eAll);
			mpPostCommandBuffer[mCurrentBackbuffer]->ImageTransition(mpDepthBufferImages[backBuffer], ResourceState::eDepthWrite, ResourceState::ePresent, SubResource::eAll);

			// Let the device take care of any final needed work, read backs for instance.
			mpDevice->EndFrame(mpPostCommandBuffer[mCurrentBackbuffer]);

			// End the command buffer prior to submission.
			mpPostCommandBuffer[mCurrentBackbuffer]->End();
		}

		void _EndFrame(ThreadContext&)
		{
			// Pick up and add the transition for present.
			int32_t commandBufferCount = Atomic::Inc(mCurrentScheduledBuffer);
			mpScheduledBuffers[commandBufferCount - 1] = mpPostCommandBuffer[mCurrentBackbuffer];

			// Submit the command buffers.
			mpDevice->Submit(commandBufferCount, mpScheduledBuffers);

			// Present the back buffer.
			mpSwapChain->Present();

			// Wait for completion.
			auto fenceToWaitFor = Atomic::Inc(mFenceTarget);
			mpDevice->Signal(mpFence, fenceToWaitFor);

			// TODO: This sure seems like a race condition but it is how all the examples seem to work.
			if (mpFence->GetValue() < fenceToWaitFor)
				mpFence->WaitFor(fenceToWaitFor);

			// TODO: Move into the render passes.
			mpDevice->Finalize();
		}

		void _Resize(int32_t x, int32_t y)
		{
			if (mpSwapChain)
			{
				mFOV = kDegToRad * 33.0f;
				float halfFov = tan(mFOV / 2.0f);
				mViewportSize = halfFov;

				mpSwapChain->Resize(x, y);

				// Recreate the depth buffers.
				mpDepthBufferImages.clear();
				mpDepthBufferImageViews.clear();
				mpDepthBufferImages.resize(mBackBufferCount);
				mpDepthBufferImageViews.resize(mBackBufferCount);
				ImageDesc depthBufferDesc
				{
					x, y,
					1,
					1,
					Format::eD32f,
					{ 1, 0 },
					ImageFlags::eAllowDepthStencil
				};
				for (int i = 0; i < mBackBufferCount; ++i)
				{
					mpDevice->CreateImage2D(&depthBufferDesc, mpDepthBufferImages[i].AsTypePP());
					mpDevice->CreateDepthStencilView(mpDepthBufferImages[i], nullptr, mpDepthBufferImageViews[i].AsTypePP());
				}
			}
		}

		int Start(const CommandLine&) override
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

			mViewportSize = 1.0f;
			mFOV = kDegToRad * 33.0f;
			float halfFov = tan(mFOV / 2.0f);
			mViewportSize = halfFov;
			mAspectRatio = 1.0f;

			// Create the virtual file system locator.
			IntrusivePtr<Resources::Locator> resourceLocator(Resources::Configuration("./Experimental/resource_config.json").GetLocator());
			if (!resourceLocator)
			{
				// Do something with configuration error.
			}

			{
				//////////////////////////////////////////////////////////////////////////
				// Create the window.
				On<OnQuit>([]() {
					CPF_LOG(Experimental, Info) << "**** Quit requested.";
					return true;
				});

				// Create the window.
				Math::Vector2i mWindowSize(1920, 1080);
				mpWindow.Adopt(
					WindowDesc(this)
					.Title(WINDOW_TITLE)
					.Position(iWindow::Centered)
					.Size(mWindowSize)
					.Flags(iWindow::eResizable | iWindow::eShown)
				);

				mpWindow->GetEmitter().On<iWindow::OnResized>(Bind(&ExperimentalD3D12::_Resize, this, Placeholders::_1, Placeholders::_2));

				//////////////////////////////////////////////////////////////////////////
				// Get an instance of the installed device from the graphics factory.
				{
					IntrusivePtr<iInstance> gfxInstance;
					Graphics::Create(1, gfxInstance.AsTypePP());
					if (gfxInstance)
					{
						{
							//////////////////////////////////////////////////////////////////////////
							// Enumerate the graphics adapters attached to the system.
							int adapterCount = 0;
							gfxInstance->EnumerateAdapters(adapterCount, nullptr);
							Vector<IntrusivePtr<iAdapter>> adapters;
							adapters.resize(adapterCount);
							gfxInstance->EnumerateAdapters(adapterCount, adapters[0].AsTypePP());

							//////////////////////////////////////////////////////////////////////////
							// Log adapter information.
							for (const auto adapter : adapters)
							{
								CPF_LOG(Experimental, Info) << "Adapter       : " << adapter->GetDescription();
								CPF_LOG(Experimental, Info) << " Is Software  : " << (adapter->IsSoftware() ? "true" : "false");
								CPF_LOG(Experimental, Info) << " Is Remote    : " << (adapter->IsRemote() ? "true" : "false");
								CPF_LOG(Experimental, Info) << " Video Memory : " << adapter->GetVideoMemory() / (1024 * 1024 * 1024) << " GB";
								CPF_LOG(Experimental, Info) << " System Memory: " << adapter->GetSystemMemory() / (1024 * 1024 * 1024) << " GB";
								CPF_LOG(Experimental, Info) << " Shared Memory: " << adapter->GetSharedMemory() / (1024 * 1024 * 1024) << " GB";
							}

							//////////////////////////////////////////////////////////////////////////
							// Choose the best adapter.  (Just find the first non software adapter at the moment.)
							int bestAdapter = -1;
							for (int i = 0; i < adapterCount; ++i)
							{
								if (adapters[i]->IsSoftware() || adapters[i]->IsRemote())
									continue;
								bestAdapter = i;
								break;
							}
							CPF_LOG(Experimental, Info) << "Chosen Adapter: " << adapters[bestAdapter]->GetDescription();

							//////////////////////////////////////////////////////////////////////////
							// Enumerate the outputs attached to the adapter.
							int32_t outputCount = 0;
							adapters[bestAdapter]->EnumerateOutputs(outputCount, nullptr);

							Vector<IntrusivePtr<iOutput>> outputs;
							outputs.resize(outputCount);
							adapters[bestAdapter]->EnumerateOutputs(outputCount, outputs[0].AsTypePP());

							//////////////////////////////////////////////////////////////////////////
							// Log the output desktop information, if any.
							for (auto& output : outputs)
							{
								OutputDesc outputDesc;
								if (output->GetDesc(&outputDesc))
								{
									CPF_LOG(Experimental, Info) << "Output      : " << outputDesc.mName;
									CPF_LOG(Experimental, Info) << " Attached   : " << (outputDesc.mAttachedToDesktop ? "true" : "false");
									if (outputDesc.mAttachedToDesktop)
									{
										CPF_LOG(Experimental, Info) << " Coordinates: "
											<< outputDesc.mDesktopCoordinates.Left() << ", " << outputDesc.mDesktopCoordinates.Top() << " - "
											<< outputDesc.mDesktopCoordinates.Right() << ", " << outputDesc.mDesktopCoordinates.Bottom();
										CPF_LOG(Experimental, Info) << " Rotation   : " <<
											(outputDesc.mRotation == ModeRotation::eIdentity ? "Identity" : "Other");
									}

									//////////////////////////////////////////////////////////////////////////
									// Enumerate modes for this output.
									int32_t modeCount = 0;
									output->EnumerateModes(Format::eRGBA8un, 0, modeCount, nullptr);
									Vector<ModeDesc> modeDescs;
									modeDescs.resize(modeCount);
									output->EnumerateModes(Format::eRGBA8un, 0, modeCount, modeDescs.data());

									CPF_LOG(Experimental, Info) << "----------------------------------------";
									for (int i = 0; i < modeCount; ++i)
									{
										CPF_LOG(Experimental, Info) << modeDescs[i].mWidth << "x" << modeDescs[i].mHeight << "@" << float(modeDescs[i].mRefreshRate);
									}
									CPF_LOG(Experimental, Info) << "----------------------------------------";
								}
							}

							//////////////////////////////////////////////////////////////////////////
							// Create a device on the desired adapter.
							gfxInstance->CreateDevice(adapters[bestAdapter], mpDevice.AsTypePP());
						}


						//////////////////////////////////////////////////////////////////////////
						// Create the swapchain attached to the window.
						SwapChainDesc desc{
							Format::eRGBA8un,
							SwapEffect::eFlipDiscard,
							{1, 0},
							mBackBufferCount,
							true
						};
						mpDevice->CreateSwapChain(gfxInstance, mpWindow, &desc, mpSwapChain.AsTypePP());

						// Create a set of depth buffers to go with the swap chain.
						mpDepthBufferImages.resize(desc.mBackBufferCount);
						mpDepthBufferImageViews.resize(desc.mBackBufferCount);
						ImageDesc depthBufferDesc
						{
							mpWindow->GetClientArea().x, mpWindow->GetClientArea().y,
							1,
							1,
							Format::eD32f,
							{1, 0},
							ImageFlags::eAllowDepthStencil
						};
						for (int i = 0; i < desc.mBackBufferCount; ++i)
						{
							mpDevice->CreateImage2D(&depthBufferDesc, mpDepthBufferImages[i].AsTypePP());
							mpDevice->CreateDepthStencilView(mpDepthBufferImages[i], nullptr, mpDepthBufferImageViews[i].AsTypePP());
						}

						//////////////////////////////////////////////////////////////////////////
						// Create pools and buffers for commands.
						for (int i = 0; i < mBackBufferCount; ++i)
						{
							mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP());
							mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP());
							mpDevice->CreateCommandBuffer(mpPreCommandPool[i], mpPreCommandBuffer[i].AsTypePP());
							mpDevice->CreateCommandBuffer(mpPostCommandPool[i], mpPostCommandBuffer[i].AsTypePP());
						}

						// Create a fence.
						mpDevice->CreateFence(0, mpFence.AsTypePP());

						// Create shaders.
						IntrusivePtr<iShader> vertexShader;
						IntrusivePtr<iShader> pixelShader;
						{
							IO::Stream* vertexShaderHlsl = resourceLocator->Open(RESOURCE_ID("shaders/", "basic_vs.hlsl"));
							IO::Stream* pixelShaderHlsl = resourceLocator->Open(RESOURCE_ID("shaders/", "basic_ps.hlsl"));
							IntrusivePtr<BinaryBlob> vertexShaderByteCode;
							{
								auto vertexShaderSrc = ReadText(vertexShaderHlsl);
								mpDevice->CompileToByteCode("main", ShaderType::eVertex, vertexShaderSrc.size(), vertexShaderSrc.data(), vertexShaderByteCode.AsTypePP());
							}
							mpDevice->CreateShader(vertexShaderByteCode, vertexShader.AsTypePP());

							IntrusivePtr<BinaryBlob> pixelShaderByteCode;
							{
								auto pixelShaderSrc = ReadText(pixelShaderHlsl);
								mpDevice->CompileToByteCode("main", ShaderType::ePixel, pixelShaderSrc.size(), pixelShaderSrc.data(), pixelShaderByteCode.AsTypePP());
							}
							mpDevice->CreateShader(pixelShaderByteCode, pixelShader.AsTypePP());
						}

						//////////////////////////////////////////////////////////////////////////
						// Create pipeline.
						PipelineStateDesc pipelineDesc = PipelineStateDesc::Build()
							.VertexShader(vertexShader)
							.PixelShader(pixelShader)
							.Topology(TopologyType::eTriangle)

							.Rasterizer(RasterizerStateDesc::Build()
								.CullMode(CullMode::eNone)
								.WindingOrder(WindingOrder::eClockwise)
								.DepthClipping(false)
							)
							.DepthStencil(DepthStencilStateDesc::Build()
								.DepthTest(true)
								.DepthWriteMask(DepthWriteMask::eAll)
							)
							.InputLayout({
								ElementDesc("POSITION", Format::eRGB32f),
								ElementDesc("COLOR", Format::eRGBA32f),
								ElementDesc("TRANSLATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
								ElementDesc("SCALE", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
								ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
								ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
								ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1)
							})
							.RenderTargets({ Format::eRGBA8un })
							.DepthStencilFormat(Format::eD32f)
							;

						//////////////////////////////////////////////////////////////////////////
						ResourceBindingDesc bindingState({
							ParamConstantBuffer(0, ParamVisibility::eVertex),
							ParamConstantBuffer(1, ParamVisibility::eVertex)
						});
						mpDevice->CreateResourceBinding(&bindingState, mpResourceBinding.AsTypePP());
						mpDevice->CreatePipeline(&pipelineDesc, mpResourceBinding, mpPipeline.AsTypePP());

						//////////////////////////////////////////////////////////////////////////
						struct PosColor
						{
							Vector3f mPosition;
							Vector4f mColor;
						};

						// Create the test data.
						const float triSize = 1.0f;
						PosColor vbData[] =
						{
							{{+0.0f, +triSize, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
							{{+triSize, -triSize, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
							{{-triSize, -triSize, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
						};
						uint32_t ibData[] =
						{
							0, 1, 2
						};

						// Create a vertex buffer.
						mpDevice->CreateVertexBuffer(BufferUsage::eImmutable, sizeof(vbData), sizeof(PosColor), vbData, mpVertexBuffer.AsTypePP());
						for (int i=0; i<mBackBufferCount; ++i)
							mpDevice->CreateVertexBuffer(BufferUsage::eDynamic, sizeof(Instance) * kInstanceCount, sizeof(Instance), nullptr, mpInstanceBuffer[i].AsTypePP());

						// Create an index buffer.
						mpDevice->CreateIndexBuffer(Format::eR32u, BufferUsage::eDefault, sizeof(ibData), ibData, mpIndexBuffer.AsTypePP());

						// Create a the view projection constant buffer.
						struct CameraProj
						{
							Matrix44fv mView;
							Matrix44fv mInvView;
							Matrix44fv mProjection;
							float mNear;
							float mFar;
						} initCameraData
						{
							Transpose(Matrix44fv::LookAt(Vector3fv(0.0f, 180.0f, 400.0f), Vector3fv(0.0f), Vector3fv(0.0f, 1.0f, 0.0f))),
							Matrix44fv::Identity(),
							Transpose(Matrix44fv::PerspectiveLH(
								2.0f * mViewportSize * mAspectRatio,
								2.0f * mViewportSize,
								1.0f, 1000.0f,
								0.0f, 1.0f
							)),
							1.0f, 1000.0f
						};
						mpDevice->CreateConstantBuffer(sizeof(CameraProj), &initCameraData, mpViewProj.AsTypePP());

						// Create a model matrix.
						ModelTransform initModelTransform
						{
							Transpose(Matrix33fv::RotateY(kDegToRad * 45.0f)),
							Vector3fv(1.0f, 1.0f, 1.0f),
							Vector3fv(0.0f, 0.0f, 0.0f)
						};
						mpDevice->CreateConstantBuffer(sizeof(ModelTransform), &initModelTransform, mpModelTransform.AsTypePP());

						//////////////////////////////////////////////////////////////////////////
						// Start up the threading system.
						// Allocates a command pool and buffer per thread.
						Thread::Group workerThreads(Thread::GetHardwareThreadCount());
						mScheduler.Initialize(Move(workerThreads),
							SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_InitThreadsForRendering),
							SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_ShutdownThreadsForRendering),
							this
							);
						mQueue = Move(mScheduler.CreateQueue());
						mQueue.Barrier();

						//////////////////////////////////////////////////////////////////////////
						mStartTime = Time::Now();
						mCurrentTime = Time::Now() - mStartTime;
						Time::Value pollingTime = Time::Seconds(0);
						Time::Value renderingTime = Time::Seconds(0);

						// Currently only a single frame.  Will Eventually match the number of back buffers and other resources.
						Scheduler::Semaphore frameSemaphore(1);
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
							// The following build command buffers in parallel.  Eventually _Draw will be called with All when there are a lot of objects to process.
							mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_ClearBuffers), this);
							mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_Draw), this);
							mQueue.FirstOne(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_PreparePresent), this);
							// Issue the command buffers in proper order.
							mQueue.LastOneBarrier(SCHEDULEDCALL(ExperimentalD3D12, &ExperimentalD3D12::_EndFrame), this);

							//////////////////////////////////////////////////////////////////////////
							// Notify that the frame of processing is complete.  TODO: Should find a better name for this or the next call.
							mQueue.Submit(frameSemaphore);

							// And submit all the work to the thread system for processing.
							mQueue.Submit(Scheduler::Queue::SubmissionType::eNormal);
						}

						// Guarantee last frame is complete.
						frameSemaphore.Acquire();

						// Guarantee shutdown order.
						vertexShader.Assign(nullptr);
						pixelShader.Assign(nullptr);
						mpVertexBuffer.Assign(nullptr);
						for (int i = 0; i < mBackBufferCount; ++i)
						{
							mpInstanceBuffer[i].Assign(nullptr);
							mpPreCommandBuffer[i].Assign(nullptr);
							mpPreCommandPool[i].Assign(nullptr);
							mpPostCommandBuffer[i].Assign(nullptr);
							mpPostCommandPool[i].Assign(nullptr);
						}
						mpIndexBuffer.Assign(nullptr);
						mpViewProj.Assign(nullptr);
						mpModelTransform.Assign(nullptr);
						mpPipeline.Assign(nullptr);
						mpDepthBufferImages.clear();
						mpDepthBufferImageViews.clear();
						mpSwapChain.Assign(nullptr);
						mpDepthBufferImages.clear();
						mpDepthBufferImageViews.clear();
						mpFence.Assign(nullptr);
						mpResourceBinding.Assign(nullptr);

						mScheduler.Shutdown();
						for (auto& data : mWorkerData)
						{
							for (int i = 0; i < mBackBufferCount; ++i)
							{
								data.mpCommandPool[i].Assign(nullptr);
								data.mpCommandBuffer[i].Assign(nullptr);
							}
						}
						mpDevice.Assign(nullptr);
						gfxInstance.Assign(nullptr);
					}
				}
			}
			return 0;
		}
	};
}

CPF_CREATE_APPLICATION(Cpf::ExperimentalD3D12);
