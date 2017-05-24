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
			Python3(iBase*);
			virtual ~Python3();

			// iBase overrides.
			GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

			// iPython3 overrides.
			GOM::Result CPF_STDCALL Initialize(const char* basePath) override;
			GOM::Result CPF_STDCALL Shutdown() override;

		private:
			bool _InitPython();
		};
	}
}
