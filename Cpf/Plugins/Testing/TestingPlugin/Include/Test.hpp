//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iTest.hpp"
#include "RefCounted.hpp"

namespace Testing
{
	class Test : public iTest
	{
	public:
		Test(iBase*);
		virtual ~Test();

		int32_t CPF_STDCALL AddRef() override;
		int32_t CPF_STDCALL Release() override;
		Cpf::GOM::Result CPF_STDCALL Cast(uint64_t id, void** outIface) override;

		int32_t CPF_STDCALL Tester(int64_t) override;

	private:
		int32_t mRefCount;
	};
}
