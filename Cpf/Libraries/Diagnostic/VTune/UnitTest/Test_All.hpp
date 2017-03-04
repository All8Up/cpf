//////////////////////////////////////////////////////////////////////////
#pragma once
#include "VTune/VTune.hpp"
#include "Threading/Thread.hpp"
#include "Time/Unit.hpp"
#include "Threading.hpp"


TEST(VTune, AllTests)
{
	Cpf::ScopedInitializer<Cpf::ThreadingInitializer> threadingInit;

	// Setup test domains.
	VTune::Domain* frameDomain = VTune::DomainCreate("test name");
	VTune::Domain* innerDomain = VTune::DomainCreate("inner");

	// Create test events.
	VTune::Event testEvent = VTune::EventCreate("event", 5);

	// Create utility strings.
	VTune::StringHandle* taskName = VTune::StringHandleCreate("test task");

	// Create test sync.
	VTune::SyncCreate(&frameDomain, "TestType", "TestSync", VTune::SyncType::eMutex);
	VTune::SyncRename(&frameDomain, "TestSync2");

	// Begin a frame.
	VTune::BeginFrame(frameDomain);

	// Offset to the event.
	Cpf::Threading::Thread::Sleep(Cpf::Platform::Time::Seconds(0.1f));

	// Start a sync.
	VTune::SyncPrepare(&frameDomain);
	VTune::SyncAcquired(&frameDomain);

	// Trigger an event.
	VTune::EventStart(testEvent);

	// Trigger an inner task.
	VTune::TaskBegin(innerDomain, taskName);

	// Sleep for a second.
	Cpf::Threading::Thread::Sleep(Cpf::Platform::Time::Seconds(1.0f));

	// End the event.
	VTune::EventEnd(testEvent);

	// End the task.
	VTune::TaskEnd(innerDomain);

	// End the sync.
	VTune::SyncReleasing(&frameDomain);

	// Offset before end frame.
	Cpf::Threading::Thread::Sleep(Cpf::Platform::Time::Seconds(0.1f));

	// End the frame.
	VTune::EndFrame(frameDomain);

	// Destroy the sync.
	VTune::SyncDestroy(&frameDomain);
}
