//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Hash/HashString.hpp"
#include "Graphics/iCommandBuffer.hpp"

namespace Cpf
{
	namespace Concurrency {
		class ThreadContext;
	}

	class ExperimentalD3D12;

	static constexpr COM::ClassID kRenderSystemCID = COM::ClassID("RenderSystemCID"_crc64);

	class RenderSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("RenderSystem"_crc64);
		//
		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);

		static constexpr MultiCore::StageID kBeginFrame = Hash::Create<MultiCore::StageID_tag>("Begin Frame"_hashString);
		static constexpr MultiCore::BlockID kClearBuffers = Hash::Create<MultiCore::BlockID_tag>("Clear Buffers"_hashString);
		static constexpr MultiCore::StageID kDrawInstances = Hash::Create<MultiCore::StageID_tag>("Draw Instances"_hashString);
		static constexpr MultiCore::BlockID kDebugUI = Hash::Create<MultiCore::BlockID_tag>("Debug UI"_hashString);
		static constexpr MultiCore::BlockID kPreparePresent = Hash::Create<MultiCore::BlockID_tag>("Prepare Present"_hashString);
		static constexpr MultiCore::BlockID kEndFrame = Hash::Create<MultiCore::BlockID_tag>("End Frame"_hashString);

		// Construction/Destruction.
		RenderSystem();
		virtual ~RenderSystem();

		// Registration.
		static COM::Result Install(Plugin::iRegistry*);
		static COM::Result Remove(Plugin::iRegistry*);

		struct Desc : iSystem::Desc
		{
			MultiCore::SystemID mTimerID;
			ExperimentalD3D12* mpApplication;
		};

		// iUnknown
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

		// iSystem
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return COM::kOK; }

		// iStageList
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		COM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

	private:
		//
		void _AllocateBuffers();

		static void _BeginFrame(Concurrency::ThreadContext& tc, void* context);
		static void _Clear(Concurrency::ThreadContext& tc, void* context);
		static void _Draw(Concurrency::ThreadContext& tc, void* context);
		static void _DebugUI(Concurrency::ThreadContext& tc, void* context);
		static void _PreparePresent(Concurrency::ThreadContext& tc, void* context);
		static void _EndFrame(Concurrency::ThreadContext& tc, void* context);

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
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}