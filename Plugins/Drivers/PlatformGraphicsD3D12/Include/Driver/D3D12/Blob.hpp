//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iBlob.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Blob final : public GOM::tUnknown<Graphics::iBlob>
			{
			public:
				Blob(size_t size, const void* data);

				GOM::Result Initialize(const void* data, int64_t size) override;
				void* CPF_STDCALL GetData() override;
				int64_t CPF_STDCALL GetSize() override;

			private:
				~Blob();

				STD::Vector<uint8_t> mData;
			};
		}
	}
}
