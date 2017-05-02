//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iFence : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iFence"_crc64);

			virtual uint64_t GetValue() const = 0;
			virtual void WaitFor(uint64_t value) = 0;

			// TODO: Replacement interface to cover Vulkan and D3D12.
			/*
			virtual COM::Result CPF_STDCALL GetStatus() = 0;
			virtual void CPF_STDCALL Reset() = 0;

			// Addition(s) to (probably) iDevice:
			virtual COM::Result CPF_STDCALL Wait(int32_t count, iFence* fences, bool waitForAll) = 0;
			virtual COM::Result CPF_STDCALL Reset(int32_t count, iFence* fences) = 0;
			*/
		};
	}
}
