//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "MultiCore/Pipeline.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "MultiCore/System/Timer.hpp"

namespace Cpf
{
	class BgfxIntegration : public Adapter::WindowedApp
	{
	public:
		BgfxIntegration();
		~BgfxIntegration() override;

		int Start(const CommandLine&) override;

	private:
	};
}
