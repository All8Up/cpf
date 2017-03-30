//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct CPF_EXPORT iRegistry : iUnknown
		{
			static constexpr InterfaceID kIID = InterfaceID("iRegistry"_crc64);

			using Creator = void*(*)();

			virtual bool Install(InterfaceID, Creator) = 0;
			virtual bool Remove(InterfaceID) = 0;
			virtual bool Create(InterfaceID, void**) = 0;
		};
	}
}
