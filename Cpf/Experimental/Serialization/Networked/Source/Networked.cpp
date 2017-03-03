#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "asio.hpp"
#include "MultiCore.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Threading;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
Networked::Networked()
{
	CPF_INIT_LOG(Networked);
}

Networked::~Networked()
{
	CPF_DROP_LOG(Networked);
}

void Networked::_Resize(int32_t width, int32_t height)
{
}

int Networked::Start(const CommandLine&)
{
	// Initialize libraries.
	ScopedInitializer<TimeInitializer> timeInit;
	ScopedInitializer<MultiCoreInitializer> multicoreInit;

	// Create the main window.
	Math::Vector2i mWindowSize(1920, 1080);
	mpWindow.Adopt(
		WindowDesc(this)
		.Title("Network Test")
		.Position(iWindow::Centered)
		.Size(mWindowSize)
		.Flags(iWindow::eResizable | iWindow::eShown)
	);

	if (mpWindow)
	{
		// Bind the window events.
		mpWindow->GetEmitter().On<iWindow::OnResized>(Bind(&Networked::_Resize, this, Placeholders::_1, Placeholders::_2));

		// Bring up the scheduler and pipeline.
		mScheduler.Initialize(
			Move(Thread::Group(Thread::GetHardwareThreadCount()))
		);
		if (Pipeline::Create(mpPipeline.AsTypePP()) && mpPipeline->Configure())
		{
			Concurrency::Scheduler::Semaphore complete;

			// Run the event loop for the window.
			while (IsRunning())
			{
				Poll();
				(*mpPipeline)(mScheduler);
				mScheduler.Submit(complete);
				complete.Acquire();
			}
		}
	}

	// Shutdown the scheduler.
	mScheduler.Shutdown();

	// Destroy the window and exit.
	mpWindow.Assign(nullptr);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPLICATION(Cpf::Networked);
