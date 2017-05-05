//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Logging/Logging.hpp"
#include "Math/Constants.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/Format.hpp"

using namespace Cpf;

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
			Graphics::ImageFlags::eAllowDepthStencil
		};
		mpDevice->CreateImage2D(&depthBufferDesc, nullptr, mpDepthBuffer.AsTypePP());
		mpDevice->CreateDepthStencilView(mpDepthBuffer, nullptr, mpDepthBufferView.AsTypePP());
	}
}
