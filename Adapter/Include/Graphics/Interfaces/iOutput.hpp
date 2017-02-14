//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/Ratio.hpp"
#include "Math/Rectangle.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class iDevice;

		enum class ScanLineOrder : int32_t
		{
			eUnspecified,
			eProgressive,
			eUpperFieldFirst,
			eLowerFieldFirst
		};

		enum class ModeScaling : int32_t
		{
			eUnspecified,
			eCentered,
			eStretched
		};

		enum class ModeRotation : int32_t
		{
			eUnspecified,
			eIdentity,
			eRotated90,
			eRotated180,
			eRotated270
		};

		struct OutputDesc
		{
			char mName[32];
			Math::Rectanglei mDesktopCoordinates;
			bool mAttachedToDesktop;
			ModeRotation mRotation;
		};

		struct ModeDesc
		{
			int32_t mWidth;
			int32_t mHeight;
			Ratio mRefreshRate;
			Format mFormat;
			ScanLineOrder mScanLineOrder;
			ModeScaling mModeScaling;
			bool mStereo;
		};

		struct EnumMode
		{
			enum : uint32_t
			{
				eNone = 0,
				eInterlaced = 1 << 0,
				eScaling = 1 << 1,
				eStereo = 1 << 2,
				eDisabledStereo = 1 << 3
			};
		};

		class iOutput : public iRefCounted
		{
		public:
			virtual ~iOutput() = 0;

			virtual bool GetDesc(OutputDesc*) const = 0;
			virtual bool EnumerateModes(Format format, uint32_t enumMode, int32_t& count, ModeDesc*) = 0;
			virtual bool FindClosestMatch(const ModeDesc* matchMode, ModeDesc* closest, iDevice* compatibleCheck) = 0;
			virtual bool WaitForVBlank() = 0;
		};
	}
}
