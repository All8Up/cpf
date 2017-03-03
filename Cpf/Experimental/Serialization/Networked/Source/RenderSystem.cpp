//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Graphics.hpp"
#include "MultiCore/Stage.hpp"

using namespace Cpf;
using namespace MultiCore;
using namespace Graphics;

bool RenderSystem::Install()
{
	return System::Install(kID, &RenderSystem::_Create);
}

bool RenderSystem::Remove()
{
	return System::Remove(kID);
}

bool RenderSystem::Initialize(iWindow* window)
{
	if (Graphics::Create(1, mpInstance.AsTypePP()))
	{
		if (_SelectAdapter() &&
			mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP()) &&
			_CreateSwapChain(window)
			)
		{
			_CreateStages();
			return true;
		}
	}
	return false;
}

bool RenderSystem::Shutdown()
{
	mpSwapChain.Adopt(nullptr);
	mpDevice.Adopt(nullptr);
	mpAdapter.Adopt(nullptr);
	mpInstance.Adopt(nullptr);
	return true;
}

void RenderSystem::Resize(int32_t w, int32_t h)
{
	mpSwapChain->Resize(w, h);
}

Graphics::DebugUI& RenderSystem::GetDebugUI()
{
	return *mpDebugUI;
}


RenderSystem::RenderSystem(Pipeline* pipeline, const char* name, const Desc* desc)
	: System(pipeline, name)
{
	(void)desc;
}

RenderSystem::~RenderSystem()
{}

System* RenderSystem::_Create(MultiCore::Pipeline* owner, const char* name, const Desc* desc)
{
	return new RenderSystem(owner, name, desc);
}

void RenderSystem::_CreateStages()
{
	IntrusivePtr<SingleUpdateStage> beginFrame(Stage::Create<SingleUpdateStage>(this, "Begin Frame"));
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, BlockOpcode::eFirst);
	AddStage(beginFrame);

	IntrusivePtr<SingleUpdateStage> endFrame(Stage::Create<SingleUpdateStage>(this, "End Frame"));
	endFrame->SetUpdate(&RenderSystem::_EndFrame, this, BlockOpcode::eLast);
	AddStage(endFrame);


	AddDependency({
		{GetID(), endFrame->GetID(), Stage::kExecute},
		{GetID(), beginFrame->GetID(), Stage::kExecute},
		DependencyPolicy::eAfter
	});
}

bool RenderSystem::_SelectAdapter()
{
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	mpInstance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IntrusivePtr<Graphics::iAdapter>> adapters;
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
	mpDevice->CreateSwapChain(mpInstance, window, &desc, mpSwapChain.AsTypePP());

	/*
	// Create a set of depth buffers to go with the swap chain.
	mpDepthBufferImages.resize(desc.mBackBufferCount);
	mpDepthBufferImageViews.resize(desc.mBackBufferCount);
	ImageDesc depthBufferDesc
	{
		mpWindow->GetClientArea().x, mpWindow->GetClientArea().y,
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
	*/

	return mpSwapChain;
}

void RenderSystem::_BeginFrame(Concurrency::ThreadContext&, void* context)
{
	
}

void RenderSystem::_EndFrame(Concurrency::ThreadContext&, void* context)
{
	
}
