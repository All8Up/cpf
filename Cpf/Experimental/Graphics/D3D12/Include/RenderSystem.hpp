//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/System.hpp"
#include "Hash/HashString.hpp"

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
		static constexpr auto kID = MultiCore::SystemID("Render System"_crc64);
		static constexpr Hash::StringHash kBeginFrame = "Begin Frame"_stringHash;
		static constexpr Hash::StringHash kClearBuffers = "Clear Buffers"_stringHash;
		static constexpr Hash::StringHash kDrawInstances = "Draw Instances"_stringHash;
		static constexpr Hash::StringHash kDebugUI = "Debug UI"_stringHash;
		static constexpr Hash::StringHash kPreparePresent = "Prepare Present"_stringHash;
		static constexpr Hash::StringHash kEndFrame = "End Frame"_stringHash;

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
		RenderSystem(const String& name, const EntityService::SystemDependencies& deps, const Desc* desc);
		~RenderSystem() override;

		static void _BeginFrame(Concurrency::ThreadContext& tc, void* context);
		static void _Clear(Concurrency::ThreadContext& tc, void* context);
		static void _Draw(Concurrency::ThreadContext& tc, void* context);
		static void _DebugUI(Concurrency::ThreadContext& tc, void* context);
		static void _PreparePresent(Concurrency::ThreadContext& tc, void* context);
		static void _EndFrame(Concurrency::ThreadContext& tc, void* context);

		//
		static System* Creator(const String& name, const System::Desc* desc, const EntityService::SystemDependencies& deps);

		ExperimentalD3D12* mpApp;
	};
}
