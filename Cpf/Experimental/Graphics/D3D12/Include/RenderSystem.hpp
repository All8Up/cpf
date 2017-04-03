//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/iSystem.hpp"
#include "Hash/HashString.hpp"
#include "Graphics/Interfaces/iCommandBuffer.hpp"

namespace Cpf
{
	namespace Concurrency {
		class ThreadContext;
	}

	class ExperimentalD3D12;

	class RenderSystem : public MultiCore::System
	{
	public:
		//
		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);

		static constexpr MultiCore::StageID kBeginFrame = Hash::Create<MultiCore::StageID_tag>("Begin Frame"_hashString);
		static constexpr MultiCore::BlockID kClearBuffers = Hash::Create<MultiCore::BlockID_tag>("Clear Buffers"_hashString);
		static constexpr MultiCore::StageID kDrawInstances = Hash::Create<MultiCore::StageID_tag>("Draw Instances"_hashString);
		static constexpr MultiCore::BlockID kDebugUI = Hash::Create<MultiCore::BlockID_tag>("Debug UI"_hashString);
		static constexpr MultiCore::BlockID kPreparePresent = Hash::Create<MultiCore::BlockID_tag>("Prepare Present"_hashString);
		static constexpr MultiCore::BlockID kEndFrame = Hash::Create<MultiCore::BlockID_tag>("End Frame"_hashString);

		// Registration.
		static bool Install();
		static bool Remove();

		struct Desc : System::Desc
		{
			MultiCore::SystemID mTimerID;
			ExperimentalD3D12* mpApplication;
		};

	private:
		// Construction/Destruction.
		RenderSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const Desc* desc);
		~RenderSystem() override;

		//
		void _AllocateBuffers();

		static void _BeginFrame(Concurrency::ThreadContext& tc, void* context);
		static void _Clear(Concurrency::ThreadContext& tc, void* context);
		static void _Draw(Concurrency::ThreadContext& tc, void* context);
		static void _DebugUI(Concurrency::ThreadContext& tc, void* context);
		static void _PreparePresent(Concurrency::ThreadContext& tc, void* context);
		static void _EndFrame(Concurrency::ThreadContext& tc, void* context);

		//
		static iSystem* Creator(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const System::Desc* desc);

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
	};
}
