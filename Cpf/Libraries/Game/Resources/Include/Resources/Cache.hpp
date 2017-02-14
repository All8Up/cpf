//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/Resource.hpp"
#include "Resources/ID.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"

namespace Cpf
{
	namespace Resources
	{
		/** @brief Base class for cache implementations. */
		class Cache : public iRefCounted
		{
		public:
			virtual ResourceBase* Get(ID) const = 0;
			virtual void Store(ID, ResourceBase*) = 0;
			virtual void LastReference(ID) = 0;
			virtual void Enumerate(Function<void (ResourceBase*)>) = 0;

			template<typename TYPE>
			TYPE* Get(ID id) const;

			struct Descriptor
			{};
		};

		/**
		 * @brief The the content and casts it appropriately.
		 * @tparam TYPE Type of the returned pointer..
		 * @param id The id of the item to retrieve.
		 * @return The resource for the given ID.
		 */
		template<typename TYPE>
		TYPE* Cache::Get(ID id) const
		{
			return static_cast<TYPE*>(Get(id));
		}
	}
}
