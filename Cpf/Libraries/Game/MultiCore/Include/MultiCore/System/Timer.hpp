//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		class Timer : public System
		{
		public:
			static constexpr auto kID = "Timer System"_hashString;

			// Registration.
			static bool Install();
			static bool Remove();

			// Timer interface.
			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;
			bool IsPaused() const;
			void SetPause(bool flag);
			void Pause();
			void Resume();

		private:
			// Construction/Destruction.
			Timer(Pipeline* owner, const char* name);
			~Timer() override;

			//
			static System* Creator(Pipeline* owner, const char* name, const Desc*);

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;
			Platform::Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<SingleUpdateStage> mpUpdate;
		};
	}
}
