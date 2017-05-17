//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iPython.hpp"

namespace Cpf
{
	namespace Tools
	{
		class Python3 : public tRefCounted<iPython3>
		{
		public:
			Python3(iUnknown*);
			virtual ~Python3();

			// iUnknown overrides.
			GOM::Result CPF_STDCALL QueryInterface(GOM::InterfaceID id, void** outIface) override;

			// iPython3 overrides.
			GOM::Result CPF_STDCALL Initialize(const char* basePath) override;
			GOM::Result CPF_STDCALL Shutdown() override;
		};
	}
}
