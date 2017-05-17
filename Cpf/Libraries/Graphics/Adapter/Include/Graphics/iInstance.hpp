//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;
		struct iAdapter;

		struct iInstance : GOM::iUnknown
		{
		public:
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iInstance"_crc64);

			virtual GOM::Result CPF_STDCALL EnumerateAdapters(int& count, iAdapter** adapters) = 0;
			virtual GOM::Result CPF_STDCALL CreateDevice(iAdapter*, iDevice**) = 0;
		};
	}
}
