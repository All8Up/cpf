//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Rtti.hpp"
#include "IntrusivePtr.hpp"
#include "Adapters/Metal.hpp"
#include "Graphics/Driver.hpp"


namespace Cpf
{
	namespace Graphics
	{
		namespace Driver
		{
			class iAdapter;
			class iCommandPool;
		}
	}
	namespace Adapters
	{
		namespace Metal
		{
			CPF_EXPORT_ADAPTERS_METAL class Device : public tRefCounted<Graphics::Driver::iDevice>
			{
			public:
				Device(Graphics::Driver::iAdapter* dev);
				virtual ~Device();

				bool CreateCommandPool(Graphics::Driver::iCommandPool**) override;
				bool CreateCommandBuffer(Graphics::Driver::iCommandPool*, Graphics::Driver::iCommandBuffer**) override;

			private:
			};
		}
	}
}


CPF_DECLARE_RTTI(Cpf::Adapters::Metal::Device, Cpf::Graphics::Driver::iDevice);
