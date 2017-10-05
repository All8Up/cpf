//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iSwapChain.hpp"
#include "Vector.hpp"
#include "RefCounted.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		namespace Driver
		{
			class iDevice;
		}
	}

	namespace Adapters
	{
		namespace Metal
		{
			class Instance;

			class SwapChain : public tRefCounted<Graphics::Driver::iSwapChain>
			{
			public:
				SwapChain(Instance*, Graphics::Driver::iDevice*, iWindow*, const Graphics::Driver::SwapChainDesc& desc);
				~SwapChain() override;

			private:
			};
		}
	}
}
