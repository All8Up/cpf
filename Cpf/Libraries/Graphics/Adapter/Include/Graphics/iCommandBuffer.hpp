//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "Math/Rectangle.hpp"
#include "Math/Vector4v.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;
		struct iConstantBuffer;
		struct iResource;
		struct iIndexBuffer;
		struct iVertexBuffer;
		struct iImage;
		struct iImageView;
		struct iSwapChain;
		struct iCommandPool;
		struct iSampler;
		struct iResourceBinding;
		struct iPipeline;

		enum class PrimitiveTopology;
		struct ResourceData;
		struct Viewport;
		struct RenderPassBeginDesc;
		enum class SubResource : int32_t;
		enum class ResourceState : int32_t;
		enum class DepthStencilClearFlag : int32_t;

		static constexpr GOM::Result kAlreadyInRenderPass = GOM::CreateResult(1, "Graphics"_crc16, "Already in render pass"_crc15);
		static constexpr GOM::Result kNotInRenderPass = GOM::CreateResult(1, "Graphics"_crc16, "Not in a render pass"_crc15);

		enum class CommandBufferType : int32_t
		{
			kPrimary = 0,
			kSecondary = 1,
			kCompute = 2,
			kCopy = 3
		};

		struct iCommandBuffer : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iCommandBuffer"_crc64);

			virtual void CPF_STDCALL Begin(iCommandBuffer* primary) = 0;
			virtual void CPF_STDCALL End() = 0;

			virtual void CPF_STDCALL Reset(iCommandPool*) = 0;

			virtual void CPF_STDCALL UpdateSubResource(iResource* src, iResource* dst, const ResourceData* data) = 0;

			virtual void CPF_STDCALL CopyResource(iResource* src, iResource* dst) = 0;

			virtual void CPF_STDCALL ResourceBarrier(iResource* resource, ResourceState startStart, ResourceState endState) = 0;
			virtual void CPF_STDCALL ImageTransition(iImage* image, ResourceState startState, ResourceState endState, SubResource subResources) = 0;

			virtual void CPF_STDCALL SetResourceBinding(iResourceBinding* binding) = 0;
			virtual void CPF_STDCALL SetPipeline(iPipeline* pipeline) = 0;
			virtual void CPF_STDCALL SetViewports(int32_t count, const Viewport* rects) = 0;
			virtual void CPF_STDCALL SetScissorRects(int32_t count, const Math::Rectanglei* rects) = 0;
			virtual void CPF_STDCALL SetTopology(PrimitiveTopology topology) = 0;
			virtual void CPF_STDCALL SetVertexBuffers(int32_t startSlot, int32_t viewCount, iVertexBuffer**) = 0;
			virtual void CPF_STDCALL SetIndexBuffer(iIndexBuffer*) = 0;
			virtual void CPF_STDCALL SetConstantBuffer(int32_t index, iConstantBuffer*) = 0;
			virtual void CPF_STDCALL SetConstants(int32_t index, int32_t count, const void*, int32_t offset = 0) = 0;
			virtual void CPF_STDCALL SetSampler(int32_t index, iSampler*) = 0;
			virtual void CPF_STDCALL SetImage(int32_t index, iImage*) = 0;

			virtual void CPF_STDCALL DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance) = 0;
			virtual void CPF_STDCALL DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance) = 0;

			// Render passes.
			virtual GOM::Result CPF_STDCALL BeginRenderPass(RenderPassBeginDesc*) = 0;
			virtual GOM::Result CPF_STDCALL NextSubPass() = 0;
			virtual GOM::Result CPF_STDCALL EndRenderPass() = 0;

			// Secondary command buffer insertion.
			virtual GOM::Result CPF_STDCALL Insert(int32_t count, iCommandBuffer* const*) = 0;
		};
	}
}
