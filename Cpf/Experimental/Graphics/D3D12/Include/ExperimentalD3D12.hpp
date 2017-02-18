//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"
#include "Graphics.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Math/Vector3.hpp"
#include "Resources/Locator.hpp"
#include "GO/Service.hpp"
#include "Threading/Reactor.hpp"
#include "Graphics/DebugUI.hpp"


namespace Cpf
{
	class ExperimentalD3D12 : public Adapter::WindowedApp
	{
	public:
		ExperimentalD3D12()
			: mScheduler(this)
			, mFenceTarget(1)
		{}

		int Start(const CommandLine&) override;

		static const int32_t kInstancesPerDimension = 50;
		static const int32_t kInstanceCount = kInstancesPerDimension*kInstancesPerDimension*kInstancesPerDimension;

		struct Instance
		{
			Math::Vector3f mTranslation;
			Math::Vector3f mScale;
			// TODO: Resurrect the Matrix33f non-simd class for this.
			Math::Vector3f mOrientation0;
			Math::Vector3f mOrientation1;
			Math::Vector3f mOrientation2;
		};

		Graphics::iVertexBuffer* GetCurrentInstanceBuffer() const { return mpInstanceBuffer[mCurrentBackbuffer]; }

	private:
		bool _CreateWindow();
		void _CreateWorkerData(Concurrency::ThreadContext& tc);
		void _DestroyWorkerData(Concurrency::ThreadContext& tc);

		bool _SelectAdapter(Graphics::iInstance* instance, Graphics::iAdapter**);
		bool _EnumerateOutputs(Graphics::iAdapter*);
		bool _CreateSwapChain(Graphics::iInstance* instance);

		bool _CreateResources();
		void _DestroyResources();

		void _BeginFrame(Concurrency::ThreadContext&);
		void _ClearBuffers(Concurrency::ThreadContext&);
		void _Draw(Concurrency::ThreadContext& tc);
		void _DebugUI(Concurrency::ThreadContext& tc);
		void _PreparePresent(Concurrency::ThreadContext&);
		void _EndFrame(Concurrency::ThreadContext&);
		void _Resize(int32_t x, int32_t y);

		IntrusivePtr<Resources::Locator> mpLocator;

		static const int32_t mBackBufferCount = 3;

		IntrusivePtr<iWindow> mpWindow;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		Vector<IntrusivePtr<Graphics::iImage>> mpDepthBufferImages;
		Vector<IntrusivePtr<Graphics::iImageView>> mpDepthBufferImageViews;
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
		Concurrency::Scheduler::Queue mQueue;

		int32_t mCurrentScheduledBuffer = 0;
		Graphics::iCommandBuffer* mpScheduledBuffers[Concurrency::Scheduler::kMaxThreads * 4];

		int32_t mCurrentBackbuffer = 0;
		uint64_t mFenceTarget = 1;
		uint64_t mFrameIndex = 0;
		uint64_t mSubmissionIndex = 0;

		Platform::Time::Value mStartTime;
		Platform::Time::Value mCurrentTime;
		Platform::Time::Value mDeltaTime;

		float mFOV;
		float mViewportSize;
		float mAspectRatio;

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

		Platform::Threading::Reactor mReactor;
		// If the multi-core side of things needs anything run on the main thread,
		// feed it in this queue.
		Platform::Threading::Reactor::WorkQueue mReactorQueue;
		GO::Service mGOService;

		Graphics::DebugUI mDebugUI;

		bool mThreadCountChanged;
		int32_t mThreadCount;
	};
}
