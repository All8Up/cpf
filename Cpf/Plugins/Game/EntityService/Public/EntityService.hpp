//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Export.hpp"
#include "Plugin/iRegistry.hpp"

namespace CPF
{
	struct EntityServiceInitializer
	{
		static int Install(Plugin::iRegistry* registry);
		static int Remove();

	private:
		EntityServiceInitializer() = delete;
		~EntityServiceInitializer() = delete;
	};
}

#ifdef CPF_STATIC_ENTITYSERVICE
#	define CPF_INIT_ENTITYSERVICE(reg, dir) ScopedInitializer<EntityServiceInitializer, int, Plugin::iRegistry*> entityServiceInit(reg);
#else
#	define CPF_INIT_ENTITYSERVICE(reg, dir) reg->Load(dir "/EntityService.cfp");
#endif
