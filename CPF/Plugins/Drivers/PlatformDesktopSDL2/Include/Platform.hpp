//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/iDesktop.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/ImmediateEventEmitter.hpp"

namespace CPF
{
	class DesktopSDL2 : public GOM::tUnknown<Platform::iDesktop>
	{
	public:
		DesktopSDL2(Plugin::iRegistry* registry);
		~DesktopSDL2();

		// Overloads from iDesktop.
		Outcome<Platform::Desktop::iWindow*, GOM::Result> CPF_STDCALL CreateWindow(const Platform::Desktop::WindowDesc* desc) override;

		// Overrides from iEventEmitter.
		GOM::Result CPF_STDCALL OnEvent(int64_t id, GOM::EventHandler cb, void* context) override;
		GOM::Result CPF_STDCALL RemoveEvent(int64_t id, GOM::EventHandler cb, void* context) override;
		GOM::Result CPF_STDCALL EmitEvent(int64_t id, size_t eventSize, const void* eventData) const override;

	private:
		IntrusivePtr<Plugin::iRegistry> mpRegistry;
		Plugin::ImmediateEventEmitter mEventEmitter;
	};
}
