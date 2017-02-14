//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iShader.hpp"
#include "Adapters/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class iDevice;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class Shader : public tRefCounted<Graphics::iShader>
			{
			public:
				Shader();
				~Shader() override;

				bool LoadFrom(Graphics::iDevice* device, const Graphics::BinaryBlob*) override;

				D3D12_SHADER_BYTECODE GetByteCode() const;

			private:
				D3D12_SHADER_BYTECODE mByteCode;
			};
		}
	}
}
