//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iBlob.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Blob : public tRefCounted<Cpf::Graphics::iBlob>
			{
			public:
				Blob(size_t size, const void* data);

				GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

				GOM::Result Initialize(const void* data, int64_t size) override;
				void* CPF_STDCALL GetData() override;
				int64_t CPF_STDCALL GetSize() override;

			private:
				~Blob();

				Cpf::Vector<uint8_t> mData;
			};
		}
	}
}
