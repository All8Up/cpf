//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/System.hpp"
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
		static constexpr auto kID = "Render System"_hashString;

		static constexpr auto kBeginFrame = "Begin Frame"_hashString;
		static constexpr auto kClearBuffers = "Clear Buffers"_hashString;
		static constexpr auto kDrawInstances = "Draw Instances"_hashString;
		static constexpr auto kDebugUI = "Debug UI"_hashString;
		static constexpr auto kPreparePresent = "Prepare Present"_hashString;
		static constexpr auto kEndFrame = "End Frame"_hashString;

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
		RenderSystem(MultiCore::Pipeline* owner, const char* name, const EntityService::SystemDependencies& deps, const Desc* desc);
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
		static System* Creator(MultiCore::Pipeline* owner, const char* name, const System::Desc* desc, const EntityService::SystemDependencies& deps);

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
