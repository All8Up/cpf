//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplicationMain.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/iWindow.hpp"
#include "Graphics.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Resources/Locator.hpp"
#include "EntityService/Interfaces/iManager.hpp"
#include "Threading/Reactor.hpp"
#include "Graphics/iDebugUI.hpp"
#include "MultiCore/iPipeline.hpp"
#include "MovementSystem.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/iImageView.hpp"
#include "Graphics/iFrameBuffer.hpp"
#include "Graphics/iRenderPass.hpp"

//
namespace Cpf
{
	class ExperimentalD3D12 : public tRefCounted<iApplicationMain>
	{
	public:
		ExperimentalD3D12()
			: mScheduler(this)
			, mFenceTarget(1)
			, mSelectedInstruction(0)
			, mpInstructionList(nullptr)
			, mInstructionCount(0)
			, mpEntityManager(nullptr)
			, mpRegistry(nullptr)
			, mpApplication(nullptr)
		{}

		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }

		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, COM::ClassID* appCid) override;
		COM::Result CPF_STDCALL Main(iApplication* application) override;
		void CPF_STDCALL Shutdown() override;

		Plugin::iRegistry* GetRegistry() { return mpRegistry; }

		static const int32_t kInstancesPerDimension = 50;
		static const int32_t kInstanceCount = kInstancesPerDimension*kInstancesPerDimension*kInstancesPerDimension;

		Graphics::iVertexBuffer* GetCurrentInstanceBuffer() const { return mpInstanceBuffer[mCurrentBackbuffer]; }

		void ReconfigurePipeline();

		// Moving to a render system.
		void _BeginFrame(Concurrency::ThreadContext&);
		void _ClearBuffers(Concurrency::ThreadContext&);
		void _Draw(Concurrency::ThreadContext& tc);
		void _DebugUI(Concurrency::ThreadContext& tc);
		void _PreparePresent(Concurrency::ThreadContext&);
		void _EndFrame(Concurrency::ThreadContext&);

	private:
		bool _CreateWindow();
		void _CreateWorkerData(Concurrency::ThreadContext& tc);
		void _DestroyWorkerData(Concurrency::ThreadContext& tc);

		bool _SelectAdapter(Graphics::iInstance* instance, Graphics::iAdapter**);
		bool _EnumerateOutputs(Graphics::iAdapter*);
		bool _CreateSwapChain(Graphics::iInstance* instance);

		bool _CreateResources();
		void _DestroyResources();

		void _Resize(int32_t x, int32_t y);

		void _UpdatePipelineDisplay();

		IntrusivePtr<Resources::Locator> mpLocator;

		static const int32_t mBackBufferCount = 3;

		IntrusivePtr<iWindow> mpWindow;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		IntrusivePtr<Graphics::iRenderPass> mpRenderPass;
		Vector<IntrusivePtr<Graphics::iFrameBuffer>> mpFrameBuffers;
		IntrusivePtr<Graphics::iImage> mpDepthBuffer;
		IntrusivePtr<Graphics::iImageView> mpDepthBufferView;
		IntrusivePtr<Graphics::iResourceBinding> mpResourceBinding;
		IntrusivePtr<Graphics::iConstantBuffer> mpViewProj;
		IntrusivePtr<Graphics::iShader> mpVertexShader;
		IntrusivePtr<Graphics::iShader> mpPixelShader;

		IntrusivePtr<Graphics::iVertexBuffer> mpVertexBuffer;
		IntrusivePtr<Graphics::iVertexBuffer> mpInstanceBuffer[mBackBufferCount];
		IntrusivePtr<Graphics::iIndexBuffer> mpIndexBuffer;

		IntrusivePtr<Graphics::iCommandPool> mpPreCommandPool[mBackBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPreCommandBuffer[mBackBufferCount];
		IntrusivePtr<Graphics::iCommandPool> mpPostCommandPool[mBackBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPostCommandBuffer[mBackBufferCount];
		IntrusivePtr<Graphics::iPipeline> mpPipeline;
		IntrusivePtr<Graphics::iFence> mpFence;
		Concurrency::Scheduler mScheduler;

		int32_t mCurrentScheduledBuffer = 0;
		Graphics::iCommandBuffer* mpScheduledBuffers[Concurrency::Scheduler::kMaxThreads * 4];

		int32_t mCurrentBackbuffer = 0;
		uint64_t mFenceTarget = 1;
		uint64_t mFrameIndex = 0;
		uint64_t mSubmissionIndex = 0;

		Time::Value mStartTime;
		Time::Value mCurrentTime;
		Time::Value mDeltaTime;

		float mFOV;
		float mViewportSize;
		float mAspectRatio;

		//
		IntrusivePtr<MultiCore::iPipeline> mpMultiCore;

		// Per thread data.
		struct ThreadData
		{
			IntrusivePtr<Graphics::iCommandPool> mpCommandPool[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandBuffer> mpCommandBuffer[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandPool> mpDebugUIPool[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandBuffer> mpDebugUIBuffer[mBackBufferCount];
		};
		ThreadData mWorkerData[Concurrency::Scheduler::kMaxThreads];

		/* Not used right now.
		struct ModelTransform
		{
			Math::Matrix33fv mOrientation;
			Math::Vector3fv mScale;
			Math::Vector3fv mTranslation;
		};
		IntrusivePtr<Graphics::iConstantBuffer> mpModelTransform;
		*/

		Threading::Reactor mReactor;
		// If the multi-core side of things needs anything run on the main thread,
		// feed it in this queue.
		Threading::Reactor::WorkQueue mReactorQueue;
		IntrusivePtr<EntityService::iManager> mpEntityManager;

		IntrusivePtr<Graphics::iDebugUI> mpDebugUI;

		int mSelectedInstruction;
		char** mpInstructionList;
		int mInstructionCount;

		bool mThreadCountChanged;
		int32_t mThreadCount;

		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<MoverSystem> mpMoverSystem;

		Plugin::iRegistry* mpRegistry;
		iWindowedApplication* mpApplication;
	};
}
