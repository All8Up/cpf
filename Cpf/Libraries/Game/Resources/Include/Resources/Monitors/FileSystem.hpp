//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Monitor.hpp"

namespace Cpf
{
	namespace Resources
	{
		namespace Monitors
		{
			class FileSystem : public tRefCounted<Monitor>
			{
			public:
				CPF_EXPORT_RESOURCES static Monitor* Create();

				bool Touch(ID) override;
				void TouchAll() override;

			private:
				FileSystem();
				~FileSystem() override;
			};
		}
	}
}