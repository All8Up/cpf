//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/iClassInstance.hpp"

namespace CPF
{
	namespace Plugin
	{
		/**
		* @brief A helper to create class instances.
		* @tparam TYPE Type of instance to create.
		*/
		template <typename TYPE>
		struct tClassInstance : iClassInstance
		{
			tClassInstance(int32_t* externalRef = nullptr) : mRefCount(1), mExternalRef(externalRef) {}
			virtual ~tClassInstance() {}

			GOM::Result CPF_STDCALL QueryInterface(uint64_t, void**) override
			{
				return GOM::kNotImplemented;
			}
			int32_t CPF_STDCALL AddRef() override
			{
				return ++mRefCount;
			}
			int32_t CPF_STDCALL Release() override
			{
				if (--mRefCount == 0)
				{
					delete this;
					return 0;
				}
				return mRefCount;
			}

			GOM::Result CPF_STDCALL CreateInstance(iRegistry* regy, iUnknown* outer, iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new TYPE(regy, outer);
					if (*outIface)
					{
						if (mExternalRef)
							++*mExternalRef;
						return GOM::kOK;
					}
					return GOM::kOutOfMemory;
				}
				return GOM::kInvalidParameter;
			}

		private:
			int32_t mRefCount;
			int32_t* mExternalRef;
		};
	}
}

#define CPF_CLASSINSTANCE_ACCESS(name) friend struct CPF::Plugin::tClassInstance<name>;
