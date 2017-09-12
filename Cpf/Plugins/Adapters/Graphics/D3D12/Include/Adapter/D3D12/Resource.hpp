//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"
#include "D3D12Utils.hpp"
#include "IntrusivePtr.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct Range;
		struct ResourceDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			static constexpr GOM::ClassID kResourceCID = GOM::ClassID("Adapter::D3D12::Resource"_crc64);

			class Resource : public tRefCounted<Graphics::iResource>
			{
			public:
				Resource(Device* device, const Graphics::ResourceDesc* desc);
				virtual ~Resource();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				ID3D12Resource* GetResource() const { return mpResource; }
				D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
			};
		}
	}
}
