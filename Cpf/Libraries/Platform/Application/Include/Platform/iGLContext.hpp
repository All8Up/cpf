//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	class iWindow;

	namespace Platform
	{
		struct iGLContext
		{
			virtual ~iGLContext() = 0;
			virtual void Swap(iWindow* window) = 0;
		};
	}
}
