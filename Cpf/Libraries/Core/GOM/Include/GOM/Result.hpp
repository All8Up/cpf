//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	namespace GOM
	{
		/** @brief A result code. */
		using Result = uint32_t;
		static_assert(sizeof(Result) == 4, "Invalid result code size.");

		/**
		 * @brief Creates a result code.
		 * @param e  If the result is an error or not.
		 * @param ss The system identifier.
		 * @param v  The error code identifier.
		 * @return The result code.
		 */
		constexpr Result CreateResult(uint8_t e, uint16_t ss, uint16_t v) { return (e == 0 ? 0 : 1) << 31 | (ss & 0xFFFF) << 15 | (v&0x7FFF); }

		/**
		 * @brief Test a result code for sucess.
		 * @param result The result code to test.
		 * @return True if the result code is a non-error code.
		 */
		constexpr bool Succeeded(Result result) { return (result & 0x80000000) == 0; }

		/**
		 * @brief Test if a result code indicates an error.
		 * @param result The result code to test.
		 * @return True if the result code is a failure code.
		 */
		constexpr bool Failed(Result result) { return (result & 0x80000000) != 0; }

		constexpr uint16_t GetError(Result result) { return uint16_t((result & 0x80000000) >> 31); }
		constexpr uint16_t GetSubSystem(Result result) { return uint16_t((result & 0x7FFF8000) >> 15); }
		constexpr uint16_t GetCode(Result result) { return uint16_t(result & 0x00007fff); }

		// Standard result codes.
		static constexpr Result kOK = CreateResult(0, "Core"_crc16, "OK"_crc15);
		static constexpr Result kError = CreateResult(1, "Core"_crc16, "Error"_crc15);
		static constexpr Result kUnknownInterface = CreateResult(1, "Core"_crc16, "UnknownInterface"_crc15);
		static constexpr Result kInvalidParameter = CreateResult(1, "Core"_crc16, "InvalidParameter"_crc15);
		static constexpr Result kOutOfMemory = CreateResult(1, "Core"_crc16, "OutOfMemory"_crc15);
		static constexpr Result kUnknownClass = CreateResult(1, "Core"_crc16, "UnknownClass"_crc15);
		static constexpr Result kNotImplemented = CreateResult(1, "Core"_crc16, "NotImplemented"_crc15);
		static constexpr Result kInvalid = CreateResult(1, "Core"_crc16, "Invalid"_crc15);
		static constexpr Result kNotEnoughSpace = CreateResult(1, "Core"_crc16, "NotEnoughSpace"_crc15);
		static constexpr Result kInUse = CreateResult(0, "Core"_crc16, "InUse"_crc15);
		static constexpr Result kNotInitialized = CreateResult(1, "Core"_crc16, "NotInitialized"_crc15);
		static constexpr Result kInitializationFailure = CreateResult(1, "Core"_crc16, "InitializationFailure"_crc15);
		static constexpr Result kOutOfRange = CreateResult(1, "Core"_crc16, "OutOfRange"_crc15);
		static constexpr Result kDuplicateCID = CreateResult(1, "Core"_crc16, "DuplicateCID"_crc15);
		static constexpr Result kRegistryError = CreateResult(1, "Core"_crc16, "RegistryError"_crc15);
		static constexpr Result kNotRunning = CreateResult(1, "Core"_crc16, "NotRunning"_crc15);
	}
}


// Utility macro for creating result codes.
#define GOM_RESULT(e, ss, v) Cpf::GOM::CreateResult(e, ss##_crc16, v##_crc15)
