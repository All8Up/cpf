//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iFence : public iRefCounted
		{
		public:
			virtual ~iFence() = 0;

			virtual uint64_t GetValue() const = 0;
			virtual void WaitFor(uint64_t value) = 0;
		};
	}
}
