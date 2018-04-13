//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iVertexBuffer.hpp"
#include "CPF/Platform/Graphics/ResourceDesc.hpp"
#include "Driver/D3D12/D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class HeapType : int32_t;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Device;


			class VertexBuffer final : public GOM::tUnknown<Graphics::iVertexBuffer>
			{
			public:
				VertexBuffer(Device* device, const Graphics::ResourceDesc* desc, int32_t stride);
				virtual ~VertexBuffer();

				GOM::Result QueryInterface(GOM::IID id, void** outIface) override;

				bool Map(void**, const Graphics::Range*) override;
				void Unmap(const Graphics::Range*) override;

				ID3D12Resource* GetResource() const;
				const D3D12_VERTEX_BUFFER_VIEW* GetView() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				D3D12_VERTEX_BUFFER_VIEW mView;
				Graphics::ResourceDesc mDesc;
			};
		}
	}
}
