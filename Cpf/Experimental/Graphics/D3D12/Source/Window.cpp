//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
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
	GetEmitter()->On<OnQuit>([]() {
		CPF_LOG(Experimental, Info) << "**** Quit requested.";
		return true;
	});

	// Create the window.
	Math::Vector2i mWindowSize(1920, 1080);
	mpWindow.Adopt(
		WindowDesc(this)
		.Title(WINDOW_TITLE)
		.Position({ iWindow::Centered(), iWindow::Centered() })
		.Size(mWindowSize)
		.Flags(WindowFlags::eResizable | WindowFlags::eShown)
	);

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
		// TODO: There should only be a single depth buffer.
		mpDepthBufferImages.clear();
		mpDepthBufferImageViews.clear();
		mpDepthBufferImages.resize(mBackBufferCount);
		mpDepthBufferImageViews.resize(mBackBufferCount);
		Graphics::ImageDesc depthBufferDesc
		{
			x, y,
			1,
			1,
			Graphics::Format::eD32f,
			{ 1, 0 },
			Graphics::ImageFlags::eAllowDepthStencil
		};
		for (int i = 0; i < mBackBufferCount; ++i)
		{
			mpDevice->CreateImage2D(&depthBufferDesc, nullptr, mpDepthBufferImages[i].AsTypePP());
			mpDevice->CreateDepthStencilView(mpDepthBufferImages[i], nullptr, mpDepthBufferImageViews[i].AsTypePP());
		}
	}
}
