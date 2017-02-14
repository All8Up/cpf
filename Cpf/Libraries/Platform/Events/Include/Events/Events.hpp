//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_EVENTS
#		define CPF_EXPORT_EVENTS
#	else // CPF_STATIC_EVENTS
#		if CPF_BUILD_EVENTS
#			define CPF_EXPORT_EVENTS CPF_EXPORT
#		else
#			define CPF_EXPORT_EVENTS CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_EVENTS CPF_EXPORT
#	else
#		define CPF_EXPORT_EVENTS
#	endif
#endif // CPF_TARGET_WINDOWS



//////////////////////////////////////////////////////////////////////////
// Forward references.
namespace Cpf
{
	namespace Platform
	{
		struct EventsInitializer
		{
			CPF_EXPORT_EVENTS static int Install();
			CPF_EXPORT_EVENTS static int Remove();

		private:
			EventsInitializer() = delete;
			~EventsInitializer() = delete;
		};

		namespace Events
		{
			class EmitterBase;
			class Emitter;
			class DeferredEmitter;
			class EventBase;
			class HandleBase;
			class Handle;
		}
	}
}
