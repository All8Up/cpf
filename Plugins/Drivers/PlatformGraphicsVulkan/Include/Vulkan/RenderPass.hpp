//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iRenderPass.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct RenderPassDesc;
	}
	namespace Vulkan
	{
		class Device;

		class RenderPass final : public GOM::tUnknown <Graphics::iRenderPass>
		{
		public:
			RenderPass();

			GOM::Result Initialize(Device* device, const Graphics::RenderPassDesc*);

			VkRenderPass GetVkRenderPass() const { return mRenderPass; }

		private:
			VkRenderPass mRenderPass;
		};
	}
}
