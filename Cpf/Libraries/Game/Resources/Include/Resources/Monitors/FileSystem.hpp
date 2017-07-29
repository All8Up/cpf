//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/iMonitor.hpp"

namespace Cpf
{
	namespace Resources
	{
		namespace Monitors
		{
			class FileSystem : public tRefCounted<iMonitor>
			{
			public:
				FileSystem(iUnknown*);
				~FileSystem() override;

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				bool CPF_STDCALL Touch(ID) override;
				void CPF_STDCALL TouchAll() override;

				void CPF_STDCALL SetLocator(iLocator* locator) override { mpLocator.Adopt(locator); }
				iLocator* CPF_STDCALL GetLocator() const override { return mpLocator; }

			private:
				IntrusivePtr<iLocator> mpLocator;
			};
		}
	}
}
