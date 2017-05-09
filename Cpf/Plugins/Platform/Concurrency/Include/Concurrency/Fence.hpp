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
			Fence(iUnknown*);
			virtual ~Fence() {}

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			void CPF_STDCALL Wait() override;
			void CPF_STDCALL Signal() override;

		private:
			Threading::Semaphore mSemaphore;
		};
	}
}
