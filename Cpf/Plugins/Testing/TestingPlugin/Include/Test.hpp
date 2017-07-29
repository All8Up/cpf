//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iTest.hpp"
#include "RefCounted.hpp"

namespace Testing
{
	/*
	 * Test plugin implementation.  Uses no helpers in order to show a full
	 * implementation and so that it can be modified a bit for unit test
	 * reasons.
	 */
	class Test : public iTest
	{
	public:
		Test(iUnknown*);
		virtual ~Test();

		int32_t CPF_STDCALL AddRef() override;
		int32_t CPF_STDCALL Release() override;
		Cpf::GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		int32_t CPF_STDCALL Tester(int64_t) override;

	private:
		int32_t mRefCount;
	};
}
