//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "Graphics/DebugUI.hpp"
#include "Graphics/Interfaces/iInstance.hpp"
#include "Graphics/Interfaces/iDevice.hpp"
#include "Graphics/Interfaces/iSwapChain.hpp"
#include "MultiCore/System/Timer.hpp"


namespace Cpf
{
	class RenderSystem : public MultiCore::System
	{
	public:
		static constexpr MultiCore::SystemID kID = "Render System"_hashString;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mTimer;
		};

		static bool Install();
		static bool Remove();

		bool Configure() override;

		bool Initialize(iWindow*, Resources::Locator*);
		bool Shutdown();

		void Resize(int32_t, int32_t);

		Graphics::DebugUI& GetDebugUI();

	private:
		RenderSystem(MultiCore::Pipeline* pipeline, const char* name, const Desc* desc);
		~RenderSystem() override;

		static System* _Create(MultiCore::Pipeline* owner, const char* name, const System::Desc* desc);
		void _CreateStages();

		bool _SelectAdapter();
		bool _CreateSwapChain(iWindow* window);
		bool _CreateRenderData(iWindow*, Resources::Locator*);

		static void _BeginFrame(Concurrency::ThreadContext&, void* context);
		static void _DebugUI(Concurrency::ThreadContext&, void* context);
		static void _EndFrame(Concurrency::ThreadContext&, void* context);

		static constexpr int kBufferCount = 3;

		Desc mDesc;
		MultiCore::Timer* mpTimer;

		IntrusivePtr<Graphics::iInstance> mpInstance;
		IntrusivePtr<Graphics::iAdapter> mpAdapter;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		IntrusivePtr<Graphics::DebugUI> mpDebugUI;

		int mBufferIndex = 0;
		int mSwapIndex = 0;
		uint64_t mFenceTarget = 0;
		IntrusivePtr<Graphics::iCommandPool> mpPreCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPreCommandBuffer[kBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpPostCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPostCommandBuffer[kBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpDebugUIPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpDebugUIBuffer[kBufferCount];
		IntrusivePtr<Graphics::iFence> mpFence;

		int mScheduleIndex = 0;
		Graphics::iCommandBuffer* mpScheduledBuffers[Concurrency::Scheduler::kMaxThreads * 4];
	};
}
