//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "Graphics/iSwapChain.hpp"
#include "Graphics/SwapChainDesc.hpp"
#include "Vector.hpp"
#include "RefCounted.hpp"
#include "IntrusivePtr.hpp"
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

	namespace Adapter
	{
		namespace D3D12
		{
			struct Instance;

			class SwapChain : public tRefCounted<Graphics::iSwapChain>
			{
			public:
				SwapChain(Instance*, Graphics::iDevice*, const Graphics::WindowData*, int32_t w, int32_t h, const Graphics::SwapChainDesc* desc);
				virtual ~SwapChain();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				void Present() override;
				void Resize(int32_t x, int32_t y) override;
				int32_t GetCurrentIndex() override;
				Graphics::iImage* GetImage(int32_t index) override;
				Graphics::iImageView* GetImageView(int32_t index) override;

			private:
				Device* mpDevice;
				IntrusivePtr<IDXGISwapChain3> mpSwapChain;
				Vector<IntrusivePtr<Graphics::iImage>> mRenderTargets;
				Vector<IntrusivePtr<Graphics::iImageView>> mRenderTargetViews;
				Graphics::SwapChainDesc mDesc;
			};
		}
	}
}
