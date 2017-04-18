//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Math/Vector2v.hpp"
#include "Math/Vector4v.hpp"
#include "Math/Constants.hpp"
#include "Pair.hpp"
#include "Vector.hpp"


namespace Cpf
{
	struct iWindow;
	struct iInputManager;

	namespace Resources
	{
		class Locator;
	}

	namespace Graphics
	{
		struct iDevice;
		struct iCommandBuffer;
		struct iConstantBuffer;
		struct iIndexBuffer;
		struct iVertexBuffer;
		struct iImage;
		struct iShader;
		struct iSampler;
		struct iPipeline;
		struct iResourceBinding;

		//////////////////////////////////////////////////////////////////////////
		static constexpr COM::ClassID kDebugUICID = COM::ClassID("Graphics::iDebugUI"_crc64);

		struct iDebugUI : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iDebugUI"_crc64);

			virtual bool CPF_STDCALL Initialize(iDevice*, iInputManager*, iWindow* window, Resources::Locator*) = 0;
			virtual void CPF_STDCALL Shutdown() = 0;
			virtual void CPF_STDCALL BeginFrame(iCommandBuffer* commands, float deltaTime) = 0;
			virtual void CPF_STDCALL EndFrame(iCommandBuffer* commands) = 0;

			//
			virtual void CPF_STDCALL PushItemWidth(int32_t width) = 0;
			virtual void CPF_STDCALL PopItemWidth() = 0;
			virtual void CPF_STDCALL Separator() = 0;

			// Window
			virtual void CPF_STDCALL Begin(const char* name, bool* isOpen = nullptr, uint32_t flags = 0) = 0;
			virtual void CPF_STDCALL End() = 0;

			// Text
			virtual void CPF_STDCALL Text(const char* fmt, ...) = 0;
			virtual void CPF_STDCALL TextColored(const Math::Vector4fv& color, const char* fmt, ...) = 0;

			// Buttons.
			virtual bool CPF_STDCALL Button(const char* label, const Math::Vector2i = Math::Vector2i(0)) = 0;
			virtual bool CPF_STDCALL SmallButton(const char* label) = 0;

			// Check box.
			virtual bool CPF_STDCALL CheckBox(const char* label, bool* v) = 0;
			virtual bool CPF_STDCALL CheckBoxFlags(const char* label, uint32_t* flags, uint32_t flags_value) = 0;

			// Sliders
			virtual bool CPF_STDCALL Slider(const char* label, int32_t* value, int vmin, int vmax, const char* fmt = "%.0f") = 0;

			// Histograms
			virtual void CPF_STDCALL Histogram(const char* label, const float* values, int32_t count,
				int32_t offset = 0, const char* overlay = nullptr, float scaleMin = Math::kFloatMax, float scaleMax = Math::kFloatMax,
				const Math::Vector2i = Math::Vector2i(0), int32_t stride = sizeof(float)) = 0;

			// List boxes.
			virtual void CPF_STDCALL ListBox(const char* label, int32_t* selectedItem, const char** items, int32_t itemCount, int32_t itemHeight = -1) = 0;

			// Rendering information.
			virtual void CPF_STDCALL SetWindowSize(int32_t width, int32_t height) = 0;

			// Debug list.
			using DebugUICall = void(*)(iDebugUI*, void* context);
			virtual void CPF_STDCALL Add(DebugUICall call, void* context) = 0;
			virtual void CPF_STDCALL Remove(DebugUICall call, void* context) = 0;
			virtual void CPF_STDCALL Execute() = 0;
		};
	}
}
