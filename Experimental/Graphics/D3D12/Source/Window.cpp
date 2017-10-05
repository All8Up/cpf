//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "Graphics/ImageFlags.hpp"
#include "CPF/Logging.hpp"
#include "Math/Constants.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/HeapType.hpp"
#include "Graphics/ClearValue.hpp"
#include "Graphics/FrameBufferDesc.hpp"

using namespace CPF;

#define WINDOW_TITLE "Hello Triangle: " CPF_STRINGIZE(GFX_ADAPTER)

bool ExperimentalD3D12::_CreateWindow()
{
	//////////////////////////////////////////////////////////////////////////
	// Create the window.
	mpApplication->GetEmitter()->On<iApplication::OnQuit>([]() {
		CPF_LOG(Experimental, Info) << "**** Quit requested.";
		return true;
	});

	// Create the window.
	Math::Vector2i mWindowSize(1200, 800);
	WindowDesc windowDesc;
	windowDesc.mpTitle = WINDOW_TITLE;
	windowDesc.mX = iWindow::Centered();
	windowDesc.mY = iWindow::Centered();
	windowDesc.mWidth = mWindowSize.x;
	windowDesc.mHeight = mWindowSize.y;
	windowDesc.mFlags = WindowFlags::eResizable | WindowFlags::eShown;
	mpApplication->Create(&windowDesc, mpWindow.AsTypePP());

	if (mpWindow)
	{
		mpWindow->GetEmitter()->On<iWindow::OnResize>(Bind(&ExperimentalD3D12::_Resize, this, Placeholders::_1, Placeholders::_2));
		return true;
	}
	return false;
}

void ExperimentalD3D12::_Resize(int32_t x, int32_t y)
{
	if (mpSwapChain)
	{
		mFOV = Math::kDegToRad * 33.0f;
		float halfFov = tan(mFOV / 2.0f);
		mViewportSize = halfFov;

		mpSwapChain->Resize(x, y);

		// Recreate the depth buffers.
		mpDepthBuffer.Assign(nullptr);
		mpDepthBufferView.Assign(nullptr);
		Graphics::ImageDesc depthBufferDesc
		{
			x, y,
			1,
			1,
			Graphics::Format::eD32f,
			{ 1, 0 },
			Graphics::ResourceState::eCommon,
			Graphics::ImageFlags::eAllowDepthStencil
		};
		Graphics::ClearValue clearValue;
		clearValue.mFormat = Graphics::Format::eD32f;
		clearValue.mValue.mDepthStencil.mDepth = 1.0f;
		clearValue.mValue.mDepthStencil.mStencil = 0;
		mpDevice->CreateImage2D(Graphics::HeapType::eDefault, &depthBufferDesc, &clearValue, mpDepthBuffer.AsTypePP());
		mpDevice->CreateDepthStencilView(mpDepthBuffer, nullptr, mpDepthBufferView.AsTypePP());

		mpFrameBuffers.clear();
		mpFrameBuffers.resize(mBackBufferCount);
		for (int i = 0; i < mBackBufferCount; ++i)
		{
			Graphics::FrameBufferDesc frameBufferDesc;
			frameBufferDesc.mpRenderPass = mpRenderPass;
			frameBufferDesc.mAttachmentCount = 2;
			Graphics::ImageAndView images[2] =
			{
				{ mpSwapChain->GetImage(i), mpSwapChain->GetImageView(i) },
				{ mpDepthBuffer, mpDepthBufferView }
			};
			frameBufferDesc.mpAttachments = images;
			frameBufferDesc.mWidth = x;
			frameBufferDesc.mHeight = y;
			frameBufferDesc.mLayers = 1;

			mpDevice->CreateFrameBuffer(&frameBufferDesc, mpFrameBuffers[i].AsTypePP());
		}
	}
}
