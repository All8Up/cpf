//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "Events/Emitter.hpp"
#include "Math/Vector2v.hpp"
#include "RefCounted.hpp"

namespace Cpf
{
	class WindowedApplication;
	enum class KeyCode : int32_t;
	enum class MouseButton : int32_t;

	struct WindowDesc
	{
		WindowDesc(WindowedApplication* app);

		WindowDesc& Title(const String& title);
		WindowDesc& Position(const Math::Vector2i& pos);
		WindowDesc& Size(const Math::Vector2i& size);
		WindowDesc& Flags(uint32_t flags);

		operator iWindow* () const;

		String mTitle;
		Math::Vector2i mPosition;
		Math::Vector2i mSize;
		uint32_t mFlags;

		WindowedApplication* mpApplication;
	};

	struct OSWindowData
	{
#if CPF_TARGET_WINDOWS
		HWND mHwnd;
		HDC mHDC;
#endif
#if CPF_TARGET_DARWIN
		void* mpView;
#endif
	};

	class iWindow : public tRefCounted<iRefCounted>
	{
	public:
		static const Math::Vector2i Centered;

		virtual Math::Vector2i GetClientArea() const = 0;
		virtual OSWindowData GetOSWindowData() const = 0;
		virtual Platform::Events::Emitter& GetEmitter() = 0;

		using OnMouseMove = Platform::Events::Event< 1, Function<void(int32_t, int32_t)> >;
		using OnButtonDown = Platform::Events::Event< 2, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnButtonUp = Platform::Events::Event< 3, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnMouseWheel = Platform::Events::Event< 4, Function<void()> >;

		using OnKeyDown = Platform::Events::Event < 5, Function<void(KeyCode)> >;
		using OnResized = Platform::Events::Event < 6, Function<void(int32_t, int32_t)> >;

	protected:
		virtual ~iWindow() = 0;
	};
}
