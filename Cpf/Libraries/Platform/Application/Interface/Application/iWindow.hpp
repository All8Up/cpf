//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Events/Event.hpp"

namespace Cpf
{
	struct OSWindowData;
	enum class MouseButton : int32_t;
	enum class KeyCode : int32_t;

	struct iWindow : COM::iUnknown
	{
		static constexpr COM::ClassID kIID = COM::ClassID("iWindow"_crc64);

		// Events.
		using OnMouseMove = Events::Event<"OnMouseMove"_crc64, Function<void(int32_t, int32_t)>>;
		using OnButtonDown = Events::Event<"OnButtonDown"_crc64, Function<void(MouseButton, int32_t, int32_t)>>;
		using OnButtonUp = Events::Event<"OnButtonUp"_crc64, Function<void(MouseButton, int32_t, int32_t)>>;
		using OnMouseWheel = Events::Event<"OnMouseWheel"_crc64, Function<void()>>;
		using OnKeyDown = Events::Event<"OnKeyDown"_crc64, Function<void(KeyCode)>>;
		using OnKeyUp = Events::Event<"OnKeyUp"_crc64, Function<void(KeyCode)>>;
		using OnMoved = Events::Event<"OnMoved"_crc64, Function<void(int32_t, int32_t)>>;
		using OnResize = Events::Event<"OnResize"_crc64, Function<void(int32_t, int32_t)>>;

		/* Additional events to implement.
		using OnClose = Events::Event<"OnClose"_crc64, Function<bool()>>;
		using OnMouseEnter = Events::Event<"OnMouseEnter"_crc64, Function<void()>>;
		using OnMouseLeave = Events::Event<"OnMouseLeave"_crc64, Function<void()>>;
		*/

		// Interface.
		virtual void CPF_STDCALL SetTitle(const char* title) = 0;
		virtual void CPF_STDCALL SetPosition(int32_t, int32_t) = 0;
		virtual void CPF_STDCALL GetPosition(int32_t*, int32_t*) = 0;
		virtual void CPF_STDCALL SetSize(int32_t, int32_t) = 0;
		virtual void CPF_STDCALL GetSize(int32_t*, int32_t*) = 0;
		virtual void CPF_STDCALL Minimize() = 0;
		virtual void CPF_STDCALL Maximize() = 0;
		virtual void CPF_STDCALL Restore() = 0;
		virtual void CPF_STDCALL GetClientArea(int32_t*, int32_t*) = 0;
		virtual void CPF_STDCALL GetEmitter(Events::Emitter**) = 0;
		virtual void CPF_STDCALL GetOSData(OSWindowData*) = 0;
	};
}
