//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Graphics;

bool ExperimentalD3D12::_SelectAdapter(Graphics::iInstance* instance, iAdapter** outAdapter)
{
	//////////////////////////////////////////////////////////////////////////
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	instance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IntrusivePtr<iAdapter>> adapters;
	adapters.resize(adapterCount);
	instance->EnumerateAdapters(adapterCount, adapters[0].AsTypePP());

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
		*outAdapter = adapters[bestAdapter];
		(*outAdapter)->AddRef();
		break;
	}
	CPF_LOG(Experimental, Info) << "Chosen Adapter: " << adapters[bestAdapter]->GetDescription();

	return bestAdapter != -1;
}

bool ExperimentalD3D12::_EnumerateOutputs(iAdapter* adapter)
{
	//////////////////////////////////////////////////////////////////////////
	// Enumerate the outputs attached to the adapter.
	int32_t outputCount = 0;
	adapter->EnumerateOutputs(outputCount, nullptr);

	Vector<IntrusivePtr<iOutput>> outputs;
	outputs.resize(outputCount);
	adapter->EnumerateOutputs(outputCount, outputs[0].AsTypePP());

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

	// Nothing to fail on right now.
	return true;
}

bool ExperimentalD3D12::_CreateSwapChain(iInstance* instance)
{
	// Create the swapchain attached to the window.
	SwapChainDesc desc{
		Format::eRGBA8un,
		SwapEffect::eFlipDiscard,
		{ 1, 0 },
		mBackBufferCount,
		true
	};
	mpDevice->CreateSwapChain(instance, mpWindow, &desc, mpSwapChain.AsTypePP() CPF_GFX_DEBUG_PARAMS);

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

	return mpSwapChain;
}
