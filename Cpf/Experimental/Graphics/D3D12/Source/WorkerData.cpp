//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"

using namespace Cpf;

void ExperimentalD3D12::_CreateWorkerData(Concurrency::ThreadContext& tc)
{
	ThreadData& td = mWorkerData[tc.GetThreadIndex()];
	tc.SetUserData(&td);

	for (int i = 0; i < mBackBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(td.mpCommandPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(td.mpCommandPool[i], td.mpCommandBuffer[i].AsTypePP());

#ifdef CPF_DEBUG
		mpDevice->CreateCommandPool(td.mpDebugUIPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(td.mpDebugUIPool[i], td.mpDebugUIBuffer[i].AsTypePP());
#endif
	}
}

void ExperimentalD3D12::_DestroyWorkerData(Concurrency::ThreadContext& tc)
{
	ThreadData& td = mWorkerData[tc.GetThreadIndex()];

	for (int i = 0; i < mBackBufferCount; ++i)
	{
		td.mpCommandBuffer[i].Assign(nullptr);
		td.mpCommandPool[i].Assign(nullptr);

#ifdef CPF_DEBUG
		td.mpDebugUIBuffer[i].Assign(nullptr);
		td.mpDebugUIPool[i].Assign(nullptr);
#endif
	}
}
