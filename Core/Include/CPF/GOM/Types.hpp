//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Hash/HashID.hpp"

namespace CPF
{
	namespace GOM
	{
		using ClassID = Hash::HashID<uint64_t, struct class_tag>;
		using InterfaceID = Hash::HashID<uint64_t, struct interface_tag>;
	}
}
