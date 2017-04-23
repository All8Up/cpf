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

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				COM::Result Initialize(const void* data, int64_t size) override;
				void* CPF_STDCALL GetData() override;
				int64_t CPF_STDCALL GetSize() override;

			private:
				~Blob();

				Cpf::Vector<uint8_t> mData;
			};
		}
	}
}
