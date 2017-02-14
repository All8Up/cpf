//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ADAPTERS_VULKAN
#		define CPF_EXPORT_ADAPTERS_VULKAN
#	else
#		if CPF_STATIC_ADAPTERS_D3D12
#			define CPF_EXPORT_ADAPTERS_VULKAN CPF_EXPORT
#		else
#			define CPF_EXPORT_ADAPTERS_VULKAN CPF_IMPORT
#		endif
#	endif
#else
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ADAPTERS_VULKAN CPF_EXPORT
#	else
#		define CPF_EXPORT_ADAPTERS_VULKAN
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Adapters
	{
		struct VulkanInitializer
		{
			CPF_EXPORT_ADAPTERS_VULKAN static int Install();
			CPF_EXPORT_ADAPTERS_VULKAN static int Remove();

		private:
			VulkanInitializer() = delete;
			~VulkanInitializer() = delete;
		};
	}
}
