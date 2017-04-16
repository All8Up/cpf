//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplicationMain.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/iWindow.hpp"
#include "MultiCore/iPipeline.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "Resources/Locator.hpp"
#include "NanoVG/nanovg.h"
#include "Math/Vector2v.hpp"

namespace Cpf
{
	class BgfxIntegration : public tRefCounted<iApplicationMain>
	{
	public:
		BgfxIntegration();
		~BgfxIntegration();

		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }

		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, COM::ClassID* appCid) override;
		COM::Result CPF_STDCALL Main(iApplication* application) override;
		void CPF_STDCALL Shutdown() override;

		Plugin::iRegistry* GetRegistry() { return mpRegistry; }

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
		IntrusivePtr<MultiCore::iTimer> mpTimer;

		IntrusivePtr<Resources::Locator> mpLocator;

		uint32_t mResetFlags;

		int32_t mSelectedRenderDevice;

		NVGcontext* mNvg;
		int mFont;

		Plugin::iRegistry* mpRegistry;
		iWindowedApplication* mpApplication;
	};
}
