//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Ratio.hpp"

namespace Cpf
{
	namespace Graphics
	{
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
