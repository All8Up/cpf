//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "Graphics/iCommandBuffer.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"
#include <d3d12.h>
#include "Math/Rectangle.hpp"
#include "Math/Vector4v.hpp"
#include "UnorderedSet.hpp"
#include "Vector.hpp"


namespace CPF
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
			class Image;

			static constexpr GOM::ClassID kCommandBufferCID = GOM::ClassID("Adapter::D3D12::CommandBuffer"_crc64);

			class CommandBuffer : public tRefCounted<Graphics::iCommandBuffer>
			{
			public:
				CommandBuffer(GOM::iUnknown*);
				virtual ~CommandBuffer();

				//
				GOM::Result CPF_STDCALL Initialize(Graphics::iDevice*, Graphics::CommandBufferType type, Graphics::iCommandPool*);

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				void CPF_STDCALL Begin(iCommandBuffer* primary) override;
				void CPF_STDCALL End() override;
				void CPF_STDCALL Reset(Graphics::iCommandPool*) override;

				void CPF_STDCALL UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data) override;
				void CPF_STDCALL CopyResource(Graphics::iResource* src, Graphics::iResource* dst) override;

				void CPF_STDCALL ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startStart, Graphics::ResourceState endState) override;
				void CPF_STDCALL ImageTransition(Graphics::iImage* image, Graphics::ResourceState startState, Graphics::ResourceState endState, Graphics::SubResource subResources) override;

				void CPF_STDCALL SetResourceBinding(Graphics::iResourceBinding* binding) override;
				void CPF_STDCALL SetPipeline(Graphics::iPipeline* pipeline) override;
				void CPF_STDCALL SetViewports(int32_t count, const Graphics::Viewport* rects) override;
				void CPF_STDCALL SetScissorRects(int32_t count, const Math::Rectanglei* rects) override;
				void CPF_STDCALL SetTopology(Graphics::PrimitiveTopology topology) override;
				void CPF_STDCALL SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer**) override;
				void CPF_STDCALL SetIndexBuffer(Graphics::iIndexBuffer*) override;
				void CPF_STDCALL SetConstantBuffer(int32_t index, Graphics::iConstantBuffer*) override;
				void CPF_STDCALL SetConstants(int32_t index, int32_t count, const void*, int32_t offset = 0) override;
				void CPF_STDCALL SetSampler(int32_t index, Graphics::iSampler*) override;
				void CPF_STDCALL SetImage(int32_t index, Graphics::iImage*) override;

				void CPF_STDCALL DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance) override;
				void CPF_STDCALL DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance) override;


				GOM::Result CPF_STDCALL BeginRenderPass(Graphics::RenderPassBeginDesc*) override;
				GOM::Result CPF_STDCALL NextSubPass() override;
				GOM::Result CPF_STDCALL EndRenderPass() override;

				GOM::Result CPF_STDCALL Insert(int32_t count, iCommandBuffer* const *) override;

				//////////////////////////////////////////////////////////////////////////
				// D3D12 specific implementation details.
				void Submit(ID3D12CommandQueue* queue);
				ID3D12GraphicsCommandList* GetCommandList() { return _Current(); }

				void CPF_STDCALL SetRenderTargets(int32_t imageCount, Graphics::iImageView** images, Graphics::iImageView* depthView);
				void CPF_STDCALL ClearRenderTargetView(Graphics::iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects);
				void CPF_STDCALL ClearDepthStencilView(Graphics::iImageView* view, Graphics::DepthStencilClearFlag flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects);

			private:
				GOM::Result _AddCommandList();
				ID3D12GraphicsCommandList* _Current() { CPF_ASSERT(mCurrent >= 0); return mCommandLists[mCurrent][0]; }
				static void _MakeBarrier(D3D12_RESOURCE_BARRIER* barrier, Image* image, Graphics::ResourceState begin, Graphics::ResourceState end);
				GOM::Result _StartSubPass();
				GOM::Result _EndSubPass();

				friend class Device;
				using CommandListPtr = ID3D12GraphicsCommandList*;
				using CommandListVector = Vector<CommandListPtr>;
				using CommandListStack = Vector<CommandListVector>;

				Device* mpDevice;
				ID3D12CommandAllocator* mpAllocator;
				CommandListStack mCommandLists;
				int32_t mCurrent;
				int32_t mSubPass;
				Graphics::CommandBufferType mType;

				UnorderedSet<ID3D12DescriptorHeap*> mHeaps;
				Graphics::RenderPassBeginDesc mRenderPass;
				Vector<Graphics::ResourceState> mAttachmentStates;

				int32_t mColorViewCount;
				Graphics::iImageView* mpColorViews[32];
				Graphics::iImageView* mpDepthBufferView;
			};
		}
	}
}
