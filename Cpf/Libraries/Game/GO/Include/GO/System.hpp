//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Types.hpp"
#include "RefCount.hpp"

namespace Cpf
{
	namespace GO
	{
		class System : public tRefCounted<iRefCounted>
		{
		public:
			using StageMap = UnorderedMap<String, IntrusivePtr<Stage>>;
			virtual StageMap& GetStages() = 0;
		};
	}
}
