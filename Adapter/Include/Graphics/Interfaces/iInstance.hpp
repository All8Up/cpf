//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		class iDevice;
		class iAdapter;
		class iSwapChain;
		struct SwapChainDesc;

		class iInstance : public iRefCounted
		{
		public:
			virtual ~iInstance() = 0;

			virtual bool EnumerateAdapters(int& count, iAdapter** adapters) = 0;
			virtual bool CreateDevice(iAdapter*, iDevice**) = 0;
		};
	}
}
