//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "RefCounted.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A service is the primary integration of the main loop
		loop and the actual game systems and components.  A service is a
		container of systems related to a specific task.  For example,
		everything directly involved in game object handling is under the
		GOService. */
		class Service : public tRefCounted<iRefCounted>
		{
		public:
			Service();
			virtual ~Service();
		};
	}
}
