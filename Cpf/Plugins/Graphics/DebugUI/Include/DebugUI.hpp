//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iDebugUI.hpp"
#include "Pair.hpp"
#include "Vector.hpp"

namespace Cpf
{
	struct iInputManager;
	struct iMouseDevice;
	struct iKeyboardDevice;
	struct iClipboard;
	enum class MouseButton : int32_t;
	enum class ScanCode : int32_t;

	namespace Graphics
	{
		class DebugUI : public tRefCounted<iDebugUI>
		{
		public:
			DebugUI(iBase* outer);
			virtual ~DebugUI();

			GOM::Result Cast(uint64_t id, void** outIface) override;

			//
			bool Initialize(iDevice*, iInputManager* im, iWindow* window, Resources::iLocator*);
			void Shutdown();
			void BeginFrame(iCommandBuffer* commands, float deltaTime);
			void EndFrame(iCommandBuffer* commands);

			//
			void PushItemWidth(int32_t width);
			void PopItemWidth();
			void Separator();

			// Window
			void Begin(const char* name, bool* isOpen = nullptr, uint32_t flags = 0);
			void End();

			// Text
			void Text(const char* fmt, ...);
			void TextColored(const Math::Vector4fv& color, const char* fmt, ...);

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
			void ListBox(const char* label, int32_t* selectedItem, const char** items, int32_t itemCount, int32_t itemHeight = -1);

			// Rendering information.
			void SetWindowSize(int32_t width, int32_t height);

			// Debug list.
			void Add(DebugUICall call, void* context);
			void Remove(DebugUICall call, void* context);
			void Execute();

		private:
			void _OnMouseWheel(int32_t, int32_t);
			void _OnMouseDown(MouseButton, int32_t, int32_t);
			void _OnKeyDown(ScanCode);
			void _OnKeyUp(ScanCode);
			void _HandleKey(bool, ScanCode);
			static const char* _GetClipboardText();
			static void _SetClipboardText(const char* text);

			static const size_t kVertexBufferSize = 1024 * 512;
			static const size_t kIndexBufferSize = 1024 * 64;

			//////////////////////////////////////////////////////////////////////////
			iDevice* mpDevice;
			Resources::iLocator* mpLocator;
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

			bool mMousePressed[3];
			float mMouseWheel;

			//
			IntrusivePtr<iMouseDevice> mpMouse;
			IntrusivePtr<iKeyboardDevice> mpKeyboard;

			//
			using DebugCallPair = Pair<DebugUICall, void*>;
			using DebugCalls = Vector<DebugCallPair>;
			DebugCalls mDebugCalls;
		};
	}
}
