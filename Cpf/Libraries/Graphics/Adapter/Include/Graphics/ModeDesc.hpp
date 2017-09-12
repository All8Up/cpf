//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Ratio.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class ScanlineOrder : int32_t;
		enum class ModeScaling : int32_t;

		struct ModeDesc
		{
			int32_t mWidth;
			int32_t mHeight;
			Ratio mRefreshRate;
			Format mFormat;
			ScanlineOrder mScanLineOrder;
			ModeScaling mModeScaling;
			bool mStereo;
		};
	}
}
