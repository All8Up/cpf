//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Events/Event.hpp"

namespace Cpf
{
	enum class KeyCode : int32_t;
	enum class MouseButton : int32_t;
	enum class WindowFlags : int32_t;
	struct OSWindowData;
	struct WindowDesc;

	struct iWindow : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iWindow"_crc64);

		using OnMouseMove = Events::Event<"OnMouseMove"_crc64, Function<void(int32_t, int32_t)>>;
		using OnButtonDown = Events::Event<"OnButtonDown"_crc64, Function<void(MouseButton, int32_t, int32_t)>>;
		using OnButtonUp = Events::Event<"OnButtonUp"_crc64, Function<void(MouseButton, int32_t, int32_t)>>;
		using OnMouseWheel = Events::Event<"OnMouseWheel"_crc64, Function<void()>>;
		using OnKeyDown = Events::Event<"OnKeyDown"_crc64, Function<void(KeyCode)>>;
		using OnKeyUp = Events::Event<"OnKeyUp"_crc64, Function<void(KeyCode)>>;
		using OnMoved = Events::Event<"OnMoved"_crc64, Function<void(int32_t, int32_t)>>;
		using OnResize = Events::Event<"OnResize"_crc64, Function<void(int32_t, int32_t)>>;
		using OnClose = Events::Event<"OnClose"_crc64, Function<bool()>>;
		using OnMouseEnter = Events::Event<"OnMouseEnter"_crc64, Function<void()>>;
		using OnMouseLeave = Events::Event<"OnMouseLeave"_crc64, Function<void()>>;
		using OnMinimized = Events::Event<"OnMinimized"_crc64, Function<void()>>;
		using OnMaximized = Events::Event<"OnMaximized"_crc64, Function<void()>>;
		using OnRestored = Events::Event<"OnRestored"_crc64, Function<void()>>;
		using OnFocusGained = Events::Event<"OnFocusGained"_crc64, Function<void()>>;
		using OnFocusLost = Events::Event<"OnFocusLost"_crc64, Function<void()>>;
		using OnShow = Events::Event<"OnShow"_crc64, Function<void()>>;
		using OnHide = Events::Event<"OnHide"_crc64, Function<void()>>;
		using OnExposed = Events::Event<"OnExposed"_crc64, Function<void()>>;

		static constexpr int32_t Centered(int monitor = 0) { return monitor | 0xFF100000; }

		virtual bool CPF_STDCALL Initialize(const WindowDesc* desc) = 0;
		virtual void CPF_STDCALL SetTitle(const char* title) = 0;
		virtual void CPF_STDCALL SetPosition(int32_t, int32_t) = 0;
		virtual void CPF_STDCALL GetPosition(int32_t*, int32_t*) = 0;
		virtual void CPF_STDCALL SetSize(int32_t, int32_t) = 0;
		virtual void CPF_STDCALL GetSize(int32_t*, int32_t*) = 0;
		virtual void CPF_STDCALL Minimize() = 0;
		virtual void CPF_STDCALL Maximize() = 0;
		virtual void CPF_STDCALL Restore() = 0;
		virtual COM::Result CPF_STDCALL GetClientAreaSize(int32_t*, int32_t*) = 0;
		virtual Events::Emitter* CPF_STDCALL GetEmitter() = 0;
		virtual COM::Result CPF_STDCALL GetOSData(OSWindowData*) = 0;
	};
}
