//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Graphics/iOutput.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Graphics/OutputDesc.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/ModeRotation.hpp"
#include "Graphics/EnumMode.hpp"
#include "Graphics/ModeDesc.hpp"
#include "Graphics/SwapChainDesc.hpp"
#include "Graphics/SwapEffect.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/iImageView.hpp"
#include "Graphics/WindowData.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/RenderPassDesc.hpp"
#include "Graphics/HeapType.hpp"
#include "Graphics/ClearValue.hpp"
#include "Application/OSWindowData.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Graphics;

bool ExperimentalD3D12::_SelectAdapter(Graphics::iInstance* instance, iAdapter** outAdapter)
{
	//////////////////////////////////////////////////////////////////////////
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	instance->EnumerateAdapters(&adapterCount, nullptr);
	Vector<IntrusivePtr<iAdapter>> adapters;
	adapters.resize(adapterCount);
	instance->EnumerateAdapters(&adapterCount, adapters[0].AsTypePP());

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
	adapter->EnumerateOutputs(&outputCount, nullptr);

	Vector<IntrusivePtr<iOutput>> outputs;
	outputs.resize(outputCount);
	adapter->EnumerateOutputs(&outputCount, outputs[0].AsTypePP());

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
			output->EnumerateModes(Format::eRGBA8un, EnumMode::eNone, &modeCount, nullptr);
			Vector<ModeDesc> modeDescs;
			modeDescs.resize(modeCount);
			output->EnumerateModes(Format::eRGBA8un, EnumMode::eNone, &modeCount, modeDescs.data());

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

#include "Graphics/FrameBufferDesc.hpp"
bool ExperimentalD3D12::_CreateSwapChain(iInstance* instance)
{
	//////////////////////////////////////////////////////////////////////////
	// Create a renderpass if it doesn't already exist.
	// TODO: This is a lazy hack...
	if (!mpRenderPass)
	{
		AttachmentDesc attachments[2] = {};

		//////////////////////////////////////////////////////////////////////////
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

		///
		AttachmentRef colorAttachment;
		colorAttachment.mIndex = 0;
		colorAttachment.mState = ResourceState::eRenderTarget;

		//////////////////////////////////////////////////////////////////////////
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

		///
		AttachmentRef depthAttachment;
		depthAttachment.mIndex = 1;
		depthAttachment.mState = ResourceState::eDepthWrite;

		//////////////////////////////////////////////////////////////////////////
		// Standard render to swap chain.
		SubPassDesc subPass;
		subPass.mBindPoint = PipelineBindPoint::eGraphic;
		// No inputs.
		subPass.mInputCount = 0;
		subPass.mpInputAttachments = nullptr;
		// 1 color output.
		subPass.mAttachmentCount = 1;
		subPass.mpColorAttachments = &colorAttachment;
		// No resolves.
		subPass.mpResolveAttachments = nullptr;
		// 1 depth buffer.
		subPass.mpDepthStencilAttachment = &depthAttachment;
		// No preservation.
		subPass.mPreserveCount = 0;
		subPass.mpPreserveAttachments = nullptr;

		//////////////////////////////////////////////////////////////////////////
		RenderPassDesc renderPassDesc;
		renderPassDesc.mAttachmentCount = 2;
		renderPassDesc.mpAttachments = attachments;
		renderPassDesc.mSubPassCount = 1;
		renderPassDesc.mpSubPasses = &subPass;
		renderPassDesc.mDependencyCount = 0;
		renderPassDesc.mpDependencies = nullptr;

		mpDevice->CreateRenderPass(&renderPassDesc, mpRenderPass.AsTypePP());
	}
	//////////////////////////////////////////////////////////////////////////

	// Create the swapchain attached to the window.
	SwapChainDesc desc{
		Format::eRGBA8un,
		SwapEffect::eFlipDiscard,
		{ 1, 0 },
		mBackBufferCount,
		true
	};
	WindowData winData;
	OSWindowData osData;
	mpWindow->GetOSData(&osData);
	winData.mHWnd = osData.mHwnd;
	int32_t w, h;
	mpWindow->GetClientAreaSize(&w, &h);
	mpDevice->CreateSwapChain(instance, &winData, w, h, &desc, mpSwapChain.AsTypePP());

	// Create a depth buffer for rendering.
	mpDepthBuffer.Assign(nullptr);
	mpDepthBufferView.Assign(nullptr);
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
	mpDevice->CreateImage2D(Graphics::HeapType::eDefault, &depthBufferDesc, &clearValue, mpDepthBuffer.AsTypePP());
	mpDevice->CreateDepthStencilView(mpDepthBuffer, nullptr, mpDepthBufferView.AsTypePP());

	// Make a frame buffer for each target in the swap chain.
	mpFrameBuffers.clear();
	mpFrameBuffers.resize(mBackBufferCount);
	for (int i=0; i<mBackBufferCount; ++i)
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

	return mpSwapChain;
}
