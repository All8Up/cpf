//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/iMonitor.hpp"
#include "Resources/Resources.hpp"

namespace CPF
{
	namespace Resources
	{
		namespace Monitors
		{
			class Manual : public tRefCounted<iMonitor>
			{
			public:
				Manual(Plugin::iRegistry*, iUnknown*);
				virtual ~Manual();

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
