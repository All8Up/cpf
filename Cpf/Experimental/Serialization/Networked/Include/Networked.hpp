//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "MultiCore/iPipeline.hpp"
#include "RenderSystem.hpp"
#include "NetworkSystem.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "MultiCore/System/iTimer.hpp"

namespace Cpf
{
	class Networked : public Adapter::WindowedApp
	{
	public:
		Networked();
		~Networked() override;

		int Start(const CommandLine&) override;

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
		static void _PerformanceUI(Graphics::DebugUI*, void*);

		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;

		Concurrency::Scheduler mLoopScheduler;
		Concurrency::ThreadPool mThreadPool;
		Concurrency::LoadBalancer mLoadBalancer;
		IntrusivePtr<Resources::Locator> mpLocator;

		IntrusivePtr<MultiCore::iPipeline> mpPipeline;
		IntrusivePtr<MultiCore::Timer> mpTimer;
		IntrusivePtr<NetworkSystem> mpNetworkSystem;
		IntrusivePtr<RenderSystem> mpRenderSystem;

		Time::Value mLastTime;
	};
}
