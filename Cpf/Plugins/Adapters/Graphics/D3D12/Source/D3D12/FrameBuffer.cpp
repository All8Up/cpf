//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/FrameBuffer.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

COM::Result CPF_STDCALL FrameBuffer::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case Graphics::iFrameBuffer::kIID.GetID():
			*outIface = static_cast<iFrameBuffer*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL FrameBuffer::Initialize(const Graphics::FrameBufferDesc* desc)
{
	if (desc == nullptr)
		return COM::kInvalidParameter;

	return COM::kOK;
}
