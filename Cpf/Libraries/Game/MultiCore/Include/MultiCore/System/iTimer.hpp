//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		static constexpr COM::ClassID kTimerCID = COM::ClassID("TimerClass"_crc64);

		struct iTimer : public iSystem
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iTimer"_crc64);

			virtual Time::Value CPF_STDCALL GetTime() const = 0;
			virtual float CPF_STDCALL GetDeltaTime() const = 0;
			virtual bool CPF_STDCALL IsPaused() const = 0;
			virtual void CPF_STDCALL SetPause(bool flag) = 0;
			virtual void CPF_STDCALL Pause() = 0;
			virtual void CPF_STDCALL Resume() = 0;
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
