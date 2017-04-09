//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iSampler.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"
#include "DescriptorManager.hpp"


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class Sampler : public tRefCounted<Graphics::iSampler>
			{
			public:
				Sampler(Device*, const Graphics::SamplerDesc* desc);
				virtual ~Sampler();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
