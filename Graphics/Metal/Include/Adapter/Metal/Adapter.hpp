//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iAdapter.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace Adapters
	{
		namespace Metal
		{
			class Adapter : public tRefCounted<Graphics::Driver::iAdapter>
			{
			public:
				// TODO: Enumerate attached outputs (monitors).
				// TODO: Enumerate video resolutions for outputs.

				~Adapter() override;
				bool IsSoftware() override;

			private:
			};
		}
	}
}
