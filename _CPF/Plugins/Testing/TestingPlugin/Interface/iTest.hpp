//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Testing
{
	// Implementation class id for instantiation.
	static constexpr CPF::GOM::ClassID kTestCID = CPF::GOM::ClassID("Testing::iTest"_crc64);

	struct iTest : CPF::GOM::iUnknown
	{
		// Interface id.
		static constexpr CPF::GOM::InterfaceID kIID = CPF::GOM::InterfaceID("Testing::iTest"_crc64);

		// Test function, simply returns the 64 bit value cast to a 32 bit value.
		virtual int32_t CPF_STDCALL Tester(int64_t) = 0;
	};
}
