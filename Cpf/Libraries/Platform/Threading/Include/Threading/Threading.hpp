//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_THREADING
#		define CPF_EXPORT_THREADING
#	else // CPF_STATIC_THREADING
#		if CPF_BUILD_THREADING
#			define CPF_EXPORT_THREADING CPF_EXPORT
#		else
#			define CPF_EXPORT_THREADING CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_THREADING CPF_EXPORT
#	else
#		define CPF_EXPORT_THREADING
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Platform
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
			class Team;

			//////////////////////////////////////////////////////////////////////////
			CPF_EXPORT_THREADING int GetHardwareConcurrency();
		}
	}
}
