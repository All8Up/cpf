//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/HashID.hpp"
#include "MultiCore/Stage.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct entity_tag {};
		using EntityID = Hash::HashID<uint64_t, entity_tag>;
		constexpr EntityID kInvalidEntityID = EntityID(uint64_t(-1));
		constexpr EntityID kTransientID = EntityID(uint64_t(0x8000000000000000));

		struct component_tag {};
		using ComponentID = Hash::HashID<uint64_t, component_tag>;
		constexpr ComponentID kInvalidComponentID = ComponentID(uint64_t(-1));

		using SystmeID = MultiCore::SystemID;
		using StageID = MultiCore::StageID;
	}
}
