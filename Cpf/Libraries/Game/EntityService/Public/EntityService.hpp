//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Export.hpp"

namespace Cpf
{
	struct EntityServiceInitializer
	{
		CPF_EXPORT_ENTITYSERVICE static int Install();
		CPF_EXPORT_ENTITYSERVICE static int Remove();

	private:
		EntityServiceInitializer() = delete;
		~EntityServiceInitializer() = delete;
	};
}
