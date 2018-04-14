//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iShader.hpp"
#include "Driver/D3D12/D3D12Utils.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
	}
	namespace Driver
	{
		namespace D3D12
		{
			class Shader final : public GOM::tUnknown<Graphics::iShader>
			{
			public:
				Shader();
				virtual ~Shader();

				bool LoadFrom(Graphics::iDevice* device, Graphics::iBlob*) override;

				D3D12_SHADER_BYTECODE GetByteCode() const;

			private:
				D3D12_SHADER_BYTECODE mByteCode;
			};
		}
	}
}
