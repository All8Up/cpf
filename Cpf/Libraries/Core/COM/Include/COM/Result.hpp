//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/HashID.hpp"

namespace Cpf
{
	namespace COM
	{
		/** @brief A result code. */
		using Result = struct Result
		{
			uint32_t Error : 1;
			uint32_t SubSystem : 16;
			uint32_t Value : 15;
		};
		static_assert(sizeof(Result) == 4, "Invalid result code size.");

		/**
		 * @brief Result code comparison.
		 * @param lhs The left hand side.
		 * @param rhs The right hand side.
		 * @return True if equivalent.
		 */
		inline bool operator == (const Result lhs, const Result rhs)
		{
			return lhs.Error == rhs.Error && lhs.SubSystem == rhs.SubSystem && lhs.Value == rhs.Value;
		}

		/**
		 * @brief Creates a result code.
		 * @param e  If the result is an error or not.
		 * @param ss The system identifier.
		 * @param v  The error code identifier.
		 * @return The result code.
		 */
		inline constexpr Result CreateResult(uint8_t e, uint16_t ss, uint16_t v) { return Result{ e, ss, uint16_t(v & 0x7FFF) }; }

		/**
		 * @brief Test a result code for sucess.
		 * @param result The result code to test.
		 * @return True if the result code is a non-error code.
		 */
		inline constexpr bool Succeeded(Result result) { return result.Error == 0; }

		/**
		 * @brief Test if a result code indicates an error.
		 * @param result The result code to test.
		 * @return True if the result code is a failure code.
		 */
		inline constexpr bool Failed(Result result) { return result.Error != 0; }

		static constexpr Result kOK = CreateResult(0, "Core"_crc16, "OK"_crc16);
		static constexpr Result kError = CreateResult(1, "Core"_crc16, "Error"_crc16);
		static constexpr Result kUnknownInterface = CreateResult(1, "Core"_crc16, "UnknownInterface"_crc16);
		static constexpr Result kInvalidParameter = CreateResult(1, "Core"_crc16, "InvalidParameter"_crc16);
		static constexpr Result kOutOfMemory = CreateResult(1, "Core"_crc16, "OutOfMemory"_crc16);
		static constexpr Result kUnknownClass = CreateResult(1, "Core"_crc16, "UnknownClass"_crc16);
		static constexpr Result kNotImplemented = CreateResult(1, "Core"_crc16, "NotImplemented"_crc16);
		static constexpr Result kInvalid = CreateResult(1, "Core"_crc16, "Invalid"_crc16);
		static constexpr Result kNotEnoughSpace = CreateResult(1, "Core"_crc16, "NotEnoughSpace"_crc16);
		static constexpr Result kInUse = CreateResult(0, "Core"_crc16, "InUse"_crc16);
		static constexpr Result kNotInitialized = CreateResult(1, "Core"_crc16, "NotInitialized"_crc16);
		static constexpr Result kInitializationFailure = CreateResult(1, "Core"_crc16, "InitializationFailure"_crc16);
		static constexpr Result kOutOfRange = CreateResult(1, "Core"_crc16, "OutOfRange"_crc16);
		static constexpr Result kDuplicateCID = CreateResult(1, "Core"_crc16, "DuplicateCID"_crc16);
		static constexpr Result kRegistryError = CreateResult(1, "Core"_crc16, "RegistryError"_crc16);
		static constexpr Result kNotRunning = CreateResult(1, "Core"_crc16, "NotRunning"_crc16);
	}
}
