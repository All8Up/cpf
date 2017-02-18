//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <d3d12.h>
#include <dxgi1_5.h>
#include <d3dcommon.h>
#include <D3Dcompiler.h>
#include <d3d12sdklayers.h>
#include "Adapter/D3D12/d3dx12.h"
#include "Graphics/Format.hpp"
#include "Graphics/Interfaces/iOutput.hpp"
#include "Graphics/Interfaces/iSwapChain.hpp"
#include "Graphics/Interfaces/iCommandBuffer.hpp"

#define SAFE_RELEASE(a) {if (a) a->Release();}


namespace Cpf
{
	namespace Graphics
	{
		class ResourceBindingDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			DXGI_FORMAT Convert(Graphics::Format pf);
			Graphics::Format Convert(DXGI_FORMAT pf);
			Graphics::ScanLineOrder Convert(DXGI_MODE_SCANLINE_ORDER order);
			Graphics::ModeScaling Convert(DXGI_MODE_SCALING scaling);
			DXGI_SWAP_EFFECT Convert(Graphics::SwapEffect swapEffect);
			D3D12_RESOURCE_STATES Convert(Graphics::ResourceState resourceState);
			UINT Convert(Graphics::SubResource sr);
			UINT ConvertEnumMode(uint32_t mode);
			bool Convert(const Graphics::ResourceBindingDesc&, ID3DBlob** result);
		}
	}
}
