//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/iRefCounted.hpp"
#include "CPF/Platform/Concurrency/iFence.hpp"
#include "CPF/Threading/Semaphore.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Platform
	{
		class Fence : public tRefCounted<iFence>
		{
		public:
			Fence(Plugin::iRegistry*, iUnknown*);
			virtual ~Fence() {}

			GOM::Result CPF_STDCALL QueryInterface(GOM::IID id, void** outIface) override;

			void CPF_STDCALL Wait() override;
			void CPF_STDCALL Signal() override;

		private:
			Threading::Semaphore mSemaphore;
		};
	}
}
