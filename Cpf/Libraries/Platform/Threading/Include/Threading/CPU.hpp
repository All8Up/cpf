//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading.hpp"

// TODO: Cleanup multiple targets.
#if CPF_TARGET_WINDOWS
#include <Pdh.h>

namespace Cpf
{
	namespace Threading
	{
		class CPF_EXPORT_THREADING CPUUsage
		{
		public:
			CPUUsage();
			~CPUUsage();

			float GetValue() const;

		private:
			PDH_HQUERY mQuery;
			PDH_HCOUNTER mTotal;
		};
	}
}
#else
#endif
