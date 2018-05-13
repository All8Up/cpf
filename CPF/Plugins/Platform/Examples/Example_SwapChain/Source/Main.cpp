//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Application.hpp"
#include "CPF/IO/File.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/GOM/tUnknown.hpp"

#include "CPF/Platform/iDesktop.hpp"
#include "CPF/Platform/Desktop/iWindow.hpp"
#include "CPF/Platform/Desktop/iEventLoop.hpp"
#include "CPF/Platform/Desktop/OSWindowData.hpp"

#include "CPF/Platform/Graphics.hpp"
#include "CPF/Time.hpp"

using namespace CPF;

// This example is hard coded to a specific graphics driver for
// purposes of demonstration.  The driver can be loaded dynamically
// based on configuration if desired.
#define GRAPHICS_DRIVER CPF_CONCAT(PlatformGraphics, CPF_GRAPHICS_DRIVER)

CPF_BEGIN_PLUGINS(SwapChainApp)
CPF_INSTALL_PLUGIN(SwapChainApp, PlatformDesktopSDL2);
CPF_INSTALL_PLUGIN(SwapChainApp, GRAPHICS_DRIVER);

/** @brief This is a basic 'renderer' layer on top of the driver layer.
 *  For the purposes here, it simply sets up a swap chain and
 *  changes the clear color over time.
 */
class Renderer
{
public:
	Renderer()
		: mpRegistry(nullptr)
		, mpWindow(nullptr)
	{}

	bool Initialize(Plugin::iRegistry* registry, Platform::Desktop::iWindow* window);

	void operator ()()
	{
		BeginFrame();
		EndFrame();
	}

private:
	static constexpr int32_t kBufferCount = 3;

	GOM::CID FindGraphicsDriver() const;
	Graphics::iAdapter* GetBestAdapter() const;
	GOM::Result CreateSwapChain();
	GOM::Result CreateRenderPass();
	bool CreateFrameBuffers();
	bool CreateRenderObjects();

	void BeginFrame();
	void EndFrame();

	Plugin::iRegistry* mpRegistry;
	Platform::Desktop::iWindow* mpWindow;

	// Basic graphics device objects.
	IntrusivePtr<Graphics::iInstance> mpInstance;
	IntrusivePtr<Graphics::iAdapter> mpAdapter;
	IntrusivePtr<Graphics::iDevice> mpDevice;
	IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
	IntrusivePtr<Graphics::iRenderPass> mpRenderPass;
	STD::Vector<IntrusivePtr<Graphics::iFrameBuffer>> mpFrameBuffers;
	IntrusivePtr<Graphics::iImage> mpDepthBuffer;
	IntrusivePtr<Graphics::iImageView> mpDepthBufferView;

	// Window size information for initializing the swap chain.
	int32_t mWidth = 400;
	int32_t mHeight = 400;

	// Indexing into the per frame buffers and swap chain.
	int32_t mBufferIndex = 0;
	int32_t mSwapIndex = 0;

	// Device objects related to actual presentation.
	IntrusivePtr<Graphics::iCommandPool> mpPrimaryPool[kBufferCount];
	IntrusivePtr<Graphics::iCommandBuffer> mpPrimaryCommands[kBufferCount];
	IntrusivePtr<Graphics::iFence> mpFences[kBufferCount];

	// Timer to cycle the background color so something visibly changes.
	Time::Value mTime;
	Time::Value mLastTime;
};

/** @brief A basic windowed application. */
class SwapChainApp : public GOM::tUnknown<iApplication>
{
public:
	SwapChainApp(Plugin::iRegistry* registry)
		: mpRegistry(registry)
		, mpRenderer(nullptr)
	{}

	// Run your application here and return the integral value the process will exit with.
	int32_t Run() override
	{
		int32_t result = 0;

		// TODO: This should probably be pulled in from a simple config like file as part of the
		// application wrapper itself.  So this should eventually be removed.
		// Setup initial working directory to be in the
		// resources directory.
		{
			auto exePath = IO::File::GetExecutableFilePath();
			exePath += "../resources/";
			IO::Directory::SetWorkingDirectory(exePath);
		}

		// Install the plugins and then
		// create the application events object and
		// an uninitialized window object.
		IntrusivePtr<Platform::iDesktop> desktop;
		IntrusivePtr<Platform::Desktop::iEventLoop> events;
		Platform::Desktop::WindowDesc windowDesc = {
			"Hello SwapChain",
			Platform::Desktop::kDesktopCentered, Platform::Desktop::kDesktopCentered,
			400, 400,
			Platform::Desktop::WindowFlags::eNone
		};
		CPF_INSTALL_PLUGINS(mpRegistry, SwapChainApp);
		if (GOM::Succeeded(mpRegistry->Create(nullptr, Platform::iDesktop::kCID, Platform::iDesktop::kIID, desktop.AsVoidPP())) &&
			GOM::Succeeded(mpRegistry->Create(nullptr, Platform::Desktop::iEventLoop::kCID, Platform::Desktop::iEventLoop::kIID, events.AsVoidPP())) &&
			(mpWindow = IntrusivePtr<Platform::Desktop::iWindow>(desktop->CreateWindow(&windowDesc).TryOK()))
			)
		{
			// Create the graphics system to drive the example.
			mpRenderer = new Renderer();
			if (mpRenderer != nullptr && mpRenderer->Initialize(mpRegistry, mpWindow))
			{
				// Run the application event loop until quit is received.
				while (events->RunAvailable() != Platform::Desktop::kQuit)
				{
					(*mpRenderer)();
				}
			}
			else
				result = -1;
		}
		else
			result = -1;

		CPF_REMOVE_PLUGINS(mpRegistry, SwapChainApp);
		return result;
	}

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
	IntrusivePtr<Platform::Desktop::iWindow> mpWindow;
	Renderer* mpRenderer;
};


//////////////////////////////////////////////////////////////////////////
bool Renderer::Initialize(Plugin::iRegistry* registry, Platform::Desktop::iWindow* window)
{
	mpRegistry = registry;
	mpWindow = window;

	mTime = Time::Value();
	mLastTime = Time::Now();

	// TODO: everything from here to swap chain creation should be
	// moved (without removing this manual solution) into a helper.
	// Probably something like window->CreateCanvas.

	// Find the graphics driver to create.
	const auto graphicsDriver = FindGraphicsDriver();
	if (graphicsDriver == GOM::CID::eInvalid)
		return false;

	// Create the graphics instance to work with.
	if (GOM::Failed(mpRegistry->Create(nullptr, graphicsDriver, Graphics::iInstance::kIID, mpInstance.AsVoidPP())))
		return false;

	// Initialize the graphics instance with or without the debug layers as appropriate.
#ifdef CPF_DEBUG
	Graphics::InstanceDesc instanceInitDesc{ true };
#else
	Graphics::InstanceDesc instanceInitDesc{ false };
#endif
	if (GOM::Failed(mpInstance->Initialize(&instanceInitDesc)))
		return false;

	// Get the best graphics adapter to use.
	if (!mpAdapter.Adopt(GetBestAdapter()))
		return false;

	// Create the graphics device.
	if (GOM::Failed(mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP())))
		return false;

	// Create the swap chain.
	if (GOM::Failed(CreateSwapChain()))
		return false;

	// Create the render pass.
	if (GOM::Failed(CreateRenderPass()))
		return false;

	// Create the target framebuffers.
	if (CreateFrameBuffers())
	{
		return CreateRenderObjects();
	}
	return false;
}

GOM::CID Renderer::FindGraphicsDriver() const
{
	int32_t typeCount = 0;
	if (GOM::Succeeded(mpRegistry->GetClasses(Graphics::iInstance::kIID, &typeCount, nullptr)))
	{
		STD::Vector<GOM::CID> classes(typeCount);
		if (GOM::Succeeded(mpRegistry->GetClasses(Graphics::iInstance::kIID, &typeCount, classes.data())))
		{
			if (typeCount > 0)
				return classes[0];
		}
	}
	return GOM::CID::eInvalid;
}

Graphics::iAdapter* Renderer::GetBestAdapter() const
{
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	mpInstance->EnumerateAdapters(&adapterCount, nullptr);
	if (adapterCount == 0)
	{
		CPF_LOG(Vulkan, Info) << "No Vulkan adapters found!";
		return nullptr;
	}

	STD::Vector<IntrusivePtr<Graphics::iAdapter>> adapters;
	adapters.resize(adapterCount);
	mpInstance->EnumerateAdapters(&adapterCount, adapters[0].AsTypePP());

	int bestAdapter = -1;
	for (int i = 0; i < adapterCount; ++i)
	{
		if (adapters[i]->IsSoftware() || adapters[i]->IsRemote())
			continue;
		bestAdapter = i;
	}
	if (bestAdapter != -1)
	{
		Graphics::iAdapter* result = adapters[bestAdapter];
		result->AddRef();
		return result;
	}

	return nullptr;
}

GOM::Result Renderer::CreateSwapChain()
{
	int32_t w, h;
	mpWindow->GetClientArea(&w, &h);

	// Create the swapchain.
	Graphics::SwapChainDesc desc{
		Graphics::Format::eBGRA8un,
		Graphics::SwapEffect::eFlipDiscard,
		{ 1, 0 },
		kBufferCount,
		true,
		false
	};
	Platform::Desktop::OSWindowData osData {nullptr};
	mpWindow->GetOSData(&osData);
	Graphics::WindowData winData {nullptr};
	winData.mHWnd = osData.mHwnd;
	if (GOM::Succeeded(mpDevice->CreateSwapChain(mpInstance, &winData, w, h, &desc, mpSwapChain.AsTypePP())))
	{
		// Create a depth buffer to go with the swap chain.
		Graphics::ImageDesc depthBufferDesc
		{
			w, h,
			1,
			1,
			Graphics::Format::eD32f,
			{ 1, 0 },
			Graphics::ResourceState::eCommon,
			Graphics::ImageFlags::eAllowDepthStencil
		};
		Graphics::ClearValue clearValue;
		clearValue.mFormat = Graphics::Format::eD32f;
		clearValue.mData.mDepthStencil.mDepth = 1.0f;
		clearValue.mData.mDepthStencil.mStencil = 0;

		if (GOM::Succeeded(mpDevice->CreateImage2D(Graphics::HeapType::eDefault, &depthBufferDesc, &clearValue, mpDepthBuffer.AsTypePP())))
			return mpDevice->CreateDepthStencilView(mpDepthBuffer, nullptr, mpDepthBufferView.AsTypePP());
	}
	return GOM::kError;
}

GOM::Result Renderer::CreateRenderPass()
{
	// Color buffer.
	Graphics::AttachmentDesc attachments[2];
	attachments[0].mFlags = 0;
	attachments[0].mFormat = Graphics::Format::eBGRA8un;
	attachments[0].mSamples = Graphics::SampleDesc{ 1, 0 };
	attachments[0].mLoadOp = Graphics::LoadOp::eClear;
	attachments[0].mStoreOp = Graphics::StoreOp::eStore;
	attachments[0].mStencilLoadOp = Graphics::LoadOp::eDontCare;
	attachments[0].mStencilStoreOp = Graphics::StoreOp::eDontCare;
	// TODO: Probably change this to a 'usage' parameter and get rid of
	// the states.  For this case, AttachmentUsage::eSwapChainImage perhaps?
	attachments[0].mStartState = Graphics::ResourceState::eUndefined;
	attachments[0].mFinalState = Graphics::ResourceState::ePresent;

	// Depth buffer.
	attachments[1].mFlags = 0;
	attachments[1].mFormat = Graphics::Format::eD32f;
	attachments[1].mSamples = Graphics::SampleDesc{ 1, 0 };
	attachments[1].mLoadOp = Graphics::LoadOp::eClear;
	attachments[1].mStoreOp = Graphics::StoreOp::eStore;
	attachments[1].mStencilLoadOp = Graphics::LoadOp::eLoad;
	attachments[1].mStencilStoreOp = Graphics::StoreOp::eStore;
	attachments[1].mStartState = Graphics::ResourceState::eUndefined;
	attachments[1].mFinalState = Graphics::ResourceState::eCommon;

	// Create attachment references for the subpass.
	Graphics::AttachmentRef colorAttachment{ 0 };
	colorAttachment.mIndex = 0;
	// TODO: See above.  AttachmentUsage::eColorTarget
	colorAttachment.mState = Graphics::ResourceState::eRenderTarget;

	Graphics::AttachmentRef depthAttachment{ 0 };
	depthAttachment.mIndex = 1;
	depthAttachment.mState = Graphics::ResourceState::eDepthWrite;

	// Standard render to swap chain.
	Graphics::SubPassDesc subPass;
	subPass.mBindPoint = Graphics::PipelineBindPoint::eGraphic;
	subPass.mInputCount = 0;
	subPass.mpInputAttachments = nullptr;
	subPass.mAttachmentCount = 1;
	subPass.mpColorAttachments = &colorAttachment;
	subPass.mpResolveAttachments = nullptr;
	subPass.mpDepthStencilAttachment = &depthAttachment;
	subPass.mPreserveCount = 0;
	subPass.mpPreserveAttachments = nullptr;

	// Setup the render pass descriptor.
	Graphics::RenderPassDesc renderPassDesc{ 0 };
	renderPassDesc.mAttachmentCount = 2;
	renderPassDesc.mpAttachments = attachments;
	renderPassDesc.mSubPassCount = 1;
	renderPassDesc.mpSubPasses = &subPass;
	renderPassDesc.mDependencyCount = 0;
	renderPassDesc.mpDependencies = nullptr;

	// And finally create the render pass.
	return mpDevice->CreateRenderPass(&renderPassDesc, mpRenderPass.AsTypePP());
}

bool Renderer::CreateFrameBuffers()
{
	int32_t w, h;
	mpWindow->GetClientArea(&w, &h);

	// Make a frame buffer for each target in the swap chain.
	mpFrameBuffers.clear();
	mpFrameBuffers.resize(kBufferCount);
	for (int i = 0; i < kBufferCount; ++i)
	{
		Graphics::FrameBufferDesc frameBufferDesc{0};
		frameBufferDesc.mpRenderPass = mpRenderPass;
		frameBufferDesc.mAttachmentCount = 2;
		Graphics::ImageAndView images[2] =
		{
			{ mpSwapChain->GetImage(i), mpSwapChain->GetImageView(i) },
			{ mpDepthBuffer, mpDepthBufferView }
		};
		frameBufferDesc.mpAttachments = images;
		frameBufferDesc.mWidth = w;
		frameBufferDesc.mHeight = h;
		frameBufferDesc.mLayers = 1;

		if (GOM::Failed(mpDevice->CreateFrameBuffer(&frameBufferDesc, mpFrameBuffers[i].AsTypePP())))
			return false;
	}

	return true;
}

bool Renderer::CreateRenderObjects()
{
	for (int i = 0; i < kBufferCount; ++i)
	{
		// Start in the signaled state.
		if (GOM::Failed(mpDevice->CreateFence(true, mpFences[i].AsTypePP())))
			return false;

		if (GOM::Failed(mpDevice->CreateCommandPool(mpPrimaryPool[i].AsTypePP())))
			return false;
		if (GOM::Failed(mpDevice->CreateCommandBuffer(mpPrimaryPool[i], Graphics::CommandBufferType::ePrimary, mpPrimaryCommands[i].AsTypePP())))
			return false;
	}
	return true;
}

void Renderer::BeginFrame()
{
	// Manage indexing.
	mBufferIndex = (mBufferIndex + 1) % kBufferCount;
	mSwapIndex = mpSwapChain->GetCurrentIndex();

	// Wait for the fence we're about to use to become available.
	mpFences[mBufferIndex]->Wait();
	mpFences[mBufferIndex]->Reset();

	// Prepare the primary command buffer for use.
	mpPrimaryPool[mBufferIndex]->Reset();
	mpPrimaryCommands[mBufferIndex]->Reset(mpPrimaryPool[mBufferIndex]);
	mpPrimaryCommands[mBufferIndex]->Begin(nullptr);

	// Begin the render pass.
	Graphics::RenderPassBeginDesc passBegin;
	passBegin.mpRenderPass = mpRenderPass;
	passBegin.mpFrameBuffer = mpFrameBuffers[mSwapIndex];
	passBegin.mClipRect = Math::Rectanglei(0, mWidth, 0, mHeight);
	passBegin.mClearValueCount = 2;

	// Update the timer for color cycling.
	mTime += Time::Now() - mLastTime;
	mLastTime = Time::Now();
	float color = fmod(float(Time::Seconds(mTime)) * 0.25f, 1.0f);

	// Set the clear color applied to the back buffer.
	Graphics::ClearValue clearValues[2];
	clearValues[0].mFormat = Graphics::Format::eRGBA8un;
	clearValues[0].mDataType = Graphics::ClearValueType::eColor;
	clearValues[0].mData.mColor.mColor[0] = color;
	clearValues[0].mData.mColor.mColor[1] = color;
	clearValues[0].mData.mColor.mColor[2] = color;
	clearValues[0].mData.mColor.mColor[3] = 1.0f;

	clearValues[1].mFormat = Graphics::Format::eD32f;
	clearValues[1].mDataType = Graphics::ClearValueType::eDepthStencil;
	clearValues[1].mData.mDepthStencil.mDepth = 1.0f;
	clearValues[1].mData.mDepthStencil.mStencil = 0;
	passBegin.mpClearValues = clearValues;

	// And kick off the render pass, this clears the backbuffer as described in the pass.
	mpPrimaryCommands[mBufferIndex]->BeginRenderPass(&passBegin);
}

void Renderer::EndFrame()
{
	// End the render pass.
	mpPrimaryCommands[mBufferIndex]->EndRenderPass();

	// End the command buffer prior to submission.
	mpPrimaryCommands[mBufferIndex]->End();

	// Submit the command buffers.
	{
		Graphics::iCommandBuffer* buffers[1] = { mpPrimaryCommands[mBufferIndex] };
		mpDevice->Submit(1, buffers);
	}

	// Signal frame completion.
	mpDevice->Signal(mpFences[mBufferIndex]);

	// Present the back buffer.
	mpSwapChain->Present();
}



//////////////////////////////////////////////////////////////////////////
// Register the application.
CPF_APPLICATION(SwapChainApp);
