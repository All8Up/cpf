//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace IO
	{
		class Stream;
	}

	namespace Resources
	{
		struct ID;
		struct VolumeDesc {};

		//////////////////////////////////////////////////////////////////////////
		struct iVolume : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iVolume"_crc64);

			virtual bool CPF_STDCALL Mount(const char* const) = 0;
			virtual void CPF_STDCALL Unmount() = 0;

			virtual IO::Stream* CPF_STDCALL Open(ID) = 0;
		};
	}
}
