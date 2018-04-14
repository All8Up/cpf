//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iInstance.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "D3D12Utils.hpp"

namespace CPF
{
	namespace Platform
	{
		struct iWindow;
	}

	namespace Graphics
	{
		struct iDevice;
		struct iAdapter;
		struct iSwapChain;

		struct SwapChainDesc;
	}
	namespace Driver
	{
		namespace D3D12
		{
			//////////////////////////////////////////////////////////////////////////
			static constexpr GOM::ClassID kD3D12InstanceCID = GOM::ClassID("Adapter::D3D12::iInstance"_crc64);

			//////////////////////////////////////////////////////////////////////////
			struct Instance final : GOM::tUnknown<Graphics::iInstance>
			{
				Instance(Plugin::iRegistry*, iUnknown*);
				virtual ~Instance();

				GOM::Result CPF_STDCALL Initialize(const Graphics::InstanceDesc* desc) override;

				GOM::Result CPF_STDCALL EnumerateAdapters(int* count, Graphics::iAdapter** adapters) override;
				GOM::Result CPF_STDCALL CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice**) override;

				//
				IDXGIFactory2* GetFactory() const { return mpDXGIFactory2; }

			private:
				IntrusivePtr<Plugin::iRegistry> mpRegistry;
				IntrusivePtr<IDXGIFactory2> mpDXGIFactory2;
				IntrusivePtr<ID3D12Debug> mpDebugController;
			};
		}
	}
}
