//////////////////////////////////////////////////////////////////////////
#include "Renderable.hpp"

using namespace Cpf;

Renderable::Renderable(GOM::iBase*)
{}

GOM::Result CPF_STDCALL Renderable::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
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
