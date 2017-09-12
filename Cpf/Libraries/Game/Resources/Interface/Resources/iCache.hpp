//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"
#include "Functional.hpp"

namespace CPF
{
	namespace Resources
	{
		struct ID;
		class ResourceBase;

		struct CacheDesc {};

		struct iCache : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iCache"_crc64);

			virtual ResourceBase* CPF_STDCALL Get(ID) const = 0;
			virtual void CPF_STDCALL Store(ID, ResourceBase*) = 0;
			virtual void CPF_STDCALL LastReference(ID) = 0;
			virtual void CPF_STDCALL Enumerate(Function<void(ResourceBase*)>) = 0;
		};
	}
}
