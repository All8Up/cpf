//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/Resource.hpp"
#include "Resources/iLocator.hpp"
#include "Events/Emitter.hpp"
#include "IO/Stream.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "UnorderedSet.hpp"


namespace CPF
{
	namespace Resources
	{
		struct ID;
		struct iCache;
		struct iMonitor;
		struct iLoader;

		class Locator : public tRefCounted<iLocator>
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			Locator(iUnknown*);
			virtual ~Locator();
			
			// iBase overrides.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void**) override;

			//
			Events::Emitter& CPF_STDCALL GetEmitter() override { return mEmitter; }

			//////////////////////////////////////////////////////////////////////////
			bool CPF_STDCALL Mount(const char* const, iVolume*) override;
			bool CPF_STDCALL Unmount(iVolume*) override;

			bool CPF_STDCALL Attach(const char* const, iCache*) override;
			bool CPF_STDCALL Detach(const char* const) override;
			iCache* CPF_STDCALL GetCache(const char* const) const override;

			bool CPF_STDCALL Attach(iMonitor*) override;
			bool CPF_STDCALL Detach(iMonitor*) override;

			bool CPF_STDCALL Install(iLoader*, iCache*) override;
			bool CPF_STDCALL Remove(iLoader*) override;
			const LoaderInfo* CPF_STDCALL GetLoader(uint32_t id) const override;

			IO::Stream* CPF_STDCALL Open(ID) const override;
			ResourceBase* CPF_STDCALL GetResource(ID) const override;

			bool CPF_STDCALL Touch(ID) override;
			void CPF_STDCALL TouchAll() override;

		private:
			//////////////////////////////////////////////////////////////////////////
			struct VolumeEntry
			{
				String mMountPoint;
				iVolume* mpVolume;
			};
			Vector<VolumeEntry> mVolumes;
			UnorderedMap<String, iCache*> mCaches;
			UnorderedSet<iMonitor*> mMonitors;
			UnorderedMap<uint32_t, LoaderInfo> mLoaders;
			Events::Emitter mEmitter;
		};
	}
}
