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
			static constexpr auto kID = MultiCore::SystemID("Timer System"_crc64);

			// Registration.
			static bool Install();
			static bool Remove();

			// Timer interface.
			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;

		private:
			// Construction/Destruction.
			Timer(const String& name);
			~Timer() override;

			//
			static System* Creator(const String& name, const Desc*);

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;

			// The internal update stage.
			IntrusivePtr<MultiCore::SingleUpdateStage> mpUpdate;
		};
	}
}
