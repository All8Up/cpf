//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/iCommandPool.hpp"
#include "IntrusivePtr.hpp"
#include <d3d12.h>


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class CommandPool : public tRefCounted<Graphics::iCommandPool>
			{
			public:
				CommandPool(Device* device);
				~CommandPool() override;

				void Reset() override;

				ID3D12CommandAllocator* GetCommandAllocator() const { return mpCommandPool; }

			private:
				IntrusivePtr<ID3D12CommandAllocator> mpCommandPool;
			};
		}
	}
}
