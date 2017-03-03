//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "Concurrency/Scheduler.hpp"
#include "MultiCore/Pipeline.hpp"

namespace Cpf
{
	class Networked : public Adapter::WindowedApp
	{
	public:
		Networked();
		~Networked() override;

		int Start(const CommandLine&) override;

	private:
		void _Resize(int32_t width, int32_t height);

		IntrusivePtr<iWindow> mpWindow;

		Concurrency::Scheduler mScheduler;
		IntrusivePtr<MultiCore::Pipeline> mpPipeline;
	};
}
