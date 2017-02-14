//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Monitor.hpp"

namespace Cpf
{
	namespace Resources
	{
		namespace Monitors
		{
			class Manual : public tRefCounted<Monitor>
			{
			public:
				CPF_EXPORT_RESOURCES static Monitor* Create();

				bool Touch(ID) override;
				void TouchAll() override;

			private:
				Manual();
				~Manual() override;
			};
		}
	}
}
