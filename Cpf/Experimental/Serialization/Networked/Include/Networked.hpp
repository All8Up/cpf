//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "MultiCore/Pipeline.hpp"
#include "RenderSystem.hpp"
#include "NetworkSystem.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"

namespace Cpf
{
	class Networked : public Adapter::WindowedApp
	{
	public:
		Networked();
		~Networked() override;

		int Start(const CommandLine&) override;

	private:
		bool _CreateWindow();
		bool _Install();
		bool _Remove();
		bool _InitializeResources();
		bool _ShutdownResources();
		bool _InitializeMultiCore();
		bool _ShutdownMultiCore();
		bool _InitializePipeline();
		bool _ConfigurePipeline();
		bool _ShutdownPipeline();

		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;

		Concurrency::Scheduler mLoopScheduler;
		Concurrency::ThreadPool mThreadPool;
		Concurrency::LoadBalancer mLoadBalancer;
		IntrusivePtr<Resources::Locator> mpLocator;

		IntrusivePtr<MultiCore::Pipeline> mpPipeline;
		IntrusivePtr<NetworkSystem> mpNetworkSystem;
		IntrusivePtr<RenderSystem> mpRenderSystem;
	};
}
