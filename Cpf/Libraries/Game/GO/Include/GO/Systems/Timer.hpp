//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/System.hpp"
#include "GO/Stage.hpp"

namespace Cpf
{
	namespace GO
	{
		class Timer : public System
		{
		public:
			// Construction/Destruction.
			Timer(Service* service, const String& name);
			~Timer() override;

			// System overrides.
			void Activate() override;
			void Deactivate() override;

			// Timer interface.
			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;

		private:
			// Internal update function.
			static void _Update(System*, Object*);

			// Implementation data.
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;

			// The internal update stage.
			Stage* mpUpdate;
		};
	}
}
