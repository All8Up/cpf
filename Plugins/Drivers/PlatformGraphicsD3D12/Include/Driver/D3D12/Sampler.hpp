//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iSampler.hpp"
#include "DescriptorManager.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct SamplerDesc;
	}
	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class Sampler final : public GOM::tUnknown<Graphics::iSampler>
			{
			public:
				Sampler(Device*, const Graphics::SamplerDesc* desc);
				virtual ~Sampler();

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
