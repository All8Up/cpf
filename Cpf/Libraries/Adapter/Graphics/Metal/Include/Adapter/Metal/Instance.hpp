//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iInstance.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		namespace Driver
		{
			class iDevice;
			class iAdapter;
			class iSwapChain;
			struct SwapChainDesc;
		}
	}
	namespace Adapters
	{
		namespace Metal
		{
			//////////////////////////////////////////////////////////////////////////
			class Instance : public tRefCounted<Graphics::Driver::iInstance>
			{
			public:
				static void* Create();

				bool EnumerateAdapters(int& count, Graphics::Driver::iAdapter** adapters) override;
				bool CreateDevice(Graphics::Driver::iAdapter* adapter, Graphics::Driver::iDevice**) override;
				bool CreateSwapChain(Graphics::Driver::iDevice*, iWindow*, const Graphics::Driver::SwapChainDesc&, Graphics::Driver::iSwapChain**) override;

			private:
				Instance();
				~Instance() override;
			};
		}
	}
}

CPF_DECLARE_RTTI(Cpf::Adapters::Metal::Instance);
