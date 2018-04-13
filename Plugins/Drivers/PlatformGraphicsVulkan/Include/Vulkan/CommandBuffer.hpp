//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iCommandBuffer.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Vulkan
	{
		class Device;
		class CommandPool;

		class CommandBuffer : public GOM::tUnknown <Graphics::iCommandBuffer>
		{
		public:
			// Internal
			GOM::Result Initialize(Device* device, CommandPool* pool, Graphics::CommandBufferType type);
			VkCommandBuffer GetVkCommandBuffer() const { return mCommandBuffer; }

			// iCommandBuffer overrides.
			void CPF_STDCALL Begin(iCommandBuffer* primary) override;
			void CPF_STDCALL End() override;
			void CPF_STDCALL Reset(Graphics::iCommandPool* pool) override;
			void CPF_STDCALL UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data) override;
			void CPF_STDCALL CopyResource(Graphics::iResource* src, Graphics::iResource* dst) override;
			void CPF_STDCALL ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startStart, Graphics::ResourceState endState) override;
			void CPF_STDCALL ImageTransition(Graphics::iImage* image, Graphics::ResourceState startState, Graphics::ResourceState endState, Graphics::SubResource subResources) override;
			void CPF_STDCALL SetResourceBinding(Graphics::iResourceBinding* binding) override;
			void CPF_STDCALL SetPipeline(Graphics::iPipeline* pipeline) override;
			void CPF_STDCALL SetViewports(int32_t count, const Graphics::Viewport* rects) override;
			void CPF_STDCALL SetScissorRects(int32_t count, const Math::Rectanglei* rects) override;
			void CPF_STDCALL SetTopology(Graphics::PrimitiveTopology topology) override;
			void CPF_STDCALL SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer** outVB) override;
			void CPF_STDCALL SetIndexBuffer(Graphics::iIndexBuffer* ib) override;
			void CPF_STDCALL SetConstantBuffer(int32_t index, Graphics::iConstantBuffer* cb) override;
			void CPF_STDCALL SetConstants(int32_t index, int32_t count, const void* data, int32_t offset) override;
			void CPF_STDCALL SetSampler(int32_t index, Graphics::iSampler* sampler) override;
			void CPF_STDCALL SetImage(int32_t index, Graphics::iImage* image) override;
			void CPF_STDCALL DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance) override;
			void CPF_STDCALL DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance) override;
			GOM::Result CPF_STDCALL BeginRenderPass(Graphics::RenderPassBeginDesc* rpbd) override;
			GOM::Result CPF_STDCALL NextSubPass() override;
			GOM::Result CPF_STDCALL EndRenderPass() override;
			GOM::Result CPF_STDCALL Insert(int32_t count, iCommandBuffer* const * icb) override;

		private:
			Device* mpDevice;
			VkCommandBuffer mCommandBuffer;
		};
	}
}
