//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Shader.hpp"
#include "Graphics/BinaryBlob.hpp"
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

bool Shader::LoadFrom(Graphics::iDevice*, const Graphics::BinaryBlob* blob)
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
