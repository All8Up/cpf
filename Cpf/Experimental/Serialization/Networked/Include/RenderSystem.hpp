//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iSystem.hpp"
#include "Graphics/iDebugUI.hpp"
#include "Graphics/iInstance.hpp"
#include "Graphics/iDevice.hpp"
#include "Graphics/iSwapChain.hpp"
#include "MultiCore/System/iTimer.hpp"


namespace Cpf
{
	static constexpr COM::ClassID kRenderSystemCID = COM::ClassID("Render System Class"_crc64);

	class RenderSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("RenderSystem"_crc64);

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);

		struct Desc : iSystem::Desc
		{
			MultiCore::SystemID mTimer;
		};

		static COM::Result Install(Plugin::iRegistry*);
		static COM::Result Remove(Plugin::iRegistry*);

		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override;

		bool Initialize(Plugin::iRegistry* registry, COM::ClassID rid, iWindow*, Resources::Locator*);
		bool Shutdown();

		void Resize(int32_t, int32_t);

		Graphics::iDebugUI* GetDebugUI();

		// iUnknown
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

		// iSystem
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
//		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return COM::kOK; }

		// iStageList
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		COM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;


		RenderSystem(COM::iUnknown*);

	private:
		virtual ~RenderSystem();

		void _CreateStages();

		bool _SelectAdapter();
		bool _CreateSwapChain(iWindow* window);
		bool _CreateRenderData(iWindow*, Resources::Locator*);

		static void _BeginFrame(Concurrency::ThreadContext&, void* context);
		static void _DebugUI(Concurrency::ThreadContext&, void* context);
		static void _EndFrame(Concurrency::ThreadContext&, void* context);

		static constexpr int kBufferCount = 3;

		Desc mDesc;
		MultiCore::iTimer* mpTimer;
		Plugin::iRegistry* mpRegistry;

		IntrusivePtr<Graphics::iInstance> mpInstance;
		IntrusivePtr<Graphics::iAdapter> mpAdapter;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		Vector<IntrusivePtr<Graphics::iImage>> mpDepthBufferImages;
		Vector<IntrusivePtr<Graphics::iImageView>> mpDepthBufferImageViews;
		IntrusivePtr<Graphics::iDebugUI> mpDebugUI;

		int mBufferIndex = 0;
		int mSwapIndex = 0;
		uint64_t mFenceTarget = 4;
		IntrusivePtr<Graphics::iCommandPool> mpPreCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPreCommandBuffer[kBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpPostCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPostCommandBuffer[kBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpDebugUIPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpDebugUIBuffer[kBufferCount];
		IntrusivePtr<Graphics::iFence> mpFence;

		int mScheduleIndex = 0;
		Graphics::iCommandBuffer* mpScheduledBuffers[Concurrency::Scheduler::kMaxThreads * 4];

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}
