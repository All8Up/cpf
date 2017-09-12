//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Concurrency
	{
		struct iScheduler;

		struct WorkContext
		{
			iScheduler* mpScheduler;
			int mThreadId;
			mutable void* mpUserData;
		};
	}
}
