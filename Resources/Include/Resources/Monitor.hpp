//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Resources
	{
		struct ID;
		class Locator;

		class Monitor : public iRefCounted
		{
		public:
			virtual bool Touch(ID) = 0;
			virtual void TouchAll() = 0;

			void SetLocator(Locator*);
			Locator* GetLocator() const;

		protected:
			Monitor();
			virtual ~Monitor() = 0;

		private:
			Locator* mpLocator;
		};
	}
}
