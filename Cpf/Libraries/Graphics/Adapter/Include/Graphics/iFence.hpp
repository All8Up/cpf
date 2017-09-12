//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iFence : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iFence"_crc64);

			virtual uint64_t GetValue() const = 0;
			virtual void WaitFor(uint64_t value) = 0;

			// TODO: Replacement interface to cover Vulkan and D3D12.
			/*
			virtual GOM::Result CPF_STDCALL GetStatus() = 0;
			virtual void CPF_STDCALL Reset() = 0;

			// Addition(s) to (probably) iDevice:
			virtual GOM::Result CPF_STDCALL Wait(int32_t count, iFence* fences, bool waitForAll) = 0;
			virtual GOM::Result CPF_STDCALL Reset(int32_t count, iFence* fences) = 0;
			*/
		};
	}
}
