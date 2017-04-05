//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "Plugin/iRegistry.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	//////////////////////////////////////////////////////////////////////////
	/// Initialize the multicore library.
	//////////////////////////////////////////////////////////////////////////
	struct MultiCoreInitializer
	{
		CPF_EXPORT_MULTICORE static int Install(Plugin::iRegistry*);
		CPF_EXPORT_MULTICORE static int Remove();

	private:
		MultiCoreInitializer() = delete;
		~MultiCoreInitializer() = delete;
	};
}

#ifdef CPF_STATIC_MULTICORE
#	define CPF_INIT_MULTICORE(reg, dir) ScopedInitializer<MultiCoreInitializer, Plugin::iRegistry*> multiCoreInit(reg);
#else
#	define CPF_INIT_MULTICORE(reg, dir) reg->Load(dir "/MultiCore.cfp");
#endif
