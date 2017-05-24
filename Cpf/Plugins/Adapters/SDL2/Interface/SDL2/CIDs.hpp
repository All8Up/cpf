//////////////////////////////////////////////////////////////////////////
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace SDL2
	{
		static constexpr GOM::ClassID kWindowCID = GOM::ClassID("Cpf::SDL2::iWindow"_crc64);
		static constexpr GOM::ClassID kWindowedApplicationCID = GOM::ClassID("Cpf::SDL2::iWindowedApplication"_crc64);
		static constexpr GOM::ClassID kClipboardCID = GOM::ClassID("Cpf::SDL2::iClipboard"_crc64);
		static constexpr GOM::ClassID kInputManagerCID = GOM::ClassID("Cpf::SDL2::iInputManager"_crc64);
		static constexpr GOM::ClassID kMouseDeviceCID = GOM::ClassID("Cpf::SDL2::iMouseDevice"_crc64);
		static constexpr GOM::ClassID kKeyboardDeviceCID = GOM::ClassID("Cpf::SDL2::iKeyboardDevice"_crc64);
	}
}
