//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/Shader.hpp"
#include "CPF/Platform/Graphics/iBlob.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Driver;
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
