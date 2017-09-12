//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iClipboard.hpp"

namespace CPF
{
	namespace SDL2
	{
		class Clipboard : public tRefCounted<iClipboard>
		{
		public:
			Clipboard(GOM::iUnknown*);
			virtual ~Clipboard();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) override;
			GOM::Result CPF_STDCALL SetClipboardText(const char*) override;
		};
	}
}
