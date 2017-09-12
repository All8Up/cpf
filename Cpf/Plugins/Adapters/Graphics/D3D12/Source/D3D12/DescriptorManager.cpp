//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/DescriptorManager.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Adapter;
using namespace D3D12;

Descriptor::Descriptor()
	: mpManager(nullptr)
	, mIndex(DescriptorManager::kInvalid)
{}

Descriptor::Descriptor(DescriptorManager* mgr, size_t index)
	: mpManager(mgr)
	, mIndex(index)
{}

Descriptor::Descriptor(Descriptor&& rhs)
	: mpManager(rhs.mpManager)
	, mIndex(rhs.mIndex)
{
	rhs.mIndex = DescriptorManager::kInvalid;
}

Descriptor::~Descriptor()
{
	if (mIndex != DescriptorManager::kInvalid)
		mpManager->_Free(mIndex);
}

DescriptorManager* Descriptor::GetManager() const
{
	return mpManager;
}

Descriptor& Descriptor::operator =(Descriptor&& rhs)
{
	if (mIndex != DescriptorManager::kInvalid)
		mpManager->_Free(mIndex);

	mpManager = rhs.mpManager;
	mIndex = rhs.mIndex;
	rhs.mIndex = DescriptorManager::kInvalid;

	return *this;
}

Descriptor::operator D3D12_CPU_DESCRIPTOR_HANDLE () const
{
	D3D12_CPU_DESCRIPTOR_HANDLE result = mpManager->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	result.ptr += mIndex * mpManager->GetIncrement();
	return result;
}

Descriptor::operator D3D12_GPU_DESCRIPTOR_HANDLE () const
{
	D3D12_GPU_DESCRIPTOR_HANDLE result = mpManager->GetHeap()->GetGPUDescriptorHandleForHeapStart();
	result.ptr += mIndex * mpManager->GetIncrement();
	return result;
}

//////////////////////////////////////////////////////////////////////////
DescriptorManager::DescriptorManager()
	: mpDevice(nullptr)
	, mIncrement(0)
	, mNextFree(0)
{
}

DescriptorManager::~DescriptorManager()
{}

bool DescriptorManager::Initialize(Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags, size_t count)
{
	mpDevice = device;
	if (device)
	{
		ID3D12Device* d3d12Device = device->GetD3DDevice();
		{
			D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
			ZeroMemory(&heapDesc, sizeof(heapDesc));
			heapDesc.NumDescriptors = UINT(count);
			heapDesc.Type = heapType;
			heapDesc.Flags = heapFlags;
			if (FAILED(d3d12Device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(mpDescriptorHeap.AsTypePP()))))
			{
				mpDevice = nullptr;
				return false;
			}
			mIncrement = size_t(d3d12Device->GetDescriptorHandleIncrementSize(heapType));

			// Initialize the free list.
			mFreeList.resize(count);
			for (auto ibegin = mFreeList.begin(), iend = mFreeList.end(); ibegin != iend; ++ibegin)
				*ibegin = size_t(ibegin - mFreeList.begin()) + 1;
			mFreeList.back() = kInvalid;
		}
		return true;
	}
	return false;
}

bool DescriptorManager::Shutdown()
{
	return true;
}

Descriptor DescriptorManager::Alloc()
{
	return Descriptor(this, _Alloc());
}

size_t DescriptorManager::_Alloc()
{
	size_t index = mNextFree;
	if (index != kInvalid)
	{
		mNextFree = mFreeList[index];
		return index;
	}
	return kInvalid;
}

void DescriptorManager::_Free(size_t index)
{
	CPF_ASSERT(index != DescriptorManager::kInvalid);
	mFreeList[index] = mNextFree;
	mNextFree = size_t(index);
}
