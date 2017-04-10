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
#include "Application/Application.hpp"
#include "Application/Window.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Graphics/SubResource.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Graphics/WindowData.hpp"

using namespace Cpf;
using namespace MultiCore;
using namespace Graphics;

COM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kRenderSystemCID, new Plugin::tSimpleClassInstance<RenderSystem>());
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

bool RenderSystem::Initialize(Plugin::iRegistry* registry, iWindow* window, Resources::Locator* locator)
{
	if (Succeeded(registry->Create(nullptr, kD3D12InstanceCID, Graphics::iInstance::kIID, mpInstance.AsVoidPP())))
	{
		if (_SelectAdapter() &&
			COM::Succeeded(mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP())) &&
			_CreateSwapChain(window) &&
			_CreateRenderData(window, locator)
			)
		{
			mpDebugUI->SetWindowSize(window->GetClientArea().x, window->GetClientArea().y);
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

	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();

	mpDebugUI.Adopt(nullptr);
	mpSwapChain.Adopt(nullptr);
	mpDevice.Adopt(nullptr);
	mpAdapter.Adopt(nullptr);
	mpInstance.Adopt(nullptr);
	return true;
}

void RenderSystem::Resize(int32_t w, int32_t h)
{
	mpSwapChain->Resize(w, h);
	if (mpDebugUI)
		mpDebugUI->SetWindowSize(w, h);
}

iDebugUI* RenderSystem::GetDebugUI()
{
	return mpDebugUI;
}


RenderSystem::RenderSystem()
	: mpTimer(nullptr)
	, mpRegistry(nullptr)
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
	WindowData winData;
	winData.mHWnd = window->GetOSWindowData().mHwnd;
	mpDevice->CreateSwapChain(mpInstance, &winData, window->GetClientArea().x, window->GetClientArea().y, &desc, mpSwapChain.AsTypePP());

	// Create a set of depth buffers to go with the swap chain.
	// TODO: There should really only be one shared depth buffer.
	mpDepthBufferImages.resize(desc.mBackBufferCount);
	mpDepthBufferImageViews.resize(desc.mBackBufferCount);
	ImageDesc depthBufferDesc
	{
		window->GetClientArea().x, window->GetClientArea().y,
		1,
		1,
		Format::eD32f,
		{ 1, 0 },
		ImageFlags::eAllowDepthStencil
	};
	for (int i = 0; i < desc.mBackBufferCount; ++i)
	{
		mpDevice->CreateImage2D(&depthBufferDesc, nullptr, mpDepthBufferImages[i].AsTypePP());
		mpDevice->CreateDepthStencilView(mpDepthBufferImages[i], nullptr, mpDepthBufferImageViews[i].AsTypePP());
	}

	return mpSwapChain;
}

bool RenderSystem::_CreateRenderData(iWindow* window, Resources::Locator* locator)
{
	mpDevice->CreateFence(3, mpFence.AsTypePP());
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP());
		mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPreCommandPool[i], mpPreCommandBuffer[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPostCommandPool[i], mpPostCommandBuffer[i].AsTypePP());
		mpDevice->CreateCommandPool(mpDebugUIPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpDebugUIPool[i], mpDebugUIBuffer[i].AsTypePP());
	}
	mpRegistry->Create(nullptr, kDebugUICID, iDebugUI::kIID, mpDebugUI.AsVoidPP());
	mpDebugUI->Initialize(mpDevice, window, locator);
	return true;
}

void RenderSystem::_BeginFrame(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// Manage indexing.
	self.mScheduleIndex = 1;	// Skips 0, we'll be filling that in ourselves.
	self.mBufferIndex = (self.mBufferIndex + 1) % kBufferCount;
	self.mSwapIndex = self.mpSwapChain->GetCurrentIndex();

	// Can only have 3 frames outstanding at a time so hang out here if we get too far ahead.
	auto lastFence = self.mFenceTarget;
	if (lastFence - self.mpFence->GetValue() >= kBufferCount)
		self.mpFence->WaitFor(lastFence - (kBufferCount - 1));

	// Issue on the shared command buffers.
	self.mpPreCommandPool[self.mBufferIndex]->Reset();
	self.mpPreCommandBuffer[self.mBufferIndex]->Reset(self.mpPreCommandPool[self.mBufferIndex]);
	self.mpPreCommandBuffer[self.mBufferIndex]->Begin();

	// TODO: This will move into the render pass abstraction when it is ready.
	self.mpDevice->BeginFrame(self.mpPreCommandBuffer[self.mBufferIndex]);

	// Transition the current back buffer and depth buffers to render targets.
	// TODO: This will go away with the render pass abstraction.
	self.mpPreCommandBuffer[self.mBufferIndex]->ImageTransition(
		self.mpSwapChain->GetImage(self.mSwapIndex),
		ResourceState::ePresent,
		ResourceState::eRenderTarget,
		SubResource::eAll);

	// Cycle the colors to make sure things are working.
	Math::Vector4fv color(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color and depth buffers.
	self.mpPreCommandBuffer[self.mBufferIndex]->ClearRenderTargetView(self.mpSwapChain->GetImageView(self.mSwapIndex), color, 0, nullptr);

	// End the command buffer prior to submission.
	self.mpPreCommandBuffer[self.mBufferIndex]->End();

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

	// 
	self.mpPostCommandPool[self.mBufferIndex]->Reset();
	self.mpPostCommandBuffer[self.mBufferIndex]->Reset(self.mpPostCommandPool[self.mBufferIndex]);
	self.mpPostCommandBuffer[self.mBufferIndex]->Begin();

	// Transition the back buffer to present.
	self.mpPostCommandBuffer[self.mBufferIndex]->ImageTransition(self.mpSwapChain->GetImage(self.mSwapIndex), ResourceState::eRenderTarget, ResourceState::ePresent, SubResource::eAll);

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
		auto result = rgy->Create(nullptr, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
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
