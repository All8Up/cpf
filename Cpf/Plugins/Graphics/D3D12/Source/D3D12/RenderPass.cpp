//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/RenderPass.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

COM::Result CPF_STDCALL RenderPass::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case Graphics::iRenderPass::kIID.GetID():
			*outIface = static_cast<iRenderPass*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL RenderPass::Initialize(const Graphics::RenderPassDesc* desc)
{
	if (desc == nullptr)
		return COM::kInvalidParameter;

	return COM::kOK;
}
