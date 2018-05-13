//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "CPF/Configuration.hpp"
#include "gtest/gtest.h"
#include "CPF/Platform/Concurrency/iFence.hpp"
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/Threading/Thread.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, All_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace CPF;
	using namespace Platform;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<iScheduler> pScheduler;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iScheduler::kCID, iScheduler::kIID, pScheduler.AsVoidPP())));
	EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

	IntrusivePtr<iFence> pFence;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iFence::kCID, iFence::kIID, pFence.AsVoidPP())));

	IntrusivePtr<iWorkBuffer> pWorkBuffer;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

	//////////////////////////////////////////////////////////////////////////
	EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);

	pScheduler->SetActiveThreads(4);
	{
		//////////////////////////////////////////////////////////////////////////
		std::atomic<int> hitCount = 0;
		for (int i=0; i<25; ++i)
		{
			pWorkBuffer->All( [](const WorkContext*, void* context)
			{
				(*reinterpret_cast<std::atomic<int>*>(context)).fetch_add(1);
			},
				&hitCount);
		}
		pScheduler->Execute(pWorkBuffer);
		pWorkBuffer->Reset();
		pScheduler->Submit(pFence);
		pFence->Wait();
		EXPECT_EQ(4 * 25, hitCount);
	}
	pScheduler->Shutdown();
}
