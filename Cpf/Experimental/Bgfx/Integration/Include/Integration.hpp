//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "MultiCore/Pipeline.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "Resources\Locator.hpp"

namespace Cpf
{
	class BgfxIntegration : public Adapter::WindowedApp
	{
	public:
		BgfxIntegration();
		~BgfxIntegration() override;

		int Start(const CommandLine&) override;

	private:
		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;
		Math::Vector2i mWindowSize;

		Concurrency::Scheduler mScheduler;
		Concurrency::ThreadPool mThreadPool;
		Concurrency::LoadBalancer mLoadBalancer;

		IntrusivePtr<Resources::Locator> mpLocator;

		uint32_t mResetFlags;
	};
}
