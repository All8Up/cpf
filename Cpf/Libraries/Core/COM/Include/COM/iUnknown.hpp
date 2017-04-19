//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "COM/Result.hpp"

namespace Cpf
{
	namespace COM
	{
		struct class_tag;
		using ClassID = Hash::HashID<uint64_t, class_tag>;
		struct interface_tag;
		using InterfaceID = Hash::HashID<uint64_t, interface_tag>;
		struct instance_tag;
		using InstanceID = Hash::HashID<uint64_t, instance_tag>;

		//////////////////////////////////////////////////////////////////////////
		struct iUnknown : iRefCounted
		{
			static constexpr InterfaceID kIID = InterfaceID("iUnknown Interface"_crc64);

			virtual Result CPF_STDCALL QueryInterface(InterfaceID id, void** outIface) = 0;
		};
	}
}
