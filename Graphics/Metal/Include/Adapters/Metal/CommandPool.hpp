//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iCommandPool.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Adapters
	{
		namespace Metal
		{
			class Device;

			class CommandPool : public tRefCounted<Graphics::Driver::iCommandPool>
			{
			public:
				CommandPool(Device* device);
				~CommandPool() override;

				void Reset() override;

			private:
			};
		}
	}
}
