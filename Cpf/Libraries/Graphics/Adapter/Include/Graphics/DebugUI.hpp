//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

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

			// Rendering information.
			void SetWindowSize(int32_t width, int32_t height);

			static bool HandleRawInput(void* context, const void* data);

		private:
			bool DebugUI::_HandleRawInput(const void* rawEvent);
			static const char* _GetClipboardText();
			static void _SetClipboardText(const char* text);

			void _OnMouseMoved(int32_t x, int32_t y);

			bool mMousePressed[3];
			float mMouseWheel;

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
