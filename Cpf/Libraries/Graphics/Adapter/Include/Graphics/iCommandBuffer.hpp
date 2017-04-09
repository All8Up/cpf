//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
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

		enum class PrimitiveTopology;
		struct ResourceData;
		class iSwapChain;
		struct iCommandPool;
		class iImage;
		class iSampler;
		class iImageView;
		class iResourceBinding;
		class iPipeline;
		struct Viewport;
		enum class SubResource : int32_t;
		enum class ResourceState : int32_t;
		enum class DepthStencilClearFlag : int32_t;

		struct iCommandBuffer : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iCommandBuffer"_crc64);

			virtual void Begin() = 0;
			virtual void End() = 0;

			virtual void Reset(iCommandPool*) = 0;

			virtual void UpdateSubResource(iResource* src, iResource* dst, const ResourceData* data) = 0;

			virtual void ResourceBarrier(iResource* resource, ResourceState startStart, ResourceState endState) = 0;
			virtual void ImageTransition(iImage* image, ResourceState startState, ResourceState endState, SubResource subResources) = 0;

			virtual void SetResourceBinding(iResourceBinding* binding) = 0;
			virtual void SetPipeline(iPipeline* pipeline) = 0;
			virtual void SetViewports(int32_t count, const Viewport* rects) = 0;
			virtual void SetScissorRects(int32_t count, const Math::Rectanglei* rects) = 0;
			virtual void SetTopology(PrimitiveTopology topology) = 0;
			virtual void SetVertexBuffers(int32_t startSlot, int32_t viewCount, iVertexBuffer**) = 0;
			virtual void SetIndexBuffer(iIndexBuffer*) = 0;
			virtual void SetConstantBuffer(int32_t index, iConstantBuffer*) = 0;
			virtual void SetConstants(int32_t index, int32_t count, const void*, int32_t offset = 0) = 0;
			virtual void SetSampler(int32_t index, iSampler*) = 0;
			virtual void SetImage(int32_t index, iImage*) = 0;

			virtual void DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance) = 0;
			virtual void DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance) = 0;

			virtual void SetRenderTargets(int32_t imageCount, iImageView** images, iImageView* depthView) = 0;
			virtual void ClearRenderTargetView(iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects) = 0;
			virtual void ClearDepthStencilView(iImageView* view, DepthStencilClearFlag flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects) = 0;

			/*
			virtual bool BeginRenderPass(iRenderPass*) = 0;
			virtual bool EndRenderPass(iRenderPass*) = 0;
			*/
		};
	}
}
