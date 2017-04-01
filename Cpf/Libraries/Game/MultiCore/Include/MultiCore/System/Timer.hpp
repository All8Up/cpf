//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		struct iTimer : iSystem
		{
			virtual Time::Value GetTime() = 0;
			virtual float GetDeltaTime() = 0;
			virtual bool IsPaused() = 0;
			virtual void SetPause(bool flag) = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
		};

		class CPF_EXPORT_MULTICORE Timer : public System
		{
		public:
			static constexpr SystemID kID = Hash::Create<SystemID_tag>("Timer System"_hashString);

			// Registration.
			static bool Install();
			static bool Remove();

			// Timer interface.
			Time::Value GetTime() const;
			float GetDeltaTime() const;
			bool IsPaused() const;
			void SetPause(bool flag);
			void Pause();
			void Resume();

		private:
			// Construction/Destruction.
			Timer(iPipeline* owner, const char* name);
			~Timer() override;

			//
			static System* Creator(iPipeline* owner, const char* name, const Desc*);

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Time::Value mTime;
			Time::Value mStart;
			Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<SingleUpdateStage> mpUpdate;
		};
	}
}
