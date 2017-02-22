//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Math/Color.hpp"
#include "Math/Vector2.hpp"
#include "Math/Constants.hpp"


namespace Cpf
{
	class iWindow;

	namespace Resources
	{
		class Locator;
	}

	namespace Graphics
	{
		class iCommandBuffer;
		class iImage;
		class iDevice;
		class iShader;
		class iSampler;
		class iPipeline;
		class iIndexBuffer;
		class iVertexBuffer;
		class iConstantBuffer;
		class iResourceBinding;

		class DebugUI : public tRefCounted<iRefCounted>
		{
		public:
			DebugUI();
			~DebugUI() override;

			bool Initialize(iDevice*, iWindow* window, Resources::Locator*);
			void Shutdown();
			void BeginFrame(iCommandBuffer* commands, float deltaTime);
			void EndFrame(iCommandBuffer* commands);

			// Window
			void Begin(const char* name, bool* isOpen = nullptr, uint32_t flags = 0);
			void End();

			// Text
			void Text(const char* fmt, ...);
			void TextColored(const Math::Color4f& color, const char* fmt, ...);

			// Buttons.
			bool Button(const char* label, const Math::Vector2i = Math::Vector2i(0));
			bool SmallButton(const char* label);

			// Check box.
			bool CheckBox(const char* label, bool* v);
			bool CheckBoxFlags(const char* label, uint32_t* flags, uint32_t flags_value);

			// Sliders
			bool Slider(const char* label, int32_t* value, int vmin, int vmax, const char* fmt = "%.0f");

			// Histograms
			void Histogram(const char* label, const float* values, int32_t count,
				int32_t offset = 0, const char* overlay = nullptr, float scaleMin = Math::kFloatMax, float scaleMax = Math::kFloatMax,
				const Math::Vector2i = Math::Vector2i(0), int32_t stride = sizeof(float));

			// List boxes.
			void ListBox(const char* label, int32_t* selectedItem, const char** items, int32_t itemCount, int32_t itemHeight=-1);

			// Rendering information.
			void SetWindowSize(int32_t width, int32_t height);

			static bool HandleRawInput(void* context, const void* data);

		private:
			bool DebugUI::_HandleRawInput(const void* rawEvent);
			static const char* _GetClipboardText();
			static void _SetClipboardText(const char* text);

			bool mMousePressed[3];
			float mMouseWheel;

			static const size_t kVertexBufferSize = 1024 * 512;
			static const size_t kIndexBufferSize = 1024 * 64;

			//////////////////////////////////////////////////////////////////////////
			iDevice* mpDevice;
			Resources::Locator* mpLocator;
			IntrusivePtr<iShader> mpVertexShader;
			IntrusivePtr<iShader> mpPixelShader;
			IntrusivePtr<iResourceBinding> mpResourceBinding;
			IntrusivePtr<iPipeline> mpPipeline;
			IntrusivePtr<iImage> mpUIAtlas;
			IntrusivePtr<iSampler> mpSampler;
			IntrusivePtr<iVertexBuffer> mpVertexBuffer;
			IntrusivePtr<iIndexBuffer> mpIndexBuffer;
			IntrusivePtr<iConstantBuffer> mpProjectionMatrix;

			// Rendering information.
			int32_t mWidth;
			int32_t mHeight;
		};
	}
}
