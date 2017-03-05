/**
* @brief Declares the refcounted interface class.
*/
#pragma once
#include "RefCount.hpp"
#include "Hash/HashID.hpp"

namespace Cpf
{
	using InterfaceID = Hash::HashID<uint64_t, 0>;

	struct CPF_NOVTABLE iRefCounted
	{
		virtual int32_t AddRef() = 0;
		virtual int32_t Release() = 0;

	protected:
		virtual ~iRefCounted() {};
	};

	struct CPF_NOVTABLE iUnknown : iRefCounted
	{
		static constexpr auto kIID = InterfaceID("iUnknown Interface"_crc64);

		virtual bool QueryInterface(InterfaceID id, void**) = 0;
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

	CPF_DLL_SAFE_BEGIN

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

	CPF_DLL_SAFE_END
}
