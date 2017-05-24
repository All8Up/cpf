//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iRenderable.hpp"

namespace Cpf
{
	class Renderable : public tRefCounted<iRenderable>
	{
	public:
		Renderable(GOM::iBase*);

		GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

		// iComponent
		void CPF_STDCALL SetSystem(MultiCore::iSystem*) override;
		MultiCore::iSystem* CPF_STDCALL GetSystem() override;

		EntityService::iEntity* CPF_STDCALL GetEntity() const override;
		void CPF_STDCALL SetEntity(EntityService::iEntity* entity) override;

		void CPF_STDCALL Initialize() override;
		void CPF_STDCALL Shutdown() override;

		void CPF_STDCALL Activate() override;
		void CPF_STDCALL Deactivate() override;
	};
}
