//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;

		enum class EnumMode : int32_t;
		enum class Format : int32_t;
		struct OutputDesc;
		struct ModeDesc;

		struct iOutput : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iOutput"_crc64);

			virtual bool GetDesc(OutputDesc*) const = 0;
			virtual bool EnumerateModes(Format format, EnumMode enumMode, int32_t& count, ModeDesc*) = 0;
			virtual bool FindClosestMatch(const ModeDesc* matchMode, ModeDesc* closest, iDevice* compatibleCheck) = 0;
			virtual bool WaitForVBlank() = 0;
		};
	}
}
