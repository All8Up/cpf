/**
* @brief Declares the refcounted interface class.
*/
#pragma once
#include "RefCount.hpp"

namespace Cpf
{
	class CPF_EXPORT_REFCOUNT iRefCounted
	{
	public:
		virtual int32_t AddRef() = 0;
		virtual int32_t Release() = 0;

	protected:
		virtual ~iRefCounted() = 0;
	};

	inline int32_t SafeAddRef(iRefCounted* rc)
	{
		if (rc)
			return rc->AddRef();
		return 0;
	}
	inline int32_t SafeRelease(iRefCounted* rc)
	{
		if (rc)
			return rc->Release();
		return 0;
	}

	template<typename BASE = iRefCounted>
	class tRefCounted : public BASE
	{
	public:
		template<typename... PARAMS>
		tRefCounted(PARAMS... params) : BASE(params...), mRefCount(1) {}
		tRefCounted() : mRefCount(1) {}

		virtual int32_t AddRef() override
		{
			CPF_ASSERT(mRefCount > 0);
			return ++mRefCount;
		}
		virtual int32_t Release() override
		{
			CPF_ASSERT(mRefCount > 0);
			if (--mRefCount == 0)
			{
				delete this;
				return 0;
			}
			return mRefCount;
		}


	private:
		int32_t mRefCount;
	};
}
