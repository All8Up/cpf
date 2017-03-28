//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Math/Rectangle.hpp"
#include "Math/Vector4v.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class PrimitiveTopology;
		struct ResourceData;
		class iDevice;
		class iSwapChain;
		class iCommandPool;
		class iImage;
		class iSampler;
		class iImageView;
		class iResource;
		class iResourceBinding;
		class iIndexBuffer;
		class iVertexBuffer;
		class iPipeline;
		class iConstantBuffer;

		struct DepthStencilClearFlag
		{
			enum : uint32_t
			{
				eDepth = 1 << 0,
				eStencil = 1 << 1
			};
		};

		enum class ResourceState : int32_t
		{
			eCommon = 0x00,
			ePresent = eCommon,
			eVertexAndConstant = 0x01,
			eIndex = 0x02,
			eRenderTarget = 0x04,
			eUnorderedAccess = 0x08,
			eDepthWrite = 0x10,
			eDepthRead = 0x20,
			eNonPixelShaderResource = 0x40,
			ePixelShaderResource = 0x80,
			eStreamOut =  0x100,
			eIndirectArgument = 0x200,
			eCopyDest = 0x400,
			eCopySource = 0x800,
			eResolveDest = 0x1000,
			eResolveSource = 0x2000,
			ePredication = eIndirectArgument,
			eGenericRead = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800)
		};

		enum class SubResource : int32_t
		{
			eAll
		};

		struct Viewport
		{
			float mX;
			float mY;
			float mWidth;
			float mHeight;
			float mMinDepth;
			float mMaxDepth;
		};

		class iCommandBuffer : public iRefCounted
		{
		public:
			virtual ~iCommandBuffer() = 0;

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
			virtual void ClearDepthStencilView(iImageView* view, uint32_t flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects) = 0;
		};
	}
}
