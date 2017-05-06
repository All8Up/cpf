//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iIndexBuffer.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Graphics
	{
		enum class HeapType : int32_t;
		struct ResourceDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class IndexBuffer : public tRefCounted<Graphics::iIndexBuffer>
			{
			public:
				IndexBuffer(Device* device, const Graphics::ResourceDesc* desc, Graphics::Format format);
				virtual ~IndexBuffer();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				ID3D12Resource* GetResource() const;
				const D3D12_INDEX_BUFFER_VIEW* GetView() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				D3D12_INDEX_BUFFER_VIEW mView;
				size_t mSize;
			};
		}
	}
}
