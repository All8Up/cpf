//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iFence.hpp"
#include "D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include <atomic>

namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class Fence final : public GOM::tUnknown<Graphics::iFence>
			{
			public:
				Fence(Device*, bool signaled);
				virtual ~Fence();

				// Overrides from iFence.
				Graphics::FenceStatus GetStatus() const override;
				void CPF_STDCALL Reset() override;
				Graphics::FenceStatus CPF_STDCALL Wait() const override;

				ID3D12Fence* GetD3DFence() const { return mpFence; }
				uint64_t GetTarget() const { return mTarget; }

			private:
				IntrusivePtr<ID3D12Fence> mpFence;
				HANDLE mEvent;
				std::atomic<uint64_t> mTarget;
			};
		}
	}
}
