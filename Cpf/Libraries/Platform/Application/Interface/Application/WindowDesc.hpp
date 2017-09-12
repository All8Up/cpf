//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Vector2v.hpp"
#include "String.hpp"

namespace CPF
{
	struct iWindow;
	struct iWindowedApplication;
	enum class WindowFlags : int32_t;

	/** @brief Descriptor for window creation. */
	struct WindowDesc
	{
		const char* mpTitle;
		int32_t mX, mY;
		int32_t mWidth, mHeight;
		WindowFlags mFlags;
	};
}
