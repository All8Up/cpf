//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "Types.hpp"

namespace Cpf
{
	namespace GO
	{
		class iComponent : public iUnknown
		{
		public:
			static constexpr auto kIID = InterfaceID("iComponent Interface"_crc64);

			virtual ComponentID GetID() const = 0;

			virtual iEntity* GetOwner() const = 0;

			virtual void Initialize() = 0;
			virtual void Shutdown() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;

			virtual void SetObject(iEntity* object) = 0;
		};
	}
}
