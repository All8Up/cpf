//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iOutput.hpp"
#include "CPF/IntrusivePtr.hpp"
#include <dxgi1_4.h>
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Output final : public GOM::tUnknown<Graphics::iOutput>
			{
			public:
				Output(IDXGIOutput4* output);
				virtual ~Output();

				bool GetDesc(Graphics::OutputDesc*) const override;
				bool EnumerateModes(Graphics::Format format, Graphics::EnumMode enumMode, int32_t* count, Graphics::ModeDesc*) override;
				bool FindClosestMatch(const Graphics::ModeDesc* matchMode, Graphics::ModeDesc* closest, Graphics::iDevice* compatibleCheck) override;
				bool WaitForVBlank() override;

			private:
				IntrusivePtr<IDXGIOutput4> mpOutput;
			};
		}
	}
}
