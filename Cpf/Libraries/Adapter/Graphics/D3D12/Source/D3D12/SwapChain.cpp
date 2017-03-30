//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/SwapChain.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Adapter/D3D12/Image.hpp"
#include "Application/Application.hpp"
#include "Application/Window.hpp"
#include "Logging/Logging.hpp"
#include "Move.hpp"

#ifdef CPF_DEBUG
#pragma comment( lib, "dxguid.lib")
#endif

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

SwapChain::SwapChain(
	Instance* instance,
	Graphics::iDevice* device,
	iWindow* window,
	const Graphics::SwapChainDesc* desc
	CPF_GFX_DEBUG_PARAM_DEF)
	: mpDevice(static_cast<Device*>(device))
	, mDesc(*desc)
{
	if (window && instance && instance->GetFactory() && device && mpDevice->GetD3DDevice() && mpDevice->GetD3DQueue())
	{
		HRESULT hr;
		IDXGIFactory2* dxgiFactory = instance->GetFactory();
		ID3D12Device* d3d12Device = mpDevice->GetD3DDevice();
		ID3D12CommandQueue* d3d12CommandQueue = mpDevice->GetD3DQueue();
		OSWindowData osWindowData = window->GetOSWindowData();

		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = window->GetClientArea().x;
		sd.Height = window->GetClientArea().y;
		sd.Format = Convert(mDesc.mFormat);
		sd.SampleDesc.Count = mDesc.mMultiSample.mCount;
		sd.SampleDesc.Quality = mDesc.mMultiSample.mQuality;
		sd.BufferUsage = 0; // Defaults to DXGI_USAGE_RENDER_TARGET_OUTPUT during creation.
		sd.BufferCount = mDesc.mBackBufferCount;
		sd.SwapEffect = Convert(mDesc.mSwapEffect);
		sd.Flags = 0; // DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

		IDXGISwapChain1* tempSwapChain;
		hr = dxgiFactory->CreateSwapChainForHwnd(d3d12CommandQueue, osWindowData.mHwnd, &sd, nullptr, nullptr, &tempSwapChain);
		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(tempSwapChain->QueryInterface(__uuidof(IDXGISwapChain), mpSwapChain.AsVoidPP())))
			{
				tempSwapChain->Release();

				if (mDesc.mAllowFullscreen)
					dxgiFactory->MakeWindowAssociation(osWindowData.mHwnd, 0);
				else
					dxgiFactory->MakeWindowAssociation(osWindowData.mHwnd, DXGI_MWA_NO_ALT_ENTER);
			}
		}
		
		// Create backbuffer views.
		mRenderTargets.resize(sd.BufferCount);
		mRenderTargetViews.resize(sd.BufferCount);
		for (UINT i = 0; i < sd.BufferCount; ++i)
		{
			mRenderTargetViews[i].Adopt(new ImageView(Move(mpDevice->GetRenderTargetViewDescriptors().Alloc())));
			ID3D12Resource* rt;
			mpSwapChain->GetBuffer(i, IID_PPV_ARGS(&rt));
			mRenderTargets[i].Adopt(new Image(rt));
			d3d12Device->CreateRenderTargetView(mRenderTargets[i].Cast<Image>()->GetResource(), nullptr, 
				mRenderTargetViews[i].Cast<ImageView>()->GetDescriptor()
				);
		}

#ifdef CPF_GFX_TRACKING
		std::stringstream str;
		str << dbgFilename << " : " << dbgLineNumber;
		mpSwapChain->SetPrivateData(WKPDID_D3DDebugObjectName, UINT(str.str().size() + 1), str.str().c_str());
#endif
	}
	CPF_LOG(D3D12, Info) << "Created swapchain: " << intptr_t(this) << " - " << intptr_t(mpSwapChain.Ptr());
}

SwapChain::~SwapChain()
{
	mRenderTargetViews.clear();
	mRenderTargets.clear();
	if (mpSwapChain)
		mpSwapChain->SetFullscreenState(FALSE, nullptr);
	CPF_LOG(D3D12, Info) << "Destroyed swapchain: " << intptr_t(this) << " - " << intptr_t(mpSwapChain.Ptr());
}

void SwapChain::Present()
{
	mpSwapChain->Present(0, 0 /* DXGI_PRESENT_ALLOW_TEARING */);
}

void SwapChain::Resize(int32_t x, int32_t y)
{
	// TODO: Validate that DXGI is taking care of resource synchronization.  Seems to be a safe bet but can't be sure.
	CPF_LOG(D3D12, Info) << "Resizing swap chain to: " << x << "x" << y;
	mRenderTargets.clear();
	mRenderTargetViews.clear();

	if (SUCCEEDED(mpSwapChain->ResizeBuffers(mDesc.mBackBufferCount, x, y, Convert(mDesc.mFormat), 0)))
	{
		CPF_LOG(D3D12, Info) << "Resizing swap chain succeeded";
		mRenderTargets.resize(mDesc.mBackBufferCount);
		mRenderTargetViews.resize(mDesc.mBackBufferCount);
		for (auto i = 0; i < mDesc.mBackBufferCount; ++i)
		{
			mRenderTargetViews[i].Adopt(new ImageView(Move(mpDevice->GetRenderTargetViewDescriptors().Alloc())));
			ID3D12Resource* rt;
			mpSwapChain->GetBuffer(i, IID_PPV_ARGS(&rt));
			mRenderTargets[i].Adopt(new Image(rt));
			mpDevice->GetD3DDevice()->CreateRenderTargetView(mRenderTargets[i].Cast<Image>()->GetResource(), nullptr, 
				mRenderTargetViews[i].Cast<ImageView>()->GetDescriptor()
				);
		}
	}
}

int32_t SwapChain::GetCurrentIndex()
{
	return mpSwapChain->GetCurrentBackBufferIndex();
}

Graphics::iImage* SwapChain::GetImage(int32_t index)
{
	return mRenderTargets[index];
}

Graphics::iImageView* SwapChain::GetImageView(int32_t index)
{
	return mRenderTargetViews[index];
}
