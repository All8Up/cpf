//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"

TEST_F(ConcurrencyTest, All_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Cpf;
	using namespace Concurrency;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<iScheduler> pScheduler;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
	EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

	IntrusivePtr<iFence> pFence;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

	IntrusivePtr<iWorkBuffer> pWorkBuffer;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

	//////////////////////////////////////////////////////////////////////////
	EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);

	pScheduler->SetActiveThreads(4);
	{
		//////////////////////////////////////////////////////////////////////////
		int hitCount = 0;
		for (int i=0; i<25; ++i)
		{
			pWorkBuffer->All( [](const WorkContext*, void* context)
			{
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
				&hitCount);
		}
		pScheduler->Execute(pWorkBuffer);
		pScheduler->Submit(pFence);
		pFence->Wait();
		EXPECT_EQ(4 * 25, hitCount);
	}
	pScheduler->Shutdown();
}
