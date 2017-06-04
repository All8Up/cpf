//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iTest.hpp"
#include "RefCounted.hpp"

namespace Testing
{
	class Test : public Cpf::tRefCounted<iTest>
	{
	public:
		Test(iBase*);
		virtual ~Test();

		Cpf::GOM::Result CPF_STDCALL Cast(Cpf::GOM::InterfaceID id, void** outIface) override;
	};
}
