//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace GO
	{
		using ObjectID = int64_t;
		constexpr ObjectID kInvalidObjectID = int64_t(-1);

		using ComponentID = int64_t;
		constexpr ComponentID kInvalidComponentID = int64_t(-1);

		using SystemID = int64_t;
		constexpr ComponentID kInvalidSystemID = int64_t(-1);

		class Object;
		class Component;
		class Service;
		class System;
	}
}
