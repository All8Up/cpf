//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ADAPTERS_D3D12
#		define CPF_EXPORT_ADAPTERS_D3D12
#	else
#		if CPF_STATIC_ADAPTERS_D3D12
#			define CPF_EXPORT_ADAPTERS_D3D12 CPF_EXPORT
#		else
#			define CPF_EXPORT_ADAPTERS_D3D12 CPF_IMPORT
#		endif
#	endif
#else
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ADAPTERS_D3D12 CPF_EXPORT
#	else
#		define CPF_EXPORT_ADAPTERS_D3D12
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Adapters
	{
		struct D3D12Initializer
		{
			CPF_EXPORT_ADAPTERS_D3D12 static int Install();
			CPF_EXPORT_ADAPTERS_D3D12 static int Remove();

		private:
			D3D12Initializer() = delete;
			~D3D12Initializer() = delete;
		};
	}
}
