//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	enum class WindowFlags : int32_t
	{
		eFullscreen = 1 << 0,
		eSupportOpenGL = 1 << 1,
		eShown = 1 << 2,
		eHidden = 1 << 3,
		eBorderless = 1 << 4,
		eResizable = 1 << 5,
		eMinimized = 1 << 6,
		eMaximized = 1 << 7,
		eInputGrabbed = 1 << 8,
		eInputFocus = 1 << 9,
		eMouseFocus = 1 << 10,
		eFullscreenDesktop = 1 << 11,
		eAllowHDPI = 1 << 12,
		eMouseCapture = 1 << 13
	};
	CPF_ENUM_FLAG_TYPE(WindowFlags);

	struct WindowDesc
	{
		const char* mpTitle;
		int32_t mX, mY;
		int32_t mWidth, mHeight;
		uint32_t mFlags;
	};

	struct OSWindowHandle
	{
	};

	struct iWindow : COM::iUnknown
	{
		static constexpr COM::ClassID kIID = COM::ClassID("iWindow"_crc64);

		// Events.
		using OnMouseMove = Platform::Events::Event< 1, Function<void(int32_t, int32_t)> >;
		using OnButtonDown = Platform::Events::Event< 2, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnButtonUp = Platform::Events::Event< 3, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnMouseWheel = Platform::Events::Event< 4, Function<void()> >;
		using OnKeyDown = Platform::Events::Event < 5, Function<void(KeyCode)> >;
		using OnKeyUp = Platform::Events::Event < 6, Function<void(KeyCode)> >;
		using OnResized = Platform::Events::Event < 7, Function<void(int32_t, int32_t)> >;

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
		virtual void CPF_STDCALL GetEmitter(Platform::Events::Emitter*) = 0;
		virtual void CPF_STDCALL GetOSData(OSWindowData*) = 0;
	};
}
