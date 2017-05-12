//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class Stream;
		}
	}

	namespace Resources
	{
		struct ID;
		struct VolumeDesc {};

		//////////////////////////////////////////////////////////////////////////
		struct iVolume : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iVolume"_crc64);

			virtual bool CPF_STDCALL Mount(const char* const) = 0;
			virtual void CPF_STDCALL Unmount() = 0;

			virtual Platform::IO::Stream* CPF_STDCALL Open(ID) = 0;
		};
	}
}
