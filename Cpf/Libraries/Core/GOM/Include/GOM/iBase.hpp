//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "GOM/Result.hpp"

namespace Cpf
{
	namespace GOM
	{
		struct class_tag;
		using ClassID = Hash::HashID<uint64_t, class_tag>;
		struct interface_tag;
		using InterfaceID = Hash::HashID<uint64_t, interface_tag>;
		struct instance_tag;
		using InstanceID = Hash::HashID<uint64_t, instance_tag>;

		//////////////////////////////////////////////////////////////////////////
		struct iBase : iRefCounted
		{
			static constexpr InterfaceID kIID = InterfaceID("Cpf::GOM::iBase"_crc64);

			virtual Result CPF_STDCALL Cast(InterfaceID id, void** outIface) = 0;
		};
	}
}
