//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/iExecutor.hpp"
#include "Threading/Reactor.hpp"
#include "Threading/Thread.hpp"

namespace CPF
{
	namespace IO
	{
		static constexpr GOM::ClassID kDefaultExecutorCID = GOM::ClassID("CPF::IO::DefaultExecutor"_crc64);

		class DefaultExecutor : public tRefCounted<iExecutor>
		{
		public:
			DefaultExecutor(Plugin::iRegistry*, iUnknown*);
			virtual ~DefaultExecutor();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			Threading::Reactor::WorkQueue* GetQueue() override;

		private:
			Threading::Reactor mReactor;
			Threading::Reactor::WorkQueue mQueue;
			Threading::Thread mWorker;
		};

		//////////////////////////////////////////////////////////////////////////
		inline DefaultExecutor::DefaultExecutor(Plugin::iRegistry*, iUnknown*)
		{
			mQueue.Initialize(&mReactor);
			mWorker = Move(Threading::Thread([&]()
			{
				mReactor.Run();
			}));
		}

		inline DefaultExecutor::~DefaultExecutor()
		{
			mReactor.Quit();
			mWorker.Join();
		}

		inline GOM::Result CPF_STDCALL DefaultExecutor::QueryInterface(uint64_t id, void** outIface)
		{
			if (outIface)
			{
				switch (id)
				{
				case iUnknown::kIID.GetID():
					*outIface = static_cast<iUnknown*>(this);
					break;
				case iExecutor::kIID.GetID():
					*outIface = static_cast<iExecutor*>(this);
					break;
				default:
					return GOM::kUnknownInterface;
				}
				AddRef();
				return GOM::kOK;
			}
			return GOM::kInvalidParameter;
		}

		inline Threading::Reactor::WorkQueue* CPF_STDCALL DefaultExecutor::GetQueue()
		{
			return &mQueue;
		}
	}
}
