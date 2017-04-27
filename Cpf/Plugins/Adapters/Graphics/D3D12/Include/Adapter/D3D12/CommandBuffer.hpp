//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/iCommandBuffer.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"
#include "IntrusivePtr.hpp"
#include <d3d12.h>
#include "Math/Rectangle.hpp"
#include "UnorderedSet.hpp"


namespace Cpf
{
	namespace Math {
		class Color4f;
	}

	namespace Graphics
	{
		struct iDevice;
		struct iCommandPool;
		struct iConstantBuffer;
		struct iResource;
		struct iFence;
		struct iImageView;
		struct iSampler;
		struct iPipeline;
		struct iVertexBufferView;
		struct iResourceBinding;
		struct iSwapChain;
		struct ResourceData;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr COM::ClassID kCommandBufferCID = COM::ClassID("Adapter::D3D12::CommandBuffer"_crc64);

			class CommandBuffer : public tRefCounted<Graphics::iCommandBuffer>
			{
			public:
				CommandBuffer(COM::iUnknown*);
				virtual ~CommandBuffer();

				//
				COM::Result CPF_STDCALL Initialize(Graphics::iDevice*, Graphics::iCommandPool*);

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				void Begin() override;
				void End() override;
				void Reset(Graphics::iCommandPool*) override;

				void UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data) override;

				void ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startStart, Graphics::ResourceState endState) override;
				void ImageTransition(Graphics::iImage* image, Graphics::ResourceState startState, Graphics::ResourceState endState, Graphics::SubResource subResources) override;

				void SetResourceBinding(Graphics::iResourceBinding* binding) override;
				void SetPipeline(Graphics::iPipeline* pipeline) override;
				void SetViewports(int32_t count, const Graphics::Viewport* rects) override;
				void SetScissorRects(int32_t count, const Math::Rectanglei* rects) override;
				void SetTopology(Graphics::PrimitiveTopology topology) override;
				void SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer**) override;
				void SetIndexBuffer(Graphics::iIndexBuffer*) override;
				void SetConstantBuffer(int32_t index, Graphics::iConstantBuffer*) override;
				void SetConstants(int32_t index, int32_t count, const void*, int32_t offset = 0) override;
				void SetSampler(int32_t index, Graphics::iSampler*) override;
				void SetImage(int32_t index, Graphics::iImage*) override;

				void DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance) override;
				void DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance) override;

				void SetRenderTargets(int32_t imageCount, Graphics::iImageView** images, Graphics::iImageView* depthView) override;

				void ClearRenderTargetView(Graphics::iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects) override;
				void ClearDepthStencilView(Graphics::iImageView* view, Graphics::DepthStencilClearFlag flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects) override;

				COM::Result CPF_STDCALL BeginRenderPass(Graphics::RenderPassBeginDesc*) override;
				COM::Result CPF_STDCALL NextSubPass() override;
				COM::Result CPF_STDCALL EndRenderPass() override;

				//////////////////////////////////////////////////////////////////////////
				// D3D12 specific implementation details.
				void Submit(ID3D12CommandQueue* queue);
				ID3D12GraphicsCommandList* GetCommandList() { return mpCommandList.Cast<ID3D12GraphicsCommandList>(); }

			private:
				friend class Device;
				IntrusivePtr<ID3D12GraphicsCommandList> mpCommandList;

				// Temporary.
				Device* mpDevice;

				UnorderedSet<ID3D12DescriptorHeap*> mHeaps;

				Graphics::RenderPassBeginDesc mRenderPass;
			};
		}
	}
}
