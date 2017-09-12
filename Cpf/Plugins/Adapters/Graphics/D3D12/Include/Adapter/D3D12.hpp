//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Plugin/iRegistry.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ADAPTER_D3D12
#		define CPF_EXPORT_ADAPTER_D3D12
#	else
#		if CPF_STATIC_ADAPTER_D3D12
#			define CPF_EXPORT_ADAPTER_D3D12 CPF_EXPORT
#		else
#			define CPF_EXPORT_ADAPTER_D3D12 CPF_IMPORT
#		endif
#	endif
#else
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ADAPTER_D3D12 CPF_EXPORT
#	else
#		define CPF_EXPORT_ADAPTER_D3D12
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace Adapter
	{
		struct D3D12Initializer
		{
			static int Install(Plugin::iRegistry* regy);
			static int Remove();

		private:
			D3D12Initializer() = delete;
			~D3D12Initializer() = delete;
		};
	}
}
