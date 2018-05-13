//////////////////////////////////////////////////////////////////////////
#include "Platform.hpp"
#include "Window.hpp"

using namespace CPF;
using namespace Platform;

DesktopSDL2::DesktopSDL2(Plugin::iRegistry* registry)
	: mpRegistry(registry)
{
}

DesktopSDL2::~DesktopSDL2()
{
}

Outcome<Desktop::iWindow*, GOM::Result> CPF_STDCALL DesktopSDL2::CreateWindow(const Desktop::WindowDesc* desc)
{
	if (desc)
	{
		auto window = new SDL2::Window(mpRegistry, nullptr);
		GOM::Result result = GOM::kOutOfMemory;
		if (window)
		{
			result = window->Initialize(desc);
			if (GOM::Succeeded(result))
			{
				iDesktop::WindowCreated createdWindow{ window, desc };
				mEventEmitter.Emit(&createdWindow);
				return Outcome<Desktop::iWindow*, GOM::Result>::OK(static_cast<Platform::Desktop::iWindow*>(window));
			}
		}
		return Outcome<Desktop::iWindow*, GOM::Result>::Error(result);
	}
	return Outcome<Desktop::iWindow*, GOM::Result>::Error(GOM::kInvalidParameter);
}

GOM::Result CPF_STDCALL DesktopSDL2::OnEvent(int64_t id, GOM::EventHandler cb, void* context)
{
	return mEventEmitter.OnEvent(id, cb, context);
}

GOM::Result CPF_STDCALL DesktopSDL2::RemoveEvent(int64_t id, GOM::EventHandler cb, void* context)
{
	return mEventEmitter.RemoveEvent(id, cb, context);
}

GOM::Result CPF_STDCALL DesktopSDL2::EmitEvent(int64_t id, size_t eventSize, const void* eventData) const
{
	return mEventEmitter.EmitEvent(id, eventSize, eventData);
}

GOM::Result CPF_STDCALL DesktopSDL2::SetEventSink(GOM::iEventSink* sink)
{
    return mEventEmitter.SetEventSink(sink);
}
