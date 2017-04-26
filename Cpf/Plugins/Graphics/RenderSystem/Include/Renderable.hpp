//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iRenderable.hpp"

namespace Cpf
{
	class Renderable : public tRefCounted<iRenderable>
	{
	public:
		Renderable(COM::iUnknown*);

		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

		// iComponent
		void CPF_STDCALL SetOwner(MultiCore::iSystem*) override;
		MultiCore::iSystem* CPF_STDCALL GetOwner() override;

		EntityService::iEntity* CPF_STDCALL GetEntity() const override;
		void CPF_STDCALL SetEntity(EntityService::iEntity* entity) override;

		void CPF_STDCALL Initialize() override;
		void CPF_STDCALL Shutdown() override;

		void CPF_STDCALL Activate() override;
		void CPF_STDCALL Deactivate() override;
	};
}
