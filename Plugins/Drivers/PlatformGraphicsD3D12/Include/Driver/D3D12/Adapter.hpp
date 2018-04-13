//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iAdapter.hpp"
#include "CPF/IntrusivePtr.hpp"
#include <dxgi1_4.h>
#include "CPF/Plugin/tClassFactory.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kAdapterCID = GOM::ClassID("Adapter::D3D12::Adapter"_crc64);

			class Adapter final : public GOM::tUnknown<Graphics::iAdapter>
			{
			public:
				//
				Adapter(Plugin::iRegistry*, GOM::iUnknown*);
				virtual ~Adapter();

				// Internal
				GOM::Result Initialize(IDXGIAdapter2* adapter);

				// Overrides from iAdapter.
				const char* CPF_STDCALL GetDescription() const override;
				size_t CPF_STDCALL GetVideoMemory() const override;
				size_t CPF_STDCALL GetSystemMemory() const override;
				size_t CPF_STDCALL GetSharedMemory() const override;

				bool CPF_STDCALL IsSoftware() const override;
				bool CPF_STDCALL IsRemote() const override;

				GOM::Result CPF_STDCALL EnumerateOutputs(int32_t* count, Graphics::iOutput**) const override;

				//
				IDXGIAdapter2* GetD3DAdapter() const { return mpAdapter; }

			private:

				IntrusivePtr<IDXGIAdapter2> mpAdapter;
				DXGI_ADAPTER_DESC2 mDesc;

				char mDescription[128];
			};
		}
	}
}
