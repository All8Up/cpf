//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "Graphics/DebugUI.hpp"
#include "Graphics/Interfaces/iInstance.hpp"
#include "Graphics/Interfaces/iDevice.hpp"
#include "Graphics/Interfaces/iSwapChain.hpp"


namespace Cpf
{
	class RenderSystem : public MultiCore::System
	{
	public:
		static constexpr MultiCore::SystemID kID = "Render System"_hashString;

		static bool Install();
		static bool Remove();

		bool Initialize(iWindow*);
		bool Shutdown();

		void Resize(int32_t, int32_t);

		Graphics::DebugUI& GetDebugUI();

	private:
		RenderSystem(MultiCore::Pipeline* pipeline, const char* name, const Desc* desc);
		~RenderSystem() override;

		static System* _Create(MultiCore::Pipeline* owner, const char* name, const Desc* desc);
		void _CreateStages();

		bool _SelectAdapter();
		bool _CreateSwapChain(iWindow* window);

		static void _BeginFrame(Concurrency::ThreadContext&, void* context);
		static void _EndFrame(Concurrency::ThreadContext&, void* context);

		static constexpr int kBufferCount = 3;

		IntrusivePtr<Graphics::iInstance> mpInstance;
		IntrusivePtr<Graphics::iAdapter> mpAdapter;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		IntrusivePtr<Graphics::DebugUI> mpDebugUI;
	};
}
