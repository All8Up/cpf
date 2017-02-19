//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Types.hpp"
#include "String.hpp"
#include "RefCount.hpp"
#include "UnorderedMap.hpp"

namespace Cpf
{
	namespace GO
	{
		/*
		Systems contain pointers to dependent systems.  So, for instance,
		movement needs the game time system so it would depend on that system.
		But, as there are potentially multiple game time systems driving
		different items such as UI versus game play the system must be
		initialized with the unique expected system names.  I.e. "UITime"
		versus "GameTime".
		*/
		class System : public tRefCounted<iRefCounted>
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			System(Service* service);

			Service* GetService() const;

			virtual const StageVector& GetStages() const;

			virtual void Activate();
			virtual void Deactivate();

		protected:
			//////////////////////////////////////////////////////////////////////////
			void Add(Stage*);
			void Remove(Stage*);

		private:
			//////////////////////////////////////////////////////////////////////////
			Service* mpService;
			StageVector mStages;
		};
	}
}
