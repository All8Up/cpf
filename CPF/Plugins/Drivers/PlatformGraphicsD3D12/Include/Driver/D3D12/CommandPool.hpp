//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Platform/Graphics/iCommandPool.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include <d3d12.h>


namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class CommandPool : public GOM::tUnknown<Graphics::iCommandPool>
			{
			public:
				CommandPool();
				virtual ~CommandPool();

				GOM::Result CPF_STDCALL Initialize(Device* device);

				void Reset() override;

				ID3D12CommandAllocator* GetCommandAllocator() const { return mpCommandPool; }

			private:
				IntrusivePtr<ID3D12CommandAllocator> mpCommandPool;
			};
		}
	}
}
