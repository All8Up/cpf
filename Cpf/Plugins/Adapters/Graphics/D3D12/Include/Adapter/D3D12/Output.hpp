//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iOutput.hpp"
#include "IntrusivePtr.hpp"
#include <dxgi1_4.h>

namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Output : public tRefCounted<Graphics::iOutput>
			{
			public:
				Output(IDXGIOutput4* output);
				virtual ~Output();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				bool GetDesc(Graphics::OutputDesc*) const override;
				bool EnumerateModes(Graphics::Format format, Graphics::EnumMode enumMode, int32_t& count, Graphics::ModeDesc*) override;
				bool FindClosestMatch(const Graphics::ModeDesc* matchMode, Graphics::ModeDesc* closest, Graphics::iDevice* compatibleCheck) override;
				bool WaitForVBlank() override;

			private:
				IntrusivePtr<IDXGIOutput4> mpOutput;
			};
		}
	}
}
