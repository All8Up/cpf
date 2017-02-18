//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iIndexBuffer.hpp"
#include "Graphics/BufferUsage.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class IndexBuffer : public tRefCounted<Graphics::iIndexBuffer>
			{
			public:
				IndexBuffer(Device* device, Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData);
				~IndexBuffer() override;

				bool Map(int32_t start, int32_t end, void**) override;
				bool Unmap() override;

				ID3D12Resource* GetResource() const;
				const D3D12_INDEX_BUFFER_VIEW* GetView() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				D3D12_INDEX_BUFFER_VIEW mView;
				size_t mSize;
				void* mpMapping;
			};
		}
	}
}
