//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplicationMain.hpp"
#include "Application/iWindowedApplication.hpp"
#include "MultiCore/iPipeline.hpp"
#include "RenderSystem.hpp"
#include "NetworkSystem.hpp"
#include "Concurrency/iThreadPool.hpp"
#include "Concurrency/iLoadBalancer.hpp"
#include "MultiCore/System/iTimer.hpp"

namespace Cpf
{
	class Networked : public tRefCounted<iApplicationMain>
	{
	public:
		Networked();
		~Networked() override;

		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }

		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, COM::ClassID* appCid) override;
		COM::Result CPF_STDCALL Main(iApplication* application) override;
		void CPF_STDCALL Shutdown() override;

		Plugin::iRegistry* GetRegistry() { return mpRegistry; }

	private:
		void _ConfigureDebugUI();
		bool _CreateWindow();
		bool _Install();
		bool _Remove();
		bool _InitializeResources();
		bool _ShutdownResources();
		bool _InitializeMultiCore();
		bool _ShutdownMultiCore();
		bool _InitializePipeline();
		COM::Result _ConfigurePipeline();
		bool _ShutdownPipeline();

		// Debug panels.
		static void _PerformanceUI(Graphics::iDebugUI*, void*);

		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;

		IntrusivePtr<Concurrency::iScheduler> mpScheduler;
		IntrusivePtr<iThreadPool> mpThreadPool;
		IntrusivePtr<Concurrency::iLoadBalancer> mpLoadBalancer;
		IntrusivePtr<Resources::Locator> mpLocator;

		IntrusivePtr<MultiCore::iPipeline> mpPipeline;
		IntrusivePtr<MultiCore::iTimer> mpTimer;
		IntrusivePtr<NetworkSystem> mpNetworkSystem;
		IntrusivePtr<RenderSystem> mpRenderSystem;

		Time::Value mLastTime;

		Plugin::iRegistry* mpRegistry;
		iWindowedApplication* mpWindowedApplication;
	};
}
