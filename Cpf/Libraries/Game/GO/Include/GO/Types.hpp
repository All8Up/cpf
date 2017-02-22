//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	namespace GO
	{
		using ObjectID = Hash::HashID<uint64_t, 4>;
		constexpr ObjectID kInvalidObjectID = ObjectID(uint64_t(-1));
		constexpr ObjectID kTransientID = ObjectID(uint64_t(0x8000000000000000));

		using ComponentID = Hash::HashID<uint64_t, 5>;
		constexpr ComponentID kInvalidComponentID = ComponentID(uint64_t(-1));

		class Object;
		class Component;
		class Manager;
	}
}
