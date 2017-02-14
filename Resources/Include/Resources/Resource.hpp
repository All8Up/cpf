//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/ID.hpp"
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Resources
	{
		class Cache;

		/** @brief The base resource class. */
		class ResourceBase : public iRefCounted
		{
		public:
			int32_t AddRef() override;
			int32_t Release() override;

			virtual void Update() = 0;

		protected:
			ResourceBase(ID, Cache*);
			virtual ~ResourceBase();

		private:
			int32_t mRefCount;
			ID mID;
			Cache* mpCache;
		};
	}
}
