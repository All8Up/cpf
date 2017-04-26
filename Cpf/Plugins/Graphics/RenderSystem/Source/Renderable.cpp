//////////////////////////////////////////////////////////////////////////
#include "Renderable.hpp"

using namespace Cpf;

Renderable::Renderable(COM::iUnknown*)
{}

COM::Result CPF_STDCALL Renderable::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;

		case iRenderable::kIID.GetID():
			*outIface = static_cast<iRenderable*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}


void CPF_STDCALL Renderable::SetOwner(MultiCore::iSystem*)
{}

MultiCore::iSystem* CPF_STDCALL Renderable::GetOwner()
{
	return nullptr;
}

EntityService::iEntity* CPF_STDCALL Renderable::GetEntity() const
{
	return nullptr;
}

void CPF_STDCALL Renderable::SetEntity(EntityService::iEntity*)
{}

void CPF_STDCALL Renderable::Initialize()
{}

void CPF_STDCALL Renderable::Shutdown()
{}

void CPF_STDCALL Renderable::Activate()
{}

void CPF_STDCALL Renderable::Deactivate()
{}
