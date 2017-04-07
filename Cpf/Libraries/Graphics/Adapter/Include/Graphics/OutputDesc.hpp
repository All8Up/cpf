//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct OutputDesc
		{
			char mName[32];
			Math::Rectanglei mDesktopCoordinates;
			bool mAttachedToDesktop;
			ModeRotation mRotation;
		};
	}
}
