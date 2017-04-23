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
				CommandPool();
				virtual ~CommandPool();

				COM::Result CPF_STDCALL Initialize(Device* device);

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

				void Reset() override;

				ID3D12CommandAllocator* GetCommandAllocator() const { return mpCommandPool; }

			private:
				IntrusivePtr<ID3D12CommandAllocator> mpCommandPool;
			};
		}
	}
}
