//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Graphics/Driver.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/SwapChainDesc.hpp"
#include "Graphics/SwapEffect.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/Format.hpp"
#include "Atomic/Atomic.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/iImageView.hpp"
#include "Graphics/HeapType.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "Application/iApplication.hpp"
#include "Application/iWindow.hpp"
#include "Application/OSWindowData.hpp"
#include "Plugin/tClassInstance.hpp"
#include "Graphics/SubResource.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Graphics/WindowData.hpp"
#include "Graphics/AttachmentDesc.hpp"
#include "Graphics/RenderPassDesc.hpp"
#include "Graphics/SubPassDesc.hpp"
#include "Graphics/FrameBufferDesc.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"

using namespace CPF;
using namespace MultiCore;
using namespace Graphics;

GOM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kRenderSystemCID.GetID(), new Plugin::tClassInstance<RenderSystem>());
}

GOM::Result RenderSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kRenderSystemCID.GetID());
}

GOM::Result RenderSystem::Configure(MultiCore::iExecutionPlan* pipeline)
{
	mpTimer = GetSystem<iTimer>(pipeline, mDesc.mTimer.GetString());
	return mpTimer != nullptr ? GOM::kOK : GOM::kInvalid;
}

bool RenderSystem::Initialize(Plugin::iRegistry* registry, GOM::ClassID rid, iInputManager* im, iWindow* window, Resources::iLocator* locator)
{
	if (GOM::Succeeded(registry->Create(nullptr, rid.GetID(), Graphics::iInstance::kIID.GetID(), mpInstance.AsVoidPP())))
	{
		if (_SelectAdapter() &&
			GOM::Succeeded(mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP())) &&
			_CreateRenderPass() &&
			_CreateSwapChain(window) &&
			_CreateRenderData(im, window, locator)
			)
		{
			int32_t w, h;
			window->GetClientAreaSize(&w, &h);
			mpDebugUI->SetWindowSize(w, h);
			_CreateStages();
			return true;
		}
	}
	return false;
}

bool RenderSystem::Shutdown()
{
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpPrimaryPool[i].Adopt(nullptr);
		mpPrimaryBuffer[i].Adopt(nullptr);
		mpDebugUIPool[i].Adopt(nullptr);
		mpDebugUIBuffer[i].Adopt(nullptr);
	}
	mpFence.Adopt(nullptr);

	mpDepthBuffer.Adopt(nullptr);
	mpDepthBufferView.Adopt(nullptr);

	mpDebugUI.Adopt(nullptr);
	mpSwapChain.Adopt(nullptr);
	mpDevice.Adopt(nullptr);
	mpAdapter.Adopt(nullptr);
	mpInstance.Adopt(nullptr);
	return true;
}

void RenderSystem::Resize(int32_t w, int32_t h)
{
	mWidth = w;
	mHeight = h;

	mpSwapChain->Resize(w, h);
	_CreateDepthBuffer(w, h);
	_CreateFrameBuffers(w, h);

	if (mpDebugUI)
		mpDebugUI->SetWindowSize(w, h);
}

iDebugUI* RenderSystem::GetDebugUI()
{
	return mpDebugUI;
}


RenderSystem::RenderSystem(GOM::iUnknown*)
	: mpTimer(nullptr)
	, mpRegistry(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::_CreateStages()
{
	IntrusivePtr<iSingleUpdateStage> beginFrame;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID.GetID(), MultiCore::iSingleUpdateStage::kIID.GetID(), beginFrame.AsVoidPP());
	beginFrame->Initialize(this, "Begin Frame");
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, BlockOpcode::eFirst);
	AddStage(beginFrame);

	IntrusivePtr<iSingleUpdateStage> debugUI;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID.GetID(), MultiCore::iSingleUpdateStage::kIID.GetID(), debugUI.AsVoidPP());
	debugUI->Initialize(this, "DebugUI");
	debugUI->SetUpdate(&RenderSystem::_DebugUI, this, BlockOpcode::eLast);
	AddStage(debugUI);

	IntrusivePtr<iSingleUpdateStage> endFrame;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID.GetID(), MultiCore::iSingleUpdateStage::kIID.GetID(), endFrame.AsVoidPP());
	endFrame->Initialize(this, "End Frame");
	endFrame->SetUpdate(&RenderSystem::_EndFrame, this, BlockOpcode::eLast);
	AddStage(endFrame);

	//////////////////////////////////////////////////////////////////////////
	AddDependency({
		{GetID(), endFrame->GetID(), iStage::kExecute},
		{GetID(), beginFrame->GetID(), iStage::kExecute},
		DependencyPolicy::eAfter
	});

	AddDependency({
		{ GetID(), debugUI->GetID(), iStage::kExecute },
		{ GetID(), beginFrame->GetID(), iStage::kExecute },
		DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), endFrame->GetID(), iStage::kExecute },
		{ GetID(), debugUI->GetID(), iStage::kExecute },
		DependencyPolicy::eBarrier
	});
}

bool RenderSystem::_SelectAdapter()
{
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	mpInstance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IntrusivePtr<iAdapter>> adapters;
	adapters.resize(adapterCount);
	mpInstance->EnumerateAdapters(adapterCount, adapters[0].AsTypePP());

	int bestAdapter = -1;
	for (int i = 0; i < adapterCount; ++i)
	{
		if (adapters[i]->IsSoftware() || adapters[i]->IsRemote())
			continue;
		bestAdapter = i;
		mpAdapter.Adopt(adapters[bestAdapter]);
		mpAdapter->AddRef();
		break;
	}

	return bestAdapter != -1;
}

bool RenderSystem::_CreateRenderPass()
{
	// Attachments in use.
	AttachmentDesc attachments[2];
	RenderPassDesc renderPassDesc;
	AttachmentRef colorAttachment;
	AttachmentRef depthAttachment;
	SubPassDesc subPass;
	{
		// Color buffer.
		attachments[0].mFlags = 0;
		attachments[0].mFormat = Format::eRGBA8un;
		attachments[0].mSamples = SampleDesc{ 1, 0 };
		attachments[0].mLoadOp = LoadOp::eClear;
		attachments[0].mStoreOp = StoreOp::eStore;
		attachments[0].mStencilLoadOp = LoadOp::eDontCare;
		attachments[0].mStencilStoreOp = StoreOp::eDontCare;
		// TODO: Figure out what makes the most sense.
		attachments[0].mStartState = ResourceState::eCommon;
		attachments[0].mFinalState = ResourceState::ePresent;

		// Depth buffer.
		attachments[1].mFlags = 0;
		attachments[1].mFormat = Format::eD32f;
		attachments[1].mSamples = SampleDesc{ 1, 0 };
		attachments[1].mLoadOp = LoadOp::eClear;
		attachments[1].mStoreOp = StoreOp::eStore;
		attachments[1].mStencilLoadOp = LoadOp::eLoad;
		attachments[1].mStencilStoreOp = StoreOp::eStore;
		// TODO: Figure out what makes the most sense.
		attachments[1].mStartState = ResourceState::eCommon;
		attachments[1].mFinalState = ResourceState::eCommon;
	}
	{
		// Create attachment references for the subpass.
		{
			colorAttachment.mIndex = 0;
			colorAttachment.mState = ResourceState::eRenderTarget;
		}
		{
			depthAttachment.mIndex = 1;
			depthAttachment.mState = ResourceState::eDepthWrite;
		}

		// Standard render to swap chain.
		{
			subPass.mBindPoint = PipelineBindPoint::eGraphic;
			// No inputs.
			subPass.mInputCount = 0;
			subPass.mpInputAttachments = nullptr;
			// 1 output.
			subPass.mAttachmentCount = 1;
			subPass.mpColorAttachments = &colorAttachment;
			// No resolves.
			subPass.mpResolveAttachments = nullptr;
			// 1 depth buffer.
			subPass.mpDepthStencilAttachment = &depthAttachment;
			// No preservation.
			subPass.mPreserveCount = 0;
			subPass.mpPreserveAttachments = nullptr;
		}

		// Setup the render pass descriptor.
		renderPassDesc.mAttachmentCount = 2;
		renderPassDesc.mpAttachments = attachments;
		renderPassDesc.mSubPassCount = 1;
		renderPassDesc.mpSubPasses = &subPass;
		renderPassDesc.mDependencyCount = 0;
		renderPassDesc.mpDependencies = nullptr;
	}
	// Create the render pass.
	mpDevice->CreateRenderPass(&renderPassDesc, mpRenderPass.AsTypePP());

	return true;
}

bool RenderSystem::_CreateSwapChain(iWindow* window)
{
	// Create the swapchain attached to the window.
	SwapChainDesc desc{
		Format::eRGBA8un,
		SwapEffect::eFlipDiscard,
		{ 1, 0 },
		kBufferCount,
		true
	};
	OSWindowData osData;
	window->GetOSData(&osData);
	WindowData winData;
	winData.mHWnd = osData.mHwnd;
	int32_t w, h;
	window->GetClientAreaSize(&w, &h);
	mWidth = w;
	mHeight = h;
	mpDevice->CreateSwapChain(mpInstance, &winData, w, h, &desc, mpSwapChain.AsTypePP());

	// Create the depth buffer.
	_CreateDepthBuffer(w, h);
	// Create the frame buffers.
	_CreateFrameBuffers(w, h);

	return mpSwapChain;
}

bool RenderSystem::_CreateRenderTargets(int32_t w, int32_t h)
{
	(void)w; (void)h;
	return false;
}

bool RenderSystem::_CreateDepthBuffer(int32_t w, int32_t h)
{
	mpDepthBuffer.Adopt(nullptr);
	mpDepthBufferView.Adopt(nullptr);

	// Create a depth buffer to go with the swap chain.
	ImageDesc depthBufferDesc
	{
		w, h,
		1,
		1,
		Format::eD32f,
		{ 1, 0 },
		ResourceState::eCommon,
		ImageFlags::eAllowDepthStencil
	};
	ClearValue clearValue;
	clearValue.mFormat = Format::eD32f;
	clearValue.mDepthStencil.mDepth = 1.0f;
	clearValue.mDepthStencil.mStencil = 0;
	mpDevice->CreateImage2D(HeapType::eDefault, &depthBufferDesc, &clearValue, mpDepthBuffer.AsTypePP());
	mpDevice->CreateDepthStencilView(mpDepthBuffer, nullptr, mpDepthBufferView.AsTypePP());

	return true;
}

bool RenderSystem::_CreateFrameBuffers(int32_t w, int32_t h)
{
	// Make a frame buffer for each target in the swap chain.
	mpFrameBuffers.clear();
	mpFrameBuffers.resize(kBufferCount);
	for (int i = 0; i < kBufferCount; ++i)
	{
		FrameBufferDesc frameBufferDesc;
		frameBufferDesc.mpRenderPass = mpRenderPass;
		frameBufferDesc.mAttachmentCount = 2;
		ImageAndView images[2] =
		{
			{mpSwapChain->GetImage(i), mpSwapChain->GetImageView(i)},
			{mpDepthBuffer, mpDepthBufferView}
		};
		frameBufferDesc.mpAttachments = images;
		frameBufferDesc.mWidth = w;
		frameBufferDesc.mHeight = h;
		frameBufferDesc.mLayers = 1;

		mpDevice->CreateFrameBuffer(&frameBufferDesc, mpFrameBuffers[i].AsTypePP());
	}

	return true;
}

bool RenderSystem::_CreateRenderData(iInputManager* im, iWindow* window, Resources::iLocator* locator)
{
	mpDevice->CreateFence(3, mpFence.AsTypePP());
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(mpPrimaryPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPrimaryPool[i], CommandBufferType::kPrimary, mpPrimaryBuffer[i].AsTypePP());
		mpDevice->CreateCommandPool(mpDebugUIPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpDebugUIPool[i], CommandBufferType::kSecondary, mpDebugUIBuffer[i].AsTypePP());
	}
	mpRegistry->Create(nullptr, kDebugUICID.GetID(), iDebugUI::kIID.GetID(), mpDebugUI.AsVoidPP());
	mpDebugUI->Initialize(mpDevice, im, window, locator);

	return true;
}

void RenderSystem::_BeginFrame(const Concurrency::WorkContext*, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// Manage indexing.
	self.mBufferIndex = (self.mBufferIndex + 1) % kBufferCount;
	self.mSwapIndex = self.mpSwapChain->GetCurrentIndex();

	// Issue on the shared command buffers.
	self.mpPrimaryPool[self.mBufferIndex]->Reset();
	self.mpPrimaryBuffer[self.mBufferIndex]->Reset(self.mpPrimaryPool[self.mBufferIndex]);
	self.mpPrimaryBuffer[self.mBufferIndex]->Begin(nullptr);

	// Begin the render pass.
	RenderPassBeginDesc passBegin;
	passBegin.mpRenderPass = self.mpRenderPass;
	passBegin.mpFrameBuffer = self.mpFrameBuffers[self.mSwapIndex];
	passBegin.mClipRect = Math::Rectanglei(0, self.mWidth, 0, self.mHeight);
	passBegin.mClearValueCount = 2;

	ClearValue clearValues[2];
	clearValues[0].mFormat = Format::eRGBA8un;
	clearValues[0].mColor[0] = 0.0f;
	clearValues[0].mColor[1] = 0.0f;
	clearValues[0].mColor[2] = 0.0f;
	clearValues[0].mColor[3] = 1.0f;

	clearValues[1].mFormat = Format::eD32f;
	clearValues[1].mDepthStencil.mDepth = 1.0f;
	clearValues[1].mDepthStencil.mStencil = 0;
	passBegin.mpClearValues = clearValues;

	self.mpPrimaryBuffer[self.mBufferIndex]->BeginRenderPass(&passBegin);
}

void RenderSystem::_DebugUI(const Concurrency::WorkContext*, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);
	float deltaTime = self.mpTimer->GetDeltaTime();

	self.mpDebugUIPool[self.mBufferIndex]->Reset();
	self.mpDebugUIBuffer[self.mBufferIndex]->Reset(self.mpDebugUIPool[self.mBufferIndex]);
	self.mpDebugUIBuffer[self.mBufferIndex]->Begin(self.mpPrimaryBuffer[self.mBufferIndex]);

//	iImageView* imageViews[] = { self.mpSwapChain->GetImageView(self.mSwapIndex) };
//	self.mpDebugUIBuffer[self.mBufferIndex]->SetRenderTargets(1, imageViews, nullptr);

	self.mpDebugUI->BeginFrame(self.mpDebugUIBuffer[self.mBufferIndex], deltaTime);
	self.mpDebugUI->Execute();
	self.mpDebugUI->EndFrame(self.mpDebugUIBuffer[self.mBufferIndex]);

	self.mpDebugUIBuffer[self.mBufferIndex]->End();
}

void RenderSystem::_EndFrame(const Concurrency::WorkContext*, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// Insert the draw buffers.
	{
		iCommandBuffer* buffers[1] = { self.mpDebugUIBuffer[self.mBufferIndex] };
		self.mpPrimaryBuffer[self.mBufferIndex]->Insert(1, buffers);
	}

	// End the render pass.
	self.mpPrimaryBuffer[self.mBufferIndex]->EndRenderPass();

	// End the command buffer prior to submission.
	self.mpPrimaryBuffer[self.mBufferIndex]->End();

	// Submit the command buffers.
	{
		iCommandBuffer* buffers[1] = { self.mpPrimaryBuffer[self.mBufferIndex] };
		self.mpDevice->Submit(1, buffers);
	}

	// Wait for completion.
	auto fenceToWaitFor = Atomic::Inc(self.mFenceTarget);
	self.mpDevice->Signal(self.mpFence, fenceToWaitFor);

	// Need to wait for the above to complete before we attempt to present the swap chain.
	auto lastFence = self.mFenceTarget;
	if (lastFence - self.mpFence->GetValue() >= kBufferCount)
		self.mpFence->WaitFor(lastFence - (kBufferCount - 1));

	// Present the back buffer.
	self.mpSwapChain->Present();
}

//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL RenderSystem::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case RenderSystem::kIID.GetID():
			*outIface = static_cast<RenderSystem*>(this);
			break;
		default:
			return GOM::kNotImplemented;
		}

		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc)
{
	mpRegistry = rgy; (void)desc;
	if (name)
	{
		mDesc = *static_cast<const Desc*>(desc);
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(this, kStageListCID.GetID(), iStageList::kIID.GetID(), mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
			return GOM::kOK;
		return result;
	}
	return GOM::kInvalidParameter;
}

SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL RenderSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

GOM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

GOM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

GOM::Result CPF_STDCALL RenderSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

GOM::Result CPF_STDCALL RenderSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL RenderSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

GOM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iExecutionPlan* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
