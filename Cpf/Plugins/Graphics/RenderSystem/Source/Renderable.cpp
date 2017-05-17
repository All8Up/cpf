//////////////////////////////////////////////////////////////////////////
#include "Renderable.hpp"

using namespace Cpf;

Renderable::Renderable(GOM::iUnknown*)
{}

GOM::Result CPF_STDCALL Renderable::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;

		case iRenderable::kIID.GetID():
			*outIface = static_cast<iRenderable*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


void CPF_STDCALL Renderable::SetSystem(MultiCore::iSystem*)
{}

MultiCore::iSystem* CPF_STDCALL Renderable::GetSystem()
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
