//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Graphics.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/SwapChainDesc.hpp"
#include "Graphics/SwapEffect.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/iImageView.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Application/iApplication.hpp"
#include "Application/iWindow.hpp"
#include "Application/OSWindowData.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Graphics/SubResource.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Graphics/WindowData.hpp"
#include "Graphics/AttachmentDesc.hpp"
#include "Graphics/RenderPassDesc.hpp"
#include "Graphics/SubPassDesc.hpp"
#include "Graphics/FrameBufferDesc.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"

using namespace Cpf;
using namespace MultiCore;
using namespace Graphics;

COM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kRenderSystemCID, new Plugin::tClassInstance<RenderSystem>());
}

COM::Result RenderSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kRenderSystemCID);
}

COM::Result RenderSystem::Configure(MultiCore::iPipeline* pipeline)
{
	mpTimer = GetSystem<iTimer>(pipeline, mDesc.mTimer.GetString());
	return mpTimer != nullptr ? COM::kOK : COM::kInvalid;
}

bool RenderSystem::Initialize(Plugin::iRegistry* registry, COM::ClassID rid, iInputManager* im, iWindow* window, Resources::Locator* locator)
{
	if (Succeeded(registry->Create(nullptr, rid, Graphics::iInstance::kIID, mpInstance.AsVoidPP())))
	{
		if (_SelectAdapter() &&
			COM::Succeeded(mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP())) &&
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
		mpPreCommandPool[i].Adopt(nullptr);
		mpPreCommandBuffer[i].Adopt(nullptr);
		mpPostCommandPool[i].Adopt(nullptr);
		mpPostCommandBuffer[i].Adopt(nullptr);
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


RenderSystem::RenderSystem(COM::iUnknown*)
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
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, beginFrame.AsVoidPP());
	beginFrame->Initialize(this, "Begin Frame");
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, BlockOpcode::eFirst);
	AddStage(beginFrame);

	IntrusivePtr<iSingleUpdateStage> debugUI;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, debugUI.AsVoidPP());
	debugUI->Initialize(this, "DebugUI");
	debugUI->SetUpdate(&RenderSystem::_DebugUI, this, BlockOpcode::eLast);
	AddStage(debugUI);

	IntrusivePtr<iSingleUpdateStage> endFrame;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, endFrame.AsVoidPP());
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
	RenderPassDesc renderPassDesc;
	{
		// Create attachment references for the subpass.
		AttachmentRef colorAttachment;
		{
			colorAttachment.mIndex = 0;
			colorAttachment.mState = ResourceState::eRenderTarget;
		}
		AttachmentRef depthAttachment;
		{
			depthAttachment.mIndex = 1;
			depthAttachment.mState = ResourceState::eDepthWrite;
		}

		// Standard render to swap chain.
		SubPassDesc subPass;
		{
			subPass.mBindPoint = PipelineBindPoint::eGraphic;
			// No inputs.
			subPass.mInputCount = 0;
			subPass.mpInputAttachments = nullptr;
			// 1 color output.
			subPass.mColorCount = 1;
			subPass.mpColorAttachments = &colorAttachment;
			// No resolves.
			subPass.mResolveCount = 0;
			subPass.mpResolveAttachments = nullptr;
			// 1 depth buffer.
			subPass.mDepthStencilCount = 1;
			subPass.mpDepthStencilAttachments = &depthAttachment;
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
		ImageFlags::eAllowDepthStencil
	};
	mpDevice->CreateImage2D(&depthBufferDesc, nullptr, mpDepthBuffer.AsTypePP());
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

bool RenderSystem::_CreateRenderData(iInputManager* im, iWindow* window, Resources::Locator* locator)
{
	mpDevice->CreateFence(3, mpFence.AsTypePP());
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP());
		mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPreCommandPool[i], CommandBufferType::kPrimary, mpPreCommandBuffer[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPostCommandPool[i], CommandBufferType::kPrimary, mpPostCommandBuffer[i].AsTypePP());
		mpDevice->CreateCommandPool(mpDebugUIPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpDebugUIPool[i], CommandBufferType::kPrimary, mpDebugUIBuffer[i].AsTypePP());
	}
	mpRegistry->Create(nullptr, kDebugUICID, iDebugUI::kIID, mpDebugUI.AsVoidPP());
	mpDebugUI->Initialize(mpDevice, im, window, locator);

	return true;
}

void RenderSystem::_BeginFrame(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// Manage indexing.
	self.mScheduleIndex = 1;	// Skips 0, we'll be filling that in ourselves.
	self.mBufferIndex = (self.mBufferIndex + 1) % kBufferCount;
	self.mSwapIndex = self.mpSwapChain->GetCurrentIndex();

	// Can only have kBufferCount frames outstanding at a time so hang out here if we get too far ahead.
	auto lastFence = self.mFenceTarget;
	if (lastFence - self.mpFence->GetValue() >= kBufferCount)
		self.mpFence->WaitFor(lastFence - (kBufferCount - 1));

	// Issue on the shared command buffers.
	self.mpPreCommandPool[self.mBufferIndex]->Reset();
	self.mpPreCommandBuffer[self.mBufferIndex]->Reset(self.mpPreCommandPool[self.mBufferIndex]);
	self.mpPreCommandBuffer[self.mBufferIndex]->Begin();

	// TODO: This will move into the render pass abstraction when it is ready.
	self.mpDevice->BeginFrame(self.mpPreCommandBuffer[self.mBufferIndex]);

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

	self.mpPreCommandBuffer[self.mBufferIndex]->BeginRenderPass(&passBegin);

	/*
	// Cycle the colors to make sure things are working.
	Math::Vector4fv color(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color and depth buffers.
	self.mpPreCommandBuffer[self.mBufferIndex]->ClearRenderTargetView(
		self.mpSwapChain->GetImageView(self.mSwapIndex),
		color,
		0,
		nullptr);
		*/

	// Always the first to issue.
	self.mpScheduledBuffers[0] = self.mpPreCommandBuffer[self.mBufferIndex];
}

void RenderSystem::_DebugUI(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);
	float deltaTime = self.mpTimer->GetDeltaTime();

	self.mpDebugUIPool[self.mBufferIndex]->Reset();
	self.mpDebugUIBuffer[self.mBufferIndex]->Reset(self.mpDebugUIPool[self.mBufferIndex]);
	self.mpDebugUIBuffer[self.mBufferIndex]->Begin();

	iImageView* imageViews[] = { self.mpSwapChain->GetImageView(self.mSwapIndex) };
	self.mpDebugUIBuffer[self.mBufferIndex]->SetRenderTargets(1, imageViews, nullptr);

	self.mpDebugUI->BeginFrame(self.mpDebugUIBuffer[self.mBufferIndex], deltaTime);
	self.mpDebugUI->Execute();
	self.mpDebugUI->EndFrame(self.mpDebugUIBuffer[self.mBufferIndex]);

	self.mpDebugUIBuffer[self.mBufferIndex]->End();
	self.mpScheduledBuffers[Atomic::Inc(self.mScheduleIndex) - 1] = self.mpDebugUIBuffer[self.mBufferIndex];
}

void RenderSystem::_EndFrame(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// End the command buffer prior to submission.
	self.mpScheduledBuffers[0]->End();

	// 
	self.mpPostCommandPool[self.mBufferIndex]->Reset();
	self.mpPostCommandBuffer[self.mBufferIndex]->Reset(self.mpPostCommandPool[self.mBufferIndex]);
	self.mpPostCommandBuffer[self.mBufferIndex]->Begin();

	// Transition the back buffer to present.
	self.mpPostCommandBuffer[self.mBufferIndex]->ImageTransition(
		self.mpSwapChain->GetImage(self.mSwapIndex),
		ResourceState::eRenderTarget,
		ResourceState::ePresent,
		SubResource::eAll
	);
	self.mpPostCommandBuffer[self.mBufferIndex]->ImageTransition(
		self.mpDepthBuffer,
		ResourceState::eDepthWrite,
		ResourceState::ePresent,
		SubResource::eAll
	);

	// Insert the debug drawing buffers.
	iCommandBuffer* debugBuffer[2] = { self.mpScheduledBuffers[1], self.mpPostCommandBuffer[self.mBufferIndex] };
	self.mpPreCommandBuffer[self.mBufferIndex]->Insert(2, debugBuffer);

	// End the render pass.
	self.mpPreCommandBuffer[self.mBufferIndex]->EndRenderPass();

	// Let the device take care of any final needed work, read backs for instance.
	self.mpDevice->EndFrame(self.mpPostCommandBuffer[self.mBufferIndex]);

	// End the command buffer prior to submission.
	self.mpPostCommandBuffer[self.mBufferIndex]->End();

	// Pick up and add the transition for present.
	int32_t commandBufferCount = Atomic::Inc(self.mScheduleIndex);
	self.mpScheduledBuffers[commandBufferCount - 1] = self.mpPostCommandBuffer[self.mBufferIndex];

	// Submit the command buffers.
	self.mpDevice->Submit(commandBufferCount, self.mpScheduledBuffers);

	// Present the back buffer.
	self.mpSwapChain->Present();

	// Wait for completion.
	auto fenceToWaitFor = Atomic::Inc(self.mFenceTarget);
	self.mpDevice->Signal(self.mpFence, fenceToWaitFor);

	// TODO: Move into the render passes.
	self.mpDevice->Finalize();
}

//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL RenderSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case RenderSystem::kIID.GetID():
			*outIface = static_cast<RenderSystem*>(this);
			break;
		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc)
{
	mpRegistry = rgy; (void)desc;
	if (name)
	{
		mDesc = *static_cast<const Desc*>(desc);
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(this, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (COM::Succeeded(result))
			return COM::kOK;
		return result;
	}
	return COM::kInvalidParameter;
}

SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL RenderSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

COM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL RenderSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL RenderSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL RenderSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
