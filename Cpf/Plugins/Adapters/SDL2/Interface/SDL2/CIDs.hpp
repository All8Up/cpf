//////////////////////////////////////////////////////////////////////////
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace SDL2
	{
		static constexpr COM::ClassID kWindowCID = COM::ClassID("Cpf::SDL2::iWindow"_crc64);
		static constexpr COM::ClassID kWindowedApplicationCID = COM::ClassID("Cpf::SDL2::iWindowedApplication"_crc64);
		static constexpr COM::ClassID kClipboardCID = COM::ClassID("Cpf::SDL2::iClipboard"_crc64);
		static constexpr COM::ClassID kInputManagerCID = COM::ClassID("Cpf::SDL2::iInputManager"_crc64);
		static constexpr COM::ClassID kMouseDeviceCID = COM::ClassID("Cpf::SDL2::iMouseDevice"_crc64);
		static constexpr COM::ClassID kKeyboardDeviceCID = COM::ClassID("Cpf::SDL2::iKeyboardDevice"_crc64);
	}
}
