//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/Resource.hpp"
#include "RefCounted.hpp"


namespace Cpf
{
	namespace Resources
	{
		struct ID;
		class Locator;

		class Loader : public iRefCounted
		{
		public:
			virtual uint32_t GetID() const = 0;
			virtual ResourceBase* operator ()(ID id) const = 0;

		protected:
			virtual ~Loader() = 0;
		};
	}
}
