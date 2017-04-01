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
			uint32_t Error : 1; uint32_t SubSystem : 7; uint32_t Value : 16;
		};
		static_assert(sizeof(Result)==4, "Invalid result code size.");

		inline constexpr Result CreateResult(uint32_t e, uint32_t ss, uint32_t v) { return Result{e, ss, v}; }
		inline constexpr bool Succeeded(Result result) { return result.Error == 0; }
		inline constexpr bool Failed(Result result) { return result.Error != 0; }

		static constexpr Result kOK = CreateResult(0, 0, 0);
		static constexpr Result kError = CreateResult(1, 0, 0);
		static constexpr Result kUnknownInterface = CreateResult(1, 0, 1);
		static constexpr Result kInvalidParameter = CreateResult(1, 0, 2);
		static constexpr Result kOutOfMemory = CreateResult(1, 0, 3);
		static constexpr Result kUnknownClass = CreateResult(1, 0, 4);
		static constexpr Result kUnimplemented = CreateResult(1, 0, 5);

		//////////////////////////////////////////////////////////////////////////
		struct CPF_EXPORT iUnknown : iRefCounted
		{
			static constexpr InterfaceID kIID = InterfaceID("iUnknown Interface"_crc64);

			virtual Result CPF_STDCALL QueryInterface(InterfaceID id, void**) = 0;
		};
	}
}
