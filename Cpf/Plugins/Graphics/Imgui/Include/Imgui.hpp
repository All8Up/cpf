//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Game
	{
		static constexpr COM::ClassID kBGFX_ImguiCID = COM::ClassID("BGFX_Imgui"_crc64);

		struct iImgui : public COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iImgui"_crc64);

			virtual COM::Result CPF_STDCALL Initialize() = 0;
			virtual void CPF_STDCALL BeginFrame(int32_t width, int32_t height) = 0;
			virtual void CPF_STDCALL EndFrame() = 0;

			virtual bool CPF_STDCALL BeginScrollArea(const char* name, int32_t x, int32_t y, int32_t w, int32_t h, int* scroll) = 0;
			virtual void CPF_STDCALL EndScrollArea() = 0;
			virtual void CPF_STDCALL SeparatorLine() = 0;

			virtual bool CPF_STDCALL Button(const char* text) = 0;
		};
	}
}
