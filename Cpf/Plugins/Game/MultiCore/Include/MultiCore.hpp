//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin/iRegistry.hpp"
#include "Concurrency/iFence.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	//////////////////////////////////////////////////////////////////////////
	/// Initialize the multicore library.
	//////////////////////////////////////////////////////////////////////////
	struct MultiCoreInitializer
	{
		static int Install(Plugin::iRegistry*);
		static int Remove();

	private:
		MultiCoreInitializer() = delete;
		~MultiCoreInitializer() = delete;
	};
}

#ifdef CPF_STATIC_MULTICORE
#	define CPF_INIT_MULTICORE(reg, dir) ScopedInitializer<MultiCoreInitializer, int, Plugin::iRegistry*> multiCoreInit(reg);
#else
#	define CPF_INIT_MULTICORE(reg, dir) reg->Load(dir "/MultiCore.cfp");
#endif
