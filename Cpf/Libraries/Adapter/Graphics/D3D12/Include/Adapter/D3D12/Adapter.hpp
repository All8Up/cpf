//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iAdapter.hpp"
#include "IntrusivePtr.hpp"
#include <dxgi1_4.h>

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Adapter : public tRefCounted<Graphics::iAdapter>
			{
			public:
				// TODO: Enumerate attached outputs (monitors).
				// TODO: Enumerate video resolutions for outputs.

				Adapter(IDXGIAdapter2* adapter);
				~Adapter() override;

				const char* GetDescription() const override;
				size_t GetVideoMemory() const override;
				size_t GetSystemMemory() const override;
				size_t GetSharedMemory() const override;

				bool IsSoftware() const override;
				bool IsRemote() const override;

				bool EnumerateOutputs(int32_t& count, Graphics::iOutput**) const;

				IDXGIAdapter2* GetD3DAdapter() const { return mpAdapter; }

			private:
				IntrusivePtr<IDXGIAdapter2> mpAdapter;
				DXGI_ADAPTER_DESC2 mDesc;

				char mDescription[128];
			};
		}
	}
}
