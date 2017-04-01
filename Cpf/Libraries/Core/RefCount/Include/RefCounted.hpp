/**
* @brief Declares the refcounted interface class.
*/
#pragma once
#include "RefCount.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	//////////////////////////////////////////////////////////////////////////
	struct CPF_EXPORT CPF_NOVTABLE iRefCounted
	{
		virtual int32_t CPF_STDCALL AddRef() = 0;
		virtual int32_t CPF_STDCALL Release() = 0;

	protected:
		virtual ~iRefCounted() {};
	};

	//////////////////////////////////////////////////////////////////////////
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


	//////////////////////////////////////////////////////////////////////////
	template<typename BASE = iRefCounted, int32_t INITREF = 1>
	class tRefCounted : public BASE
	{
	public:
		template<typename... PARAMS>
		tRefCounted(PARAMS... params) : BASE(params...), mRefCount(INITREF) {}
		tRefCounted() : mRefCount(INITREF) {}

		virtual int32_t CPF_STDCALL AddRef() override
		{
			CPF_ASSERT(mRefCount > 0);
			return ++mRefCount;
		}
		virtual int32_t CPF_STDCALL Release() override
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
