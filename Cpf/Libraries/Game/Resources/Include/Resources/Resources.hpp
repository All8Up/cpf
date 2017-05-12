//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Plugin/iRegistry.hpp"
#include "rapidjson/document.h"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Resources
	{
		struct ResourcesInitializer
		{
			static int Install(Plugin::iRegistry*);
			static int Remove(Plugin::iRegistry*);

		private:
			ResourcesInitializer() = delete;
			~ResourcesInitializer() = delete;
		};
	}
}
