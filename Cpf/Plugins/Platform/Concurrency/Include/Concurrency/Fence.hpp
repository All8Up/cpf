//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Concurrency/iFence.hpp"
#include "Threading/Semaphore.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		class Fence : public tRefCounted<iFence>
		{
		public:
			Fence(iBase*);
			virtual ~Fence() {}

			GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

			void CPF_STDCALL Wait() override;
			void CPF_STDCALL Signal() override;

		private:
			Threading::Semaphore mSemaphore;
		};
	}
}
