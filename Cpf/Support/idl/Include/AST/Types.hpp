//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <stdint.h>

namespace AST
{
	enum class IntegralType : uint32_t
	{
		Unknown		= 0,
		U8			= 1<<0,
		S8,
		U16,
		S16,
		U32,
		S32,
		U64,
		S64
	};

	std::string TypeString(IntegralType type);
}
