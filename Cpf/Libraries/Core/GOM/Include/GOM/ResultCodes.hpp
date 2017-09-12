//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/Result.hpp"

namespace CPF
{
	namespace GOM
	{
		static constexpr Result kOK = CreateResult(0, "Core"_crc15, "OK"_crc16);
		static constexpr Result kError = CreateResult(1, "Core"_crc15, "Error"_crc16);
		static constexpr Result kUnknownInterface = CreateResult(1, "Core"_crc15, "UnknownInterface"_crc16);
		static constexpr Result kInvalidParameter = CreateResult(1, "Core"_crc15, "InvalidParameter"_crc16);
		static constexpr Result kOutOfMemory = CreateResult(1, "Core"_crc15, "OutOfMemory"_crc16);
		static constexpr Result kUnknownClass = CreateResult(1, "Core"_crc15, "UnknownClass"_crc16);
		static constexpr Result kNotImplemented = CreateResult(1, "Core"_crc15, "NotImplemented"_crc16);
		static constexpr Result kInvalid = CreateResult(1, "Core"_crc15, "Invalid"_crc16);
		static constexpr Result kNotEnoughSpace = CreateResult(1, "Core"_crc15, "NotEnoughSpace"_crc16);
		static constexpr Result kInUse = CreateResult(0, "Core"_crc15, "InUse"_crc16);
		static constexpr Result kNotInitialized = CreateResult(1, "Core"_crc15, "NotInitialized"_crc16);
		static constexpr Result kInitializationFailure = CreateResult(1, "Core"_crc15, "InitializationFailure"_crc16);
		static constexpr Result kOutOfRange = CreateResult(1, "Core"_crc15, "OutOfRange"_crc16);
		static constexpr Result kDuplicateCID = CreateResult(1, "Core"_crc15, "DuplicateCID"_crc16);
		static constexpr Result kRegistryError = CreateResult(1, "Core"_crc15, "RegistryError"_crc16);
		static constexpr Result kNotRunning = CreateResult(1, "Core"_crc15, "NotRunning"_crc16);
	}
}
