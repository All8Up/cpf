//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Configuration/Configuration.hpp>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

inline bool CheckExtensionAvailability(const char *extension_name, const std::vector<VkExtensionProperties> &available_extensions)
{
	for (size_t i = 0; i < available_extensions.size(); ++i)
	{
		if (strcmp(available_extensions[i].extensionName, extension_name) == 0)
		{
			return true;
		}
	}
	return false;
}
