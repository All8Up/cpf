//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iInstance.hpp"
#include "IntrusivePtr.hpp"
#include "D3D12Utils.hpp"
// Used for IDXGIFactory2.  Not all systems have dxgi1_4.h yet so this seems more compatible.
#include <d3d11_1.h>

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

#ifdef CPF_DEBUG
				IntrusivePtr<ID3D12Debug> mpDebugController;
#endif
			};
		}
	}
}
