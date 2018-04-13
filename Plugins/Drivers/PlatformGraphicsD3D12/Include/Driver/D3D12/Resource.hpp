//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iResource.hpp"
#include "D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct Range;
		struct ResourceDesc;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			static constexpr GOM::ClassID kResourceCID = GOM::ClassID("Adapter::D3D12::Resource"_crc64);

			class Resource final : public GOM::tUnknown<Graphics::iResource>
			{
			public:
				Resource(Device* device, const Graphics::ResourceDesc* desc);
				virtual ~Resource();

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
