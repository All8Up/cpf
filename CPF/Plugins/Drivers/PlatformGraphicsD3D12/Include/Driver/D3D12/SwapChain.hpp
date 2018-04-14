//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Platform/Graphics/iSwapChain.hpp"
#include "CPF/Platform/Graphics/SwapChainDesc.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "DescriptorManager.hpp"
#include <dxgi1_4.h>
#include <d3d12.h>


namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
		struct WindowData;
	}

	namespace Driver
	{
		namespace D3D12
		{
			struct Instance;

			class SwapChain final : public GOM::tUnknown<Graphics::iSwapChain>
			{
			public:
				SwapChain(Instance*, Graphics::iDevice*, const Graphics::WindowData*, int32_t w, int32_t h, const Graphics::SwapChainDesc* desc);
				virtual ~SwapChain();

				void Present() override;
				void Resize(int32_t x, int32_t y) override;
				int32_t GetCurrentIndex() override;
				Graphics::iImage* GetImage(int32_t index) override;
				Graphics::iImageView* GetImageView(int32_t index) override;

			private:
				Device* mpDevice;
				IntrusivePtr<IDXGISwapChain3> mpSwapChain;
				STD::Vector<IntrusivePtr<Graphics::iImage>> mRenderTargets;
				STD::Vector<IntrusivePtr<Graphics::iImageView>> mRenderTargetViews;
				Graphics::SwapChainDesc mDesc;
			};
		}
	}
}
