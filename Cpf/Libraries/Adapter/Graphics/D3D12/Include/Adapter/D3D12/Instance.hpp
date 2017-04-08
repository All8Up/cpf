//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iInstance.hpp"
#include "Plugin/iRegistry.hpp"
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
			struct Instance : tRefCounted<Graphics::iInstance>
			{
				Instance(Plugin::iRegistry*);
				virtual ~Instance();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				bool CPF_STDCALL EnumerateAdapters(int& count, Graphics::iAdapter** adapters) override;
				bool CPF_STDCALL CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice**) override;

				//
				IDXGIFactory2* GetFactory() const { return mpDXGIFactory2; }

			private:
				IntrusivePtr<IDXGIFactory2> mpDXGIFactory2;
				Plugin::iRegistry* mpRegistry;

#ifdef CPF_USE_D3D12_DEBUG_LAYER
				IntrusivePtr<ID3D12Debug> mpDebugController;
#endif
			};
		}
	}
}
