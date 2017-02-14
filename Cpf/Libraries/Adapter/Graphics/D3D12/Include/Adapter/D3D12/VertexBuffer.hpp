//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iVertexBuffer.hpp"
#include "Graphics/BufferUsage.hpp"
#include "Adapters/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;


			class VertexBuffer : public tRefCounted<Graphics::iVertexBuffer>
			{
			public:
				VertexBuffer(Device* device, Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData);
				~VertexBuffer() override;

				bool Map(int32_t start, int32_t end, void**) override;
				bool Unmap() override;

				ID3D12Resource* GetResource() const;
				const D3D12_VERTEX_BUFFER_VIEW* GetView() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				D3D12_VERTEX_BUFFER_VIEW mView;
				size_t mSize;
				size_t mStride;
				void* mpMapping;
			};
		}
	}
}
