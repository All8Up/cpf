//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/IO.hpp"

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			/** @brief An archive. */
			class Archive
			{
			public:
				Archive() {}
				virtual ~Archive() = 0;
			};
		}
	}
}
