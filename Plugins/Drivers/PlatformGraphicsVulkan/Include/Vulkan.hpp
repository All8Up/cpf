//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

namespace CPF
{
	namespace Graphics
	{
		enum class PipelineBindPoint : int32_t;
		enum class ResourceState : int32_t;
		enum class Format : int32_t;
	}

	namespace Vulkan
	{
		VkFormat ToVKFormat(Graphics::Format format);
		VkImageLayout ToVkImageLayout(Graphics::ResourceState state);
		VkPipelineBindPoint ToVkPipelineBindPoint(Graphics::PipelineBindPoint bindPoint);
	}
}
