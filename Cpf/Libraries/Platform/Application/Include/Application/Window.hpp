//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "Events/Emitter.hpp"
#include "Math/Vector2v.hpp"
#include "Application/OSWindowData.hpp"
#include "COM/iUnknown.hpp"

namespace Cpf
{
	class WindowedApplication;
	enum class KeyCode : int32_t;
	enum class MouseButton : int32_t;
	enum class WindowFlags : int32_t;

	class iWindow : public tRefCounted<COM::iUnknown>
	{
	public:
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("iWindow"_crc64);

		static const Math::Vector2i Centered;

		virtual Math::Vector2i GetClientArea() const = 0;
		virtual OSWindowData GetOSWindowData() const = 0;
		virtual Events::Emitter& GetEmitter() = 0;

		using OnMouseMove = Events::Event<"OnMouseMove"_crc64, Function<void(int32_t, int32_t)> >;
		using OnButtonDown = Events::Event<"OnButtonDown"_crc64, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnButtonUp = Events::Event<"OnButtonUp"_crc64, Function<void(MouseButton, int32_t, int32_t)> >;
		using OnMouseWheel = Events::Event<"OnMouseWheel"_crc64, Function<void()> >;

		using OnKeyDown = Events::Event <"OnKeyDown"_crc64, Function<void(KeyCode)> >;
		using OnResized = Events::Event <"OnResize"_crc64, Function<void(int32_t, int32_t)> >;
	};
}
