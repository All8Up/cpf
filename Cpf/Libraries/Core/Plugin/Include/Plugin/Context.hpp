//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/iRegistry.hpp"

namespace Cpf
{
	namespace Plugin
	{
		class Context
		{
		public:
			Context() : mpRegistry(nullptr), mRefCount(0) {}

			void SetRegistry(iRegistry* regy) { mpRegistry = regy; }
			iRegistry* GetRegistry() const { return mpRegistry; }
			int32_t GetRefCount() const { return mRefCount; }
			int32_t AddRef() { return ++mRefCount; }
			int32_t Release() { return --mRefCount; }

		private:
			iRegistry* mpRegistry;
			int32_t mRefCount;
		};
	}
}
