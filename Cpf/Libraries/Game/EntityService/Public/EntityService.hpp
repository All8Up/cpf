//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Export.hpp"
#include "Plugin/iRegistry.hpp"

namespace Cpf
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
