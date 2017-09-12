//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Concurrency/iFence.hpp"
#include "Threading/Semaphore.hpp"

namespace CPF
{
	namespace Concurrency
	{
		class Fence : public tRefCounted<iFence>
		{
		public:
			Fence(iUnknown*);
			virtual ~Fence() {}

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			void CPF_STDCALL Wait() override;
			void CPF_STDCALL Signal() override;

		private:
			Threading::Semaphore mSemaphore;
		};
	}
}
