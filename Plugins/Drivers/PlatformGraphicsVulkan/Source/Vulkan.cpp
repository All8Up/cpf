//////////////////////////////////////////////////////////////////////////
#include "Vulkan.hpp"
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "Vulkan/Instance.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Platform/Graphics/ResourceUsage.hpp"

using namespace CPF;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{ Graphics::iInstance::kIID, Vulkan::kVulkanInstanceCID }
};


//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (GOM::Succeeded(registry->Install(Vulkan::kVulkanInstanceCID, new Plugin::tClassFactory<Vulkan::Instance>())) &&
			GOM::Succeeded(registry->ClassInstall(1, sImplementations)))
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->ClassRemove(1, sImplementations);
		registry->Remove(Vulkan::kVulkanInstanceCID);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(PlatformGraphicsVulkan)
	&Install,
	&Remove
};


//////////////////////////////////////////////////////////////////////////
using namespace Vulkan;

VkFormat Vulkan::ToVKFormat(Graphics::Format format)
{
	switch (format)
	{
	case Graphics::Format::eNone: return VK_FORMAT_UNDEFINED;
	case Graphics::Format::eR8: return VK_FORMAT_R8_UINT; // No Vulkan equivalent to typeless.
	case Graphics::Format::eR8u: return VK_FORMAT_R8_UINT;
	case Graphics::Format::eR8s: return VK_FORMAT_R8_SINT;
	case Graphics::Format::eR8un: return VK_FORMAT_R8_UNORM;
	case Graphics::Format::eR8sn: return VK_FORMAT_R8_SNORM;
	case Graphics::Format::eR16: return VK_FORMAT_R16_UINT;
	case Graphics::Format::eR16u: return VK_FORMAT_R16_UINT;
	case Graphics::Format::eR16s: return VK_FORMAT_R16_SINT;
	case Graphics::Format::eR16un: return VK_FORMAT_R16_UNORM;
	case Graphics::Format::eR16sn: return VK_FORMAT_R16_SNORM;
	case Graphics::Format::eR16f: return VK_FORMAT_R16_SFLOAT;
	case Graphics::Format::eR32: return VK_FORMAT_R32_UINT;
	case Graphics::Format::eR32u: return VK_FORMAT_R32_UINT;
	case Graphics::Format::eR32s: return VK_FORMAT_R32_SINT;
	case Graphics::Format::eR32f: return VK_FORMAT_R32_SFLOAT;
	case Graphics::Format::eRG8: return VK_FORMAT_R8G8_UINT; // No Vulkan equivalent to typeless.
	case Graphics::Format::eRG8u: return VK_FORMAT_R8G8_UINT;
	case Graphics::Format::eRG8s: return VK_FORMAT_R8G8_SINT;
	case Graphics::Format::eRG8un: return VK_FORMAT_R8G8_UNORM;
	case Graphics::Format::eRG8sn: return VK_FORMAT_R8G8_SNORM;
	case Graphics::Format::eRG16: return VK_FORMAT_R16G16_UINT;
	case Graphics::Format::eRG16u: return VK_FORMAT_R16G16_UINT;
	case Graphics::Format::eRG16s: return VK_FORMAT_R16G16_SINT;
	case Graphics::Format::eRG16un: return VK_FORMAT_R16G16_UNORM;
	case Graphics::Format::eRG16sn: return VK_FORMAT_R16G16_SNORM;
	case Graphics::Format::eRG16f: return VK_FORMAT_R16G16_SFLOAT;
	case Graphics::Format::eRG32: return VK_FORMAT_R32G32_UINT;
	case Graphics::Format::eRG32u: return VK_FORMAT_R32G32_UINT;
	case Graphics::Format::eRG32s: return VK_FORMAT_R32G32_SINT;
	case Graphics::Format::eRG32f: return VK_FORMAT_R32G32_SFLOAT;
	case Graphics::Format::eRGB32: return VK_FORMAT_R32G32B32_UINT;
	case Graphics::Format::eRGB32u: return VK_FORMAT_R32G32B32_UINT;
	case Graphics::Format::eRGB32s: return VK_FORMAT_R32G32B32_SINT;
	case Graphics::Format::eRGB32f: return VK_FORMAT_R32G32B32_SFLOAT;
	case Graphics::Format::eRGBA8: return VK_FORMAT_R8G8B8A8_UINT; // No Vulkan equivalent to typeless.
	case Graphics::Format::eRGBA8u: return VK_FORMAT_R8G8B8A8_UINT;
	case Graphics::Format::eRGBA8s: return VK_FORMAT_R8G8B8A8_SINT;
	case Graphics::Format::eRGBA8un: return VK_FORMAT_R8G8B8A8_UNORM;
	case Graphics::Format::eRGBA8sn: return VK_FORMAT_R8G8B8A8_SNORM;
	case Graphics::Format::eRGBA16: return VK_FORMAT_R16G16B16A16_UINT;
	case Graphics::Format::eRGBA16u: return VK_FORMAT_R16G16B16A16_UINT;
	case Graphics::Format::eRGBA16s: return VK_FORMAT_R16G16B16A16_SINT;
	case Graphics::Format::eRGBA16un: return VK_FORMAT_R16G16B16A16_UNORM;
	case Graphics::Format::eRGBA16sn: return VK_FORMAT_R16G16B16A16_SNORM;
	case Graphics::Format::eRGBA16f: return VK_FORMAT_R16G16B16A16_SFLOAT;
	case Graphics::Format::eRGBA32: return VK_FORMAT_R32G32B32A32_UINT;
	case Graphics::Format::eRGBA32u: return VK_FORMAT_R32G32B32A32_UINT;
	case Graphics::Format::eRGBA32s: return VK_FORMAT_R32G32B32A32_SINT;
	case Graphics::Format::eRGBA32f: return VK_FORMAT_R32G32B32A32_SFLOAT;
	case Graphics::Format::eBGRA8: return VK_FORMAT_B8G8R8A8_UINT;
	case Graphics::Format::eBGRA8un: return VK_FORMAT_B8G8R8A8_UNORM;
	case Graphics::Format::eD32f: return VK_FORMAT_D32_SFLOAT;
	case Graphics::Format::eR24G8: return VK_FORMAT_D24_UNORM_S8_UINT; // ??
	case Graphics::Format::eD24unS8u: return VK_FORMAT_D24_UNORM_S8_UINT;
	default:
		CPF_ASSERT_ALWAYS;
	}

	return VK_FORMAT_UNDEFINED;
}

VkImageLayout Vulkan::ToVkImageLayout(Graphics::ResourceState state)
{
	switch (state)
	{
	case Graphics::ResourceState::eCommon: /* | Graphics::ResourceState::ePresent */
		return VK_IMAGE_LAYOUT_GENERAL;
	case Graphics::ResourceState::eVertexAndConstant:
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	case Graphics::ResourceState::eIndex:
	case Graphics::ResourceState::eRenderTarget:
		// Vulkan does not have 'render targets', instead Vulkan handles the transitions itself within the renderpass infrastructure.
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	case Graphics::ResourceState::eUnorderedAccess:
	case Graphics::ResourceState::eDepthWrite:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	case Graphics::ResourceState::eDepthRead:
	case Graphics::ResourceState::eNonPixelShaderResource:
	case Graphics::ResourceState::ePixelShaderResource:
	case Graphics::ResourceState::eStreamOut:
	case Graphics::ResourceState::eIndirectArgument: /* | case Graphics::ResourceState::ePredication */
	case Graphics::ResourceState::eCopyDest:
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	case Graphics::ResourceState::eCopySource:
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	case Graphics::ResourceState::eResolveDest:
	case Graphics::ResourceState::eResolveSource:
	case Graphics::ResourceState::eGenericRead:

	case Graphics::ResourceState::ePresent:
		return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	case Graphics::ResourceState::eUndefined:
		return VK_IMAGE_LAYOUT_UNDEFINED;
		
		/*
		VK_IMAGE_LAYOUT_GENERAL = 1,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = 2,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = 5,
		VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = 6,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = 7,
		VK_IMAGE_LAYOUT_PREINITIALIZED = 8,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR = 1000001002,
		VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR = 1000111000,
		VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR = 1000117000,
		VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR = 1000117001,
		VK_IMAGE_LAYOUT_BEGIN_RANGE = VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_END_RANGE = VK_IMAGE_LAYOUT_PREINITIALIZED,
		VK_IMAGE_LAYOUT_RANGE_SIZE = (VK_IMAGE_LAYOUT_PREINITIALIZED - VK_IMAGE_LAYOUT_UNDEFINED + 1),
		*/
	default:
		CPF_ASSERT_ALWAYS;
	}
	return VK_IMAGE_LAYOUT_UNDEFINED;
}

VkPipelineBindPoint Vulkan::ToVkPipelineBindPoint(Graphics::PipelineBindPoint bindPoint)
{
	switch (bindPoint)
	{
	case Graphics::PipelineBindPoint::eGraphic: return VK_PIPELINE_BIND_POINT_GRAPHICS;
	case Graphics::PipelineBindPoint::eCompute: return VK_PIPELINE_BIND_POINT_COMPUTE;
	default:
		CPF_ASSERT_ALWAYS;
	}
	return VK_PIPELINE_BIND_POINT_MAX_ENUM;
}
