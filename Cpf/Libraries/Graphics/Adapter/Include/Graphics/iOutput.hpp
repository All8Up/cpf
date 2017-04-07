//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/Ratio.hpp"
#include "Math/Rectangle.hpp"
#include "EnumFlagType.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class iDevice;

		enum class ScanlineOrder : int32_t;
		enum class ModeScaling : int32_t;
		enum class ModeRotation : int32_t;
		enum class EnumMode : int32_t;
		struct OutputDesc;
		struct ModeDesc;

		class iOutput : public iRefCounted
		{
		public:
			virtual ~iOutput() = 0;

			virtual bool GetDesc(OutputDesc*) const = 0;
			virtual bool EnumerateModes(Format format, EnumMode enumMode, int32_t& count, ModeDesc*) = 0;
			virtual bool FindClosestMatch(const ModeDesc* matchMode, ModeDesc* closest, iDevice* compatibleCheck) = 0;
			virtual bool WaitForVBlank() = 0;
		};
	}
}
