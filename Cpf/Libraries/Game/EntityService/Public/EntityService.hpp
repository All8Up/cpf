//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Export.hpp"
#include "Plugin/iRegistry.hpp"

namespace Cpf
{
	struct EntityServiceInitializer
	{
		CPF_EXPORT_ENTITYSERVICE static int Install(Plugin::iRegistry* registry);
		CPF_EXPORT_ENTITYSERVICE static int Remove();

	private:
		EntityServiceInitializer() = delete;
		~EntityServiceInitializer() = delete;
	};
}
