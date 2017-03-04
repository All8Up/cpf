//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Threading/Export.hpp"

namespace Cpf
{
	//////////////////////////////////////////////////////////////////////////
	/// Threading library initializer.
	//////////////////////////////////////////////////////////////////////////
	struct ThreadingInitializer
	{
		CPF_EXPORT_THREADING static int Install();
		CPF_EXPORT_THREADING static int Remove();

	private:
		ThreadingInitializer() = delete;
		~ThreadingInitializer() = delete;
	};


	namespace Threading
	{
		//////////////////////////////////////////////////////////////////////////
		class CPF_EXPORT_THREADING ConditionVariable;
		class CPF_EXPORT_THREADING Mutex;
		class CPF_EXPORT_THREADING Semaphore;
		class CPF_EXPORT_THREADING Thread;

		//////////////////////////////////////////////////////////////////////////
		CPF_EXPORT_THREADING int GetHardwareConcurrency();
	}
}
