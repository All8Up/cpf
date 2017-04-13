//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/Resource.hpp"
#include "Events/Emitter.hpp"
#include "IO/Stream.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "UnorderedSet.hpp"


namespace Cpf
{
	namespace Resources
	{
		struct ID;
		class Cache;
		class Loader;
		class Volume;
		class Monitor;

		class Locator : public tRefCounted<>, public Events::Emitter
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Mounted = Events::Event<0, Function<void(const char* const, Volume*)>>;
			using Unmounted = Events::Event<1, Function<void(const char* const, Volume*)>>;

			//////////////////////////////////////////////////////////////////////////
			struct LoaderInfo
			{
				Loader* mpLoader;
				Cache* mpCache;
			};

			//////////////////////////////////////////////////////////////////////////
			CPF_EXPORT_RESOURCES static Locator* Create();

			//////////////////////////////////////////////////////////////////////////
			bool Mount(const char* const, Volume*);
			bool Unmount(Volume*);

			bool Attach(const char* const, Cache*);
			bool Detach(const char* const);
			Cache* GetCache(const char* const) const;

			bool Attach(Monitor*);
			bool Detach(Monitor*);

			bool Install(Loader*, Cache*);
			bool Remove(Loader*);
			const LoaderInfo* GetLoader(uint32_t id) const;

			Platform::IO::Stream* Open(ID) const;
			template<typename TYPE>
			typename TYPE::Resource* Load(ID);
			ResourceBase* GetResource(ID) const;

			bool Touch(ID);
			void TouchAll();

		private:
			//////////////////////////////////////////////////////////////////////////
			Locator();
			virtual ~Locator();

			//////////////////////////////////////////////////////////////////////////
			struct VolumeEntry
			{
				String mMountPoint;
				Volume* mpVolume;
			};
			Vector<VolumeEntry> mVolumes;
			UnorderedMap<String, Cache*> mCaches;
			UnorderedSet<Monitor*> mMonitors;
			UnorderedMap<uint32_t, LoaderInfo> mLoaders;
		};

		template<typename TYPE>
		typename TYPE::Resource* Locator::Load(ID id)
		{
			auto info = GetLoader(TYPE::kID);
			if (info != nullptr)
			{
				return static_cast<typename TYPE::Resource*>((*static_cast<TYPE*>(info->mpLoader))(id));
			}
			return nullptr;
		}
	}
}
