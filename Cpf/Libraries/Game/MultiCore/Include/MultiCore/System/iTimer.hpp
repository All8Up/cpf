//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		class CPF_EXPORT_MULTICORE Timer : public System
		{
		public:
			static constexpr SystemID kID = Hash::Create<SystemID_tag>("Timer System"_hashString);

			// Registration.
			static bool Install();
			static bool Remove();

			// System overrides.
			COM::Result CPF_STDCALL Initialize(iPipeline* owner, const char* name) override;

			// Timer interface.
			Time::Value GetTime() const;
			float GetDeltaTime() const;
			bool IsPaused() const;
			void SetPause(bool flag);
			void Pause();
			void Resume();

		private:
			// Construction/Destruction.
			Timer();
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
