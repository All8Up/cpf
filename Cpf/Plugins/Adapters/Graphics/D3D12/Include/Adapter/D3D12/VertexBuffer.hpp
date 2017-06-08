//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iVertexBuffer.hpp"
#include "Graphics/ResourceDesc.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Graphics
	{
		enum class HeapType : int32_t;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;


			class VertexBuffer : public tRefCounted<Graphics::iVertexBuffer>
			{
			public:
				VertexBuffer(Device* device, const Graphics::ResourceDesc* desc, int32_t stride);
				virtual ~VertexBuffer();

				GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

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
