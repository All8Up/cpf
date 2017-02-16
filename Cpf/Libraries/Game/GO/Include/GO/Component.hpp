//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Export.hpp"
#include "RefCount.hpp"
#include "Types.hpp"
#include "Hash/Crc.hpp"

namespace Cpf
{
	namespace GO
	{
		class Component : public tRefCounted<iRefCounted>
		{
		public:
			Component() : mpObject(nullptr) {}
			virtual ~Component() {}

			// Component interface.
			Object* GetObject() const { return mpObject; }

			virtual ComponentID GetID() const = 0;

			virtual void Initialize() {}
			virtual void Shutdown() {}

			virtual void Activate() {}
			virtual void Deactivate() {}

		private:
			friend class Object;
			void SetObject(Object* object) { mpObject = object; }

			Object* mpObject;
		};
	}
}
