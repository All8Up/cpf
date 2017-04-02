//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "MultiCore/iPipeline.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "Resources/Locator.hpp"
#include "NanoVG/nanovg.h"

namespace Cpf
{
	class BgfxIntegration : public Adapter::WindowedApp
	{
	public:
		BgfxIntegration();
		~BgfxIntegration() override;

		int Start(const CommandLine&) override;

	private:
		bool _CreateWindow();
		bool _InitializeResources();
		bool _InitializeConcurrency();
		bool _InitializePipeline();
		bool _SelectRenderDevice();

		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;
		Math::Vector2i mWindowSize;

		Concurrency::Scheduler mScheduler;
		Concurrency::ThreadPool mThreadPool;
		Concurrency::LoadBalancer mLoadBalancer;

		IntrusivePtr<MultiCore::iPipeline> mpPipeline;
		IntrusivePtr<MultiCore::Timer> mpTimer;

		IntrusivePtr<Resources::Locator> mpLocator;

		uint32_t mResetFlags;

		int32_t mSelectedRenderDevice;

		NVGcontext* mNvg;
		int mFont;
	};
}
