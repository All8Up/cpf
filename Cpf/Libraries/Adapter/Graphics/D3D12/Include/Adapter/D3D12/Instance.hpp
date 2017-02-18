//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iInstance.hpp"
#include "IntrusivePtr.hpp"
#include "D3D12Utils.hpp"

#define CPF_D3D12_DEBUG_LAYER 1
#if defined(CPF_DEBUG) || CPF_D3D12_DEBUG_LAYER
#	define CPF_USE_D3D12_DEBUG_LAYER
#endif

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		class iDevice;
		class iAdapter;
		class iSwapChain;
		struct SwapChainDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			//////////////////////////////////////////////////////////////////////////
			class Instance : public tRefCounted<Graphics::iInstance>
			{
			public:
				static void* Create();

				bool EnumerateAdapters(int& count, Graphics::iAdapter** adapters) override;
				bool CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice**) override;

				IDXGIFactory2* GetFactory() const { return mpDXGIFactory2; }

			private:
				Instance();
				~Instance() override;

				IntrusivePtr<IDXGIFactory2> mpDXGIFactory2;

#ifdef CPF_USE_D3D12_DEBUG_LAYER
				IntrusivePtr<ID3D12Debug> mpDebugController;
#endif
			};
		}
	}
}
