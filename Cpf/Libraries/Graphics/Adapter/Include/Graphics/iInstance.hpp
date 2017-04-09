//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		struct iDevice;
		struct iAdapter;
		struct iSwapChain;

		struct SwapChainDesc;

		struct iInstance : COM::iUnknown
		{
		public:
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iInstance"_crc64);

			virtual bool CPF_STDCALL EnumerateAdapters(int& count, iAdapter** adapters) = 0;
			virtual COM::Result CPF_STDCALL CreateDevice(iAdapter*, iDevice**) = 0;
		};
	}
}
