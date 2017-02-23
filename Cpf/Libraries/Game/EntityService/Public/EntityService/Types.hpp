//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	namespace EntityService
	{
		using EntityID = Hash::HashID<uint64_t, 1>;
		constexpr EntityID kInvalidEntityID = EntityID(uint64_t(-1));
		constexpr EntityID kTransientID = EntityID(uint64_t(0x8000000000000000));

		using ComponentID = Hash::HashID<uint64_t, 5>;
		constexpr ComponentID kInvalidComponentID = ComponentID(uint64_t(-1));

		struct iEntity;
		struct iComponent;
		struct iEntityService;
	}
}
