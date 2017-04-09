//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ModeRotation : int32_t;

		struct OutputDesc
		{
			char mName[32];
			Math::Rectanglei mDesktopCoordinates;
			bool mAttachedToDesktop;
			ModeRotation mRotation;
		};
	}
}
