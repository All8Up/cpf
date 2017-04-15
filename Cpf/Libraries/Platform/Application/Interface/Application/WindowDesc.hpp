//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Vector2v.hpp"
#include "String.hpp"

namespace Cpf
{
	class WindowedApplication;
	struct iWindow;
	enum class WindowFlags : int32_t;

	struct WindowDesc
	{
		WindowDesc(WindowedApplication* app);

		WindowDesc& Title(const String& title);
		WindowDesc& Position(const Math::Vector2i& pos);
		WindowDesc& Size(const Math::Vector2i& size);
		WindowDesc& Flags(WindowFlags flags);

		operator iWindow* () const;

		String mTitle;
		Math::Vector2i mPosition;
		Math::Vector2i mSize;
		WindowFlags mFlags;

		WindowedApplication* mpApplication;
	};

	/*
	struct WindowDesc
	{
		const char* mpTitle;
		int32_t mX, mY;
		int32_t mWidth, mHeight;
		WindowFlags mFlags;
	};
	*/
}
