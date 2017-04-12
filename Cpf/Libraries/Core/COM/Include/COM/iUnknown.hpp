//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	namespace COM
	{
		struct class_tag;
		using ClassID = Hash::HashID<uint64_t, class_tag>;
		struct interface_tag;
		using InterfaceID = Hash::HashID<uint64_t, interface_tag>;

		using Result = struct Result {
			uint32_t Error : 1; uint32_t SubSystem : 16; uint32_t Value : 15;
		};
		static_assert(sizeof(Result)==4, "Invalid result code size.");

		inline bool operator == (const Result lhs, const Result rhs)
		{
			return lhs.Error == rhs.Error && lhs.SubSystem == rhs.SubSystem && lhs.Value == rhs.Value;
		}

		inline constexpr Result CreateResult(uint8_t e, uint16_t ss, uint16_t v) { return Result{e, ss, v}; }
		inline constexpr bool Succeeded(Result result) { return result.Error == 0; }
		inline constexpr bool Failed(Result result) { return result.Error != 0; }

		static constexpr Result kOK = CreateResult(0, "Core"_crc16, 0);
		static constexpr Result kError = CreateResult(1, "Core"_crc16, 0);
		static constexpr Result kUnknownInterface = CreateResult(1, "Core"_crc16, 1);
		static constexpr Result kInvalidParameter = CreateResult(1, "Core"_crc16, 2);
		static constexpr Result kOutOfMemory = CreateResult(1, "Core"_crc16, 3);
		static constexpr Result kUnknownClass = CreateResult(1, "Core"_crc16, 4);
		static constexpr Result kNotImplemented = CreateResult(1, "Core"_crc16, 5);
		static constexpr Result kInvalid = CreateResult(1, "Core"_crc16, 6);
		static constexpr Result kNotEnoughSpace = CreateResult(1, "Core"_crc16, 7);
		static constexpr Result kInUse = CreateResult(0, "Core"_crc16, 8);
		static constexpr Result kNotInitialized = CreateResult(1, "Core"_crc16, 9);
		static constexpr Result kInitializationFailure = CreateResult(1, "Core"_crc16, 10);
		static constexpr Result kOutOfRange = CreateResult(1, "Core"_crc16, 11);

		//////////////////////////////////////////////////////////////////////////
		struct iUnknown : iRefCounted
		{
			static constexpr InterfaceID kIID = InterfaceID("iUnknown Interface"_crc64);

			virtual Result CPF_STDCALL QueryInterface(InterfaceID id, void** outIface) = 0;
		};
	}
}
