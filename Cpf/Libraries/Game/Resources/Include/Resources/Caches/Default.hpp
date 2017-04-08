//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Cache.hpp"
#include "UnorderedMap.hpp"

namespace Cpf
{
	namespace Resources
	{
		namespace Caches
		{
			/** @brief A default cache implementation. */
			class Default : public tRefCounted<Cache>
			{
			public:
				static const char* const kCacheName;

				struct Descriptor : public Cache::Descriptor
				{};

				CPF_EXPORT_RESOURCES static Cache* Create(const Cache::Descriptor* const desc);
				CPF_EXPORT_RESOURCES static Cache::Descriptor* CreateDescriptor(const rapidjson::Value&);

				// Overrides of Cache.
				ResourceBase* Get(ID) const override;
				void Store(ID, ResourceBase*) override;
				void LastReference(ID) override;
				void Enumerate(Function<void(ResourceBase*)>) override;

			private:
				// Construction/Destruction.
				Default();
				virtual ~Default();

				// Implementation types.
				using ResourceMap = UnorderedMap<uint64_t, ResourceBase*>;

				// Implementation data.
				ResourceMap mResources;
				bool mShuttingDown;
			};
		}
	}
}
