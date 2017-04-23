//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Shader.hpp"
#include "Graphics/iBlob.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
Shader::Shader()
{
	mByteCode.pShaderBytecode = nullptr;
	mByteCode.BytecodeLength = 0;
	CPF_LOG(D3D12, Info) << "Created shader: " << intptr_t(this);
}

Shader::~Shader()
{
	if (mByteCode.pShaderBytecode)
		delete[] reinterpret_cast<const uint8_t*>(mByteCode.pShaderBytecode);
	CPF_LOG(D3D12, Info) << "Destroyed shader: " << intptr_t(this);
}

COM::Result CPF_STDCALL Shader::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iShader::kIID.GetID():
			*outIface = static_cast<iShader*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool Shader::LoadFrom(Graphics::iDevice*, Graphics::iBlob* blob)
{
	if (blob && blob->GetSize() > 0)
	{
		uint8_t* data = new uint8_t[blob->GetSize()];
		::memcpy(data, blob->GetData(), blob->GetSize());
		mByteCode.pShaderBytecode = data;
		mByteCode.BytecodeLength = blob->GetSize();
		return true;
	}
	return false;
}

D3D12_SHADER_BYTECODE Shader::GetByteCode() const
{
	return mByteCode;
}
