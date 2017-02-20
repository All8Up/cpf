//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "GO/ObjectStage.hpp"

namespace Cpf
{
	namespace GO
	{
		class Timer : public MultiCore::System
		{
		public:
			//
			static constexpr int64_t kID = "Timer System"_crc64;

			// Registration.
			static bool Install();
			static bool Remove();

			// Timer interface.
			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;

		private:
			// Construction/Destruction.
			Timer(MultiCore::Pipeline* owner, const String& name);
			~Timer() override;

			//
			static System* Creator(MultiCore::Pipeline* owner, const String& name);

			// Internal update function.
			static void _Update(System*, Object*);

			// Implementation data.
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;

			// The internal update stage.
			IntrusivePtr<ObjectStage> mpUpdate;
		};
	}
}
