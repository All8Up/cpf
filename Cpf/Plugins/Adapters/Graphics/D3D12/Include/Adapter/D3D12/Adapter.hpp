//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iAdapter.hpp"
#include "IntrusivePtr.hpp"
#include <dxgi1_4.h>
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kAdapterCID = GOM::ClassID("Adapter::D3D12::Adapter"_crc64);

			class Adapter : public tRefCounted<Graphics::iAdapter>
			{
			public:
				// Internal
				GOM::Result Initialize(IDXGIAdapter2* adapter);

				// Overrides from iBase.
				GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

				const char* CPF_STDCALL GetDescription() const override;
				size_t CPF_STDCALL GetVideoMemory() const override;
				size_t CPF_STDCALL GetSystemMemory() const override;
				size_t CPF_STDCALL GetSharedMemory() const override;

				bool CPF_STDCALL IsSoftware() const override;
				bool CPF_STDCALL IsRemote() const override;

				GOM::Result CPF_STDCALL EnumerateOutputs(int32_t& count, Graphics::iOutput**) const override;

				IDXGIAdapter2* GetD3DAdapter() const { return mpAdapter; }

			private:
				CPF_CLASSINSTANCE_ACCESS(Adapter);
				Adapter(GOM::iBase*);
				virtual ~Adapter();

				IntrusivePtr<IDXGIAdapter2> mpAdapter;
				DXGI_ADAPTER_DESC2 mDesc;

				char mDescription[128];
			};
		}
	}
}
