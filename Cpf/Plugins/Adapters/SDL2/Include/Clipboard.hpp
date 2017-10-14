//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iClipboard.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace SDL2
	{
		class Clipboard : public tRefCounted<iClipboard>
		{
		public:
			Clipboard(Plugin::iRegistry*, GOM::iUnknown*);
			virtual ~Clipboard();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) override;
			GOM::Result CPF_STDCALL SetClipboardText(const char*) override;
		};
	}
}
