//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iClipboard.hpp"

namespace Cpf
{
	namespace SDL2
	{
		class Clipboard : public tRefCounted<iClipboard>
		{
		public:
			Clipboard(GOM::iBase*);
			virtual ~Clipboard();

			GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

			GOM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) override;
			GOM::Result CPF_STDCALL SetClipboardText(const char*) override;
		};
	}
}
