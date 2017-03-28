//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/Interfaces/iSwapChain.hpp"
#include "Vector.hpp"
#include "RefCounted.hpp"
#include "IntrusivePtr.hpp"
#include "DescriptorManager.hpp"
#include <dxgi1_4.h>
#include <d3d12.h>


namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		class iDevice;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Instance;

			class SwapChain : public tRefCounted<Graphics::iSwapChain>
			{
			public:
				SwapChain(Instance*, Graphics::iDevice*, iWindow*, const Graphics::SwapChainDesc* desc CPF_GFX_DEBUG_PARAM_DECL);
				~SwapChain() override;

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
