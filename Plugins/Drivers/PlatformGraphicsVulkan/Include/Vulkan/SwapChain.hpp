//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iSwapChain.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Std/Vector.hpp"
#include "Vulkan.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct WindowData;
	}

	namespace Vulkan
	{
		class Instance;
		class Device;

		class SwapChain final : public GOM::tUnknown<Graphics::iSwapChain>
		{
		public:
			// Overrides from iSwapChain.
			void CPF_STDCALL Present() override;
			void CPF_STDCALL Resize(int32_t x, int32_t y) override;
			int32_t CPF_STDCALL GetCurrentIndex() override;
			Graphics::iImage* CPF_STDCALL GetImage(int32_t index) override;
			Graphics::iImageView* CPF_STDCALL GetImageView(int32_t index) override;

			//
			GOM::Result Initialize(Instance* inst, Device* device, const Graphics::WindowData* wd, int32_t w, int32_t h, const Graphics::SwapChainDesc* scd);

		private:
			Device* mpDevice;

			VkSurfaceKHR mPresentationSurface;
			VkSwapchainKHR mSwapChain;
			STD::Vector<IntrusivePtr<Graphics::iImage>> mpImages;
			STD::Vector<IntrusivePtr<Graphics::iImageView>> mpImageViews;
			STD::Vector<VkFence> mFences;
			uint32_t mNextImage;

			VkQueue mSubmitQueue;
		};
	}
}
