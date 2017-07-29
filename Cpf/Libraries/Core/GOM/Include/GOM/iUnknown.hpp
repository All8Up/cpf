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

		static_assert(sizeof(ClassID) == sizeof(uint64_t), "Size is incorrect.");
		static_assert(sizeof(InterfaceID) == sizeof(uint64_t), "Size is incorrect.");

		//////////////////////////////////////////////////////////////////////////
		struct iUnknown
		{
			static constexpr InterfaceID kIID = InterfaceID("Cpf::GOM::iUnknown"_crc64);

			virtual int32_t CPF_STDCALL AddRef() = 0;
			virtual int32_t CPF_STDCALL Release() = 0;
			virtual Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) = 0;
		};
	}
}
