//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/iCache.hpp"
#include "UnorderedMap.hpp"

namespace CPF
{
	namespace Resources
	{
		namespace Caches
		{
			static constexpr GOM::ClassID kCacheDefaultCID = GOM::ClassID("Cpf::Resources::Caches::Default"_crc64);

			/** @brief A default cache implementation. */
			class Default : public tRefCounted<iCache>
			{
			public:
				// Construction/Destruction.
				Default(iUnknown*);
				virtual ~Default();

				static const char* const kCacheName;

				struct Descriptor : CacheDesc
				{};

				// iBase overrides.
				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				static iCache* Create(const CacheDesc* const desc);
				static CacheDesc* CreateDescriptor(const rapidjson::Value&);

				// Overrides of Cache.
				ResourceBase* CPF_STDCALL Get(ID) const override;
				void CPF_STDCALL Store(ID, ResourceBase*) override;
				void CPF_STDCALL LastReference(ID) override;
				void CPF_STDCALL Enumerate(Function<void(ResourceBase*)>) override;

			private:
				// Implementation types.
				using ResourceMap = UnorderedMap<uint64_t, ResourceBase*>;

				// Implementation data.
				ResourceMap mResources;
				bool mShuttingDown;
			};
		}
	}
}
