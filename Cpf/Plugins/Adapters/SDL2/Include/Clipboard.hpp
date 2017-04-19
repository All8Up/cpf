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
			Clipboard(COM::iUnknown*);
			virtual ~Clipboard();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			COM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) override;
			COM::Result CPF_STDCALL SetClipboardText(const char*) override;
		};
	}
}
