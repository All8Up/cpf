//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Hash/HashString.hpp"
#include "Graphics/iCommandBuffer.hpp"

namespace CPF
{
	namespace Concurrency {
		class ThreadContext;
	}

	class ExperimentalD3D12;

	static constexpr GOM::ClassID kRenderSystemCID = GOM::ClassID("RenderSystemCID"_crc64);

	class RenderSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("RenderSystem"_crc64);
		//
		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);

		static constexpr MultiCore::StageID kBeginFrame = Hash::Create<MultiCore::StageID_tag>("Begin Frame"_hashString);
		static constexpr MultiCore::StageID kDrawInstances = Hash::Create<MultiCore::StageID_tag>("Draw Instances"_hashString);
		static constexpr MultiCore::StageID kDebugUI = Hash::Create<MultiCore::StageID_tag>("Debug UI"_hashString);
		static constexpr MultiCore::StageID kEndFrame = Hash::Create<MultiCore::StageID_tag>("End Frame"_hashString);

		// Construction/Destruction.
		RenderSystem(Plugin::iRegistry*, GOM::iUnknown*);
		virtual ~RenderSystem();

		// Registration.
		static GOM::Result Install(Plugin::iRegistry*);
		static GOM::Result Remove(Plugin::iRegistry*);

		struct Desc : iSystem::Desc
		{
			MultiCore::SystemID mTimerID;
			ExperimentalD3D12* mpApplication;
		};

		// iBase
		GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		// iSystem
		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		GOM::Result CPF_STDCALL Configure(MultiCore::iExecutionPlan*) override { return GOM::kOK; }

		// iStageList
		GOM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		GOM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		GOM::Result CPF_STDCALL GetDependencies(MultiCore::iExecutionPlan* owner, int32_t*, MultiCore::BlockDependency*) override;

		GOM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		GOM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

	private:
		//
		static void _BeginFrame(const Concurrency::WorkContext* tc, void* context);
		static void _Clear(const Concurrency::WorkContext* tc, void* context);
		static void _Draw(const Concurrency::WorkContext* tc, void* context);
		static void _DebugUI(const Concurrency::WorkContext* tc, void* context);
		static void _PreparePresent(const Concurrency::WorkContext* tc, void* context);
		static void _EndFrame(const Concurrency::WorkContext* tc, void* context);

		ExperimentalD3D12* mpApp;

		//////////////////////////////////////////////////////////////////////////
		static const int kBufferCount = 3;

		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<Graphics::iDevice> mpDevice;

		int mCurrentBackBuffer;
		IntrusivePtr<Graphics::iCommandPool> mpPreCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPreCommandBuffer[kBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpPostCommandPool[kBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPostCommandBuffer[kBufferCount];

		MultiCore::SystemID mID;
		IntrusivePtr<iStageList> mpStages;
	};
}
