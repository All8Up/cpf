//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplicationMain.hpp"
#include "Application/iWindowedApplication.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "RenderSystem.hpp"
#include "Concurrency/iThreadPool.hpp"
#include "Concurrency/iLoadBalancer.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "Resources/iLocator.hpp"
//#include "iPython.hpp"

namespace CPF
{
	class StarterApp : public tRefCounted<iApplicationMain>
	{
	public:
		StarterApp();
		~StarterApp() override;

		GOM::Result CPF_STDCALL QueryInterface(uint64_t, void**) override { return GOM::kNotImplemented; }

		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, GOM::ClassID* appCid) override;
		GOM::Result CPF_STDCALL Main(iApplication* application) override;
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
		GOM::Result _ConfigurePipeline();
		bool _ShutdownPipeline();

		// Debug panels.
		static void _PerformanceUI(Graphics::iDebugUI*, void*);

		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;

		IntrusivePtr<Concurrency::iScheduler> mpScheduler;
		IntrusivePtr<iThreadPool> mpThreadPool;
		IntrusivePtr<Concurrency::iLoadBalancer> mpLoadBalancer;
		IntrusivePtr<Resources::iLocator> mpLocator;

		IntrusivePtr<MultiCore::iExecutionPlan> mpPipeline;
		IntrusivePtr<MultiCore::iTimer> mpTimer;
		IntrusivePtr<RenderSystem> mpRenderSystem;

//		IntrusivePtr<Tools::iPython3> mpPython3;

		Time::Value mLastTime;

		Plugin::iRegistry* mpRegistry;
		iWindowedApplication* mpWindowedApplication;
	};
}
