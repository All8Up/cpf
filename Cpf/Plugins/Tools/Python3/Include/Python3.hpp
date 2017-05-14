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
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			// iPython3 overrides.
			COM::Result CPF_STDCALL Initialize(const char* basePath) override;
			COM::Result CPF_STDCALL Shutdown() override;
		};
	}
}
