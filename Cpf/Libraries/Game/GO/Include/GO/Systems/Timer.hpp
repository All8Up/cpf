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
			//
			Timer(Service* service);
			~Timer() override;

			//
			void Activate() override;
			void Deactivate() override;

			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;

		private:
			//
			static void _Update(System*, Object*);

			//
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;

			//
			Stage* mpUpdate;
		};
	}
}
