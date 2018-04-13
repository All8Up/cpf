//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Desktop/iWindow.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/ImmediateEventEmitter.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "SDL.h"

namespace CPF
{
	namespace SDL2
	{
		class Window : public GOM::tUnknown<Platform::Desktop::iWindow>
		{
		public:
			Window(Plugin::iRegistry*, iUnknown*)
				: mpWindow(nullptr)
			{}
			~Window();

			GOM::Result Initialize(const Platform::Desktop::WindowDesc* desc);

			// Overrides from iWindow.
			void CPF_STDCALL SetTitle(const char* title) override;
			void CPF_STDCALL SetPosition(int32_t x, int32_t y) override;
			void CPF_STDCALL GetPosition(int32_t* x, int32_t* y) override;
			void CPF_STDCALL SetSize(int32_t x, int32_t y) override;
			void CPF_STDCALL GetSize(int32_t* x, int32_t* y) override;
			void CPF_STDCALL Minimize() override;
			void CPF_STDCALL Maximize() override;
			void CPF_STDCALL Restore() override;
			void CPF_STDCALL GetClientArea(int32_t* x, int32_t* y) override;
			GOM::Result CPF_STDCALL GetOSData(Platform::Desktop::OSWindowData* data) override;

			// Overrides from iEventEmitter.
			GOM::Result CPF_STDCALL OnEvent(int64_t id, GOM::EventHandler cb, void* context) override;
			GOM::Result CPF_STDCALL RemoveEvent(int64_t id, GOM::EventHandler cb, void* context) override;
			GOM::Result CPF_STDCALL EmitEvent(int64_t id, size_t eventSize, const void* eventData) const override;

		private:
			SDL_Window * mpWindow;
			Plugin::ImmediateEventEmitter mEmitter;
		};
	}
}
