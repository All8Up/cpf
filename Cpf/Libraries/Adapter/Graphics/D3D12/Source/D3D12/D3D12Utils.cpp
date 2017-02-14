//////////////////////////////////////////////////////////////////////////
#include "Adapters/D3D12/D3D12Utils.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/Interfaces/iOutput.hpp"
#include "Graphics/Descriptors/ResourceBindingDesc.hpp"
#include <dxgi1_2.h>

using namespace Cpf;
using namespace Adapters;
using namespace Graphics;

UINT D3D12::Convert(SubResource sr)
{
	switch (sr)
	{
	case SubResource::eAll:			return D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	}
	CPF_ASSERT_ALWAYS;
	return 0;
}

D3D12_RESOURCE_STATES D3D12::Convert(ResourceState resourceState)
{
	switch(resourceState)
	{
	case ResourceState::eCommon:					return D3D12_RESOURCE_STATE_COMMON;
	case ResourceState::eVertexAndConstant:			return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
	case ResourceState::eIndex:						return D3D12_RESOURCE_STATE_INDEX_BUFFER;
	case ResourceState::eRenderTarget:				return D3D12_RESOURCE_STATE_RENDER_TARGET;
	case ResourceState::eUnorderedAccess:			return D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
	case ResourceState::eDepthWrite:				return D3D12_RESOURCE_STATE_DEPTH_WRITE;
	case ResourceState::eDepthRead:					return D3D12_RESOURCE_STATE_DEPTH_READ;
	case ResourceState::eNonPixelShaderResource:	return D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
	case ResourceState::ePixelShaderResource:		return D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	case ResourceState::eStreamOut:					return D3D12_RESOURCE_STATE_STREAM_OUT;
	case ResourceState::eIndirectArgument:			return D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
	case ResourceState::eCopyDest:					return D3D12_RESOURCE_STATE_COPY_DEST;
	case ResourceState::eCopySource:				return D3D12_RESOURCE_STATE_COPY_SOURCE;
	case ResourceState::eResolveDest:				return D3D12_RESOURCE_STATE_RESOLVE_DEST;
	case ResourceState::eResolveSource:				return D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
	}
	CPF_ASSERT_ALWAYS;
	return D3D12_RESOURCE_STATES(-1);
}

DXGI_FORMAT D3D12::Convert(const Format pf)
{
	switch (pf)
	{
	case Format::eNone:		return DXGI_FORMAT_UNKNOWN;

	case Format::eR8:		return DXGI_FORMAT_R8_TYPELESS;
	case Format::eR8u:		return DXGI_FORMAT_R8_UINT;
	case Format::eR8s:		return DXGI_FORMAT_R8_SINT;
	case Format::eR8un:		return DXGI_FORMAT_R8_UNORM;
	case Format::eR8sn:		return DXGI_FORMAT_R8_SNORM;

	case Format::eR16:		return DXGI_FORMAT_R16_TYPELESS;
	case Format::eR16u:		return DXGI_FORMAT_R16_UINT;
	case Format::eR16s:		return DXGI_FORMAT_R16_SINT;
	case Format::eR16un:	return DXGI_FORMAT_R16_UNORM;
	case Format::eR16sn:	return DXGI_FORMAT_R16_SNORM;
	case Format::eR16f:		return DXGI_FORMAT_R16_FLOAT;

	case Format::eR32:		return DXGI_FORMAT_R32_TYPELESS;
	case Format::eR32u:		return DXGI_FORMAT_R32_UINT;
	case Format::eR32s:		return DXGI_FORMAT_R32_SINT;
	case Format::eR32f:		return DXGI_FORMAT_R32_FLOAT;

	case Format::eRG8:		return DXGI_FORMAT_R8G8_TYPELESS;
	case Format::eRG8u:		return DXGI_FORMAT_R8G8_UINT;
	case Format::eRG8s:		return DXGI_FORMAT_R8G8_SINT;
	case Format::eRG8un:	return DXGI_FORMAT_R8G8_UNORM;
	case Format::eRG8sn:	return DXGI_FORMAT_R8G8_SNORM;

	case Format::eRG16:		return DXGI_FORMAT_R16G16_TYPELESS;
	case Format::eRG16u:	return DXGI_FORMAT_R16G16_UINT;
	case Format::eRG16s:	return DXGI_FORMAT_R16G16_SINT;
	case Format::eRG16un:	return DXGI_FORMAT_R16G16_UNORM;
	case Format::eRG16sn:	return DXGI_FORMAT_R16G16_SNORM;
	case Format::eRG16f:	return DXGI_FORMAT_R16G16_FLOAT;

	case Format::eRG32:		return DXGI_FORMAT_R32G32_TYPELESS;
	case Format::eRG32u:	return DXGI_FORMAT_R32G32_UINT;
	case Format::eRG32s:	return DXGI_FORMAT_R32G32_SINT;
	case Format::eRG32f:	return DXGI_FORMAT_R32G32_FLOAT;

	case Format::eRGB32:	return DXGI_FORMAT_R32G32B32_TYPELESS;
	case Format::eRGB32u:	return DXGI_FORMAT_R32G32B32_UINT;
	case Format::eRGB32s:	return DXGI_FORMAT_R32G32B32_SINT;
	case Format::eRGB32f:	return DXGI_FORMAT_R32G32B32_FLOAT;

	case Format::eRGBA8:	return DXGI_FORMAT_R8G8B8A8_TYPELESS;
	case Format::eRGBA8u:	return DXGI_FORMAT_R8G8B8A8_UINT;
	case Format::eRGBA8s:	return DXGI_FORMAT_R8G8B8A8_SINT;
	case Format::eRGBA8un:	return DXGI_FORMAT_R8G8B8A8_UNORM;
	case Format::eRGBA8sn:	return DXGI_FORMAT_R8G8B8A8_SNORM;
	case Format::eRGBA8uns:	return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	case Format::eRGBA16:	return DXGI_FORMAT_R16G16B16A16_TYPELESS;
	case Format::eRGBA16u:	return DXGI_FORMAT_R16G16B16A16_UINT;
	case Format::eRGBA16s:	return DXGI_FORMAT_R16G16B16A16_SINT;
	case Format::eRGBA16un:	return DXGI_FORMAT_R16G16B16A16_UNORM;
	case Format::eRGBA16sn:	return DXGI_FORMAT_R16G16B16A16_SNORM;
	case Format::eRGBA16f:	return DXGI_FORMAT_R16G16B16A16_FLOAT;

	case Format::eRGBA32:	return DXGI_FORMAT_R32G32B32A32_TYPELESS;
	case Format::eRGBA32u:	return DXGI_FORMAT_R32G32B32A32_UINT;
	case Format::eRGBA32s:	return DXGI_FORMAT_R32G32B32A32_SINT;
	case Format::eRGBA32f:	return DXGI_FORMAT_R32G32B32A32_FLOAT;

	case Format::eD32f:		return DXGI_FORMAT_D32_FLOAT;

	/*
	DXGI_FORMAT_R32G8X24_TYPELESS
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT
	DXGI_FORMAT_R10G10B10A2_TYPELESS
	DXGI_FORMAT_R10G10B10A2_UNORM
	DXGI_FORMAT_R10G10B10A2_UINT
	DXGI_FORMAT_R11G11B10_FLOAT
	DXGI_FORMAT_D32_FLOAT
	DXGI_FORMAT_R24G8_TYPELESS
	DXGI_FORMAT_D24_UNORM_S8_UINT
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	DXGI_FORMAT_X24_TYPELESS_G8_UINT
	DXGI_FORMAT_D16_UNORM
	DXGI_FORMAT_R8_TYPELESS
	DXGI_FORMAT_R8_UNORM
	DXGI_FORMAT_R8_UINT
	DXGI_FORMAT_R8_SNORM
	DXGI_FORMAT_R8_SINT
	DXGI_FORMAT_A8_UNORM
	DXGI_FORMAT_R1_UNORM
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP
	DXGI_FORMAT_R8G8_B8G8_UNORM
	DXGI_FORMAT_G8R8_G8B8_UNORM
	DXGI_FORMAT_BC1_TYPELESS
	DXGI_FORMAT_BC1_UNORM
	DXGI_FORMAT_BC1_UNORM_SRGB
	DXGI_FORMAT_BC2_TYPELESS
	DXGI_FORMAT_BC2_UNORM
	DXGI_FORMAT_BC2_UNORM_SRGB
	DXGI_FORMAT_BC3_TYPELESS
	DXGI_FORMAT_BC3_UNORM
	DXGI_FORMAT_BC3_UNORM_SRGB
	DXGI_FORMAT_BC4_TYPELESS
	DXGI_FORMAT_BC4_UNORM
	DXGI_FORMAT_BC4_SNORM
	DXGI_FORMAT_BC5_TYPELESS
	DXGI_FORMAT_BC5_UNORM
	DXGI_FORMAT_BC5_SNORM
	DXGI_FORMAT_B5G6R5_UNORM
	DXGI_FORMAT_B5G5R5A1_UNORM
	DXGI_FORMAT_B8G8R8A8_UNORM
	DXGI_FORMAT_B8G8R8X8_UNORM
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM
	DXGI_FORMAT_B8G8R8A8_TYPELESS
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	DXGI_FORMAT_B8G8R8X8_TYPELESS
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB
	DXGI_FORMAT_BC6H_TYPELESS
	DXGI_FORMAT_BC6H_UF16
	DXGI_FORMAT_BC6H_SF16
	DXGI_FORMAT_BC7_TYPELESS
	DXGI_FORMAT_BC7_UNORM
	DXGI_FORMAT_BC7_UNORM_SRGB
	DXGI_FORMAT_AYUV
	DXGI_FORMAT_Y410
	DXGI_FORMAT_Y416
	DXGI_FORMAT_NV12
	DXGI_FORMAT_P010
	DXGI_FORMAT_P016
	DXGI_FORMAT_420_OPAQUE
	DXGI_FORMAT_YUY2
	DXGI_FORMAT_Y210
	DXGI_FORMAT_Y216
	DXGI_FORMAT_NV11
	DXGI_FORMAT_AI44
	DXGI_FORMAT_IA44
	DXGI_FORMAT_P8
	DXGI_FORMAT_A8P8
	DXGI_FORMAT_B4G4R4A4_UNORM

	DXGI_FORMAT_P208
	DXGI_FORMAT_V208
	DXGI_FORMAT_V408
	*/
	}
	return DXGI_FORMAT_UNKNOWN;
}

Format D3D12::Convert(DXGI_FORMAT pf)
{
	switch (pf)
	{
	case DXGI_FORMAT_UNKNOWN:				return Format::eNone;

	case DXGI_FORMAT_R8_TYPELESS:			return Format::eR8;
	case DXGI_FORMAT_R8_UINT:				return Format::eR8u;
	case DXGI_FORMAT_R8_SINT:				return Format::eR8s;
	case DXGI_FORMAT_R8_UNORM:				return Format::eR8un;
	case DXGI_FORMAT_R8_SNORM:				return Format::eR8sn;

	case DXGI_FORMAT_R16_TYPELESS:			return Format::eR16;
	case DXGI_FORMAT_R16_UINT:				return Format::eR16u;
	case DXGI_FORMAT_R16_SINT:				return Format::eR16s;
	case DXGI_FORMAT_R16_UNORM:				return Format::eR16un;
	case DXGI_FORMAT_R16_SNORM:				return Format::eR16sn;
	case DXGI_FORMAT_R16_FLOAT:				return Format::eR16f;

	case DXGI_FORMAT_R32_TYPELESS:			return Format::eR32;
	case DXGI_FORMAT_R32_UINT:				return Format::eR32u;
	case DXGI_FORMAT_R32_SINT:				return Format::eR32s;
	case DXGI_FORMAT_R32_FLOAT:				return Format::eR32f;

	case DXGI_FORMAT_R8G8_TYPELESS:			return Format::eRG8;
	case DXGI_FORMAT_R8G8_UINT:				return Format::eRG8u;
	case DXGI_FORMAT_R8G8_SINT:				return Format::eRG8s;
	case DXGI_FORMAT_R8G8_UNORM:			return Format::eRG8un;
	case DXGI_FORMAT_R8G8_SNORM:			return Format::eRG8sn;

	case DXGI_FORMAT_R16G16_TYPELESS:		return Format::eRG16;
	case DXGI_FORMAT_R16G16_UINT:			return Format::eRG16u;
	case DXGI_FORMAT_R16G16_SINT:			return Format::eRG16s;
	case DXGI_FORMAT_R16G16_UNORM:			return Format::eRG16un;
	case DXGI_FORMAT_R16G16_SNORM:			return Format::eRG16sn;
	case DXGI_FORMAT_R16G16_FLOAT:			return Format::eRG16f;

	case DXGI_FORMAT_R32G32_TYPELESS:		return Format::eRG32;
	case DXGI_FORMAT_R32G32_UINT:			return Format::eRG32u;
	case DXGI_FORMAT_R32G32_SINT:			return Format::eRG32s;
	case DXGI_FORMAT_R32G32_FLOAT:			return Format::eRG32f;

	case DXGI_FORMAT_R32G32B32_TYPELESS:	return Format::eRGB32;
	case DXGI_FORMAT_R32G32B32_UINT:		return Format::eRGB32u;
	case DXGI_FORMAT_R32G32B32_SINT:		return Format::eRGB32s;
	case DXGI_FORMAT_R32G32B32_FLOAT:		return Format::eRGB32f;

	case DXGI_FORMAT_R8G8B8A8_TYPELESS:		return Format::eRGBA8;
	case DXGI_FORMAT_R8G8B8A8_UINT:			return Format::eRGBA8u;
	case DXGI_FORMAT_R8G8B8A8_SINT:			return Format::eRGBA8s;
	case DXGI_FORMAT_R8G8B8A8_UNORM:		return Format::eRGBA8un;
	case DXGI_FORMAT_R8G8B8A8_SNORM:		return Format::eRGBA8sn;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:	return Format::eRGBA8uns;

	case DXGI_FORMAT_R16G16B16A16_TYPELESS:	return Format::eRGBA16;
	case DXGI_FORMAT_R16G16B16A16_UINT:		return Format::eRGBA16u;
	case DXGI_FORMAT_R16G16B16A16_SINT:		return Format::eRGBA16s;
	case DXGI_FORMAT_R16G16B16A16_UNORM:	return Format::eRGBA16un;
	case DXGI_FORMAT_R16G16B16A16_SNORM:	return Format::eRGBA16sn;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:	return Format::eRGBA16f;

	case DXGI_FORMAT_R32G32B32A32_TYPELESS:	return Format::eRGBA32;
	case DXGI_FORMAT_R32G32B32A32_UINT:		return Format::eRGBA32u;
	case DXGI_FORMAT_R32G32B32A32_SINT:		return Format::eRGBA32s;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:	return Format::eRGBA32f;

	case DXGI_FORMAT_D32_FLOAT:				return Format::eD32f;
	}
	CPF_ASSERT_ALWAYS;
	return Format::eNone;
}

DXGI_SWAP_EFFECT D3D12::Convert(SwapEffect swapEffect)
{
	switch (swapEffect)
	{
	case SwapEffect::eDiscard: return DXGI_SWAP_EFFECT_DISCARD;
	case SwapEffect::eSequential: return DXGI_SWAP_EFFECT_SEQUENTIAL;
	case SwapEffect::eFlipSequential: return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	case SwapEffect::eFlipDiscard: return DXGI_SWAP_EFFECT_FLIP_DISCARD;
	}
	CPF_ASSERT_ALWAYS;
	return DXGI_SWAP_EFFECT(-1);
}

ScanLineOrder D3D12::Convert(DXGI_MODE_SCANLINE_ORDER order)
{
	switch (order)
	{
	case DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:			return ScanLineOrder::eUnspecified;
	case DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:			return ScanLineOrder::eProgressive;
	case DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST:	return ScanLineOrder::eUpperFieldFirst;
	case DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST:	return ScanLineOrder::eLowerFieldFirst;
	}
	CPF_ASSERT_ALWAYS;
	return ScanLineOrder::eUnspecified;
}

ModeScaling D3D12::Convert(DXGI_MODE_SCALING scaling)
{
	switch (scaling)
	{
	case DXGI_MODE_SCALING_UNSPECIFIED:	return ModeScaling::eUnspecified;
	case DXGI_MODE_SCALING_CENTERED:	return ModeScaling::eCentered;
	case DXGI_MODE_SCALING_STRETCHED:	return ModeScaling::eStretched;
	}
	CPF_ASSERT_ALWAYS;
	return ModeScaling::eUnspecified;
}

UINT D3D12::ConvertEnumMode(uint32_t mode)
{
	UINT result = 0;
	result |= (mode & EnumMode::eInterlaced) ? DXGI_ENUM_MODES_INTERLACED : 0;
	result |= (mode & EnumMode::eScaling) ? DXGI_ENUM_MODES_SCALING : 0;
	result |= (mode & EnumMode::eStereo) ? DXGI_ENUM_MODES_STEREO : 0;
	result |= (mode & EnumMode::eDisabledStereo) ? DXGI_ENUM_MODES_DISABLED_STEREO : 0;
	return result;
}

bool D3D12::Convert(const ResourceBindingDesc& desc, ID3DBlob** result)
{
	// Eventually switch to the versioned signatures, for the moment go for compatibility.
#if 0
	CD3DX12_ROOT_PARAMETER1* parameters = new CD3DX12_ROOT_PARAMETER1[desc.GetParameters().size()];

	int32_t i = 0;
	for (const auto& param : desc.GetParameters())
	{
		switch (param.GetType())
		{
		case BindingType::eConstants:
			{
				const auto& cb = param.GetConstants();
				parameters[i++].InitAsConstants(cb.mCount, cb.mRegisterIndex, 0, D3D12_SHADER_VISIBILITY(cb.mVisibility));
			}
			break;
		case BindingType::eConstantBuffer:
			{
				const auto& cb = param.GetConstantBuffer();
				parameters[i++].InitAsConstantBufferView(
					cb.mRegisterIndex,
					0,
					D3D12_ROOT_DESCRIPTOR_FLAGS(cb.mFlags),
					D3D12_SHADER_VISIBILITY(cb.mVisibility));
			}
			break;
		default:
			CPF_ASSERT_ALWAYS;// Type not implemented.
		}
	}

	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC signature;
	signature.Init_1_1(UINT(desc.GetParameters().size()), parameters, 0, nullptr, rootSignatureFlags);

	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	if (SUCCEEDED(D3D12SerializeVersionedRootSignature(&signature, &signatureBlob, &errorBlob)))
	{
		if (errorBlob)
			errorBlob->Release();
		*result = signatureBlob;
		delete[] parameters;
		return true;
	}
	if (signatureBlob)
		signatureBlob->Release();
	*result = errorBlob;
	delete[] parameters;
	return false;
#else
	CD3DX12_ROOT_PARAMETER* parameters = new CD3DX12_ROOT_PARAMETER[desc.GetParameters().size()];

	int32_t i = 0;
	for (const auto& param : desc.GetParameters())
	{
		switch (param.GetType())
		{
		case BindingType::eConstants:
		{
			const auto& cb = param.GetConstants();
			parameters[i++].InitAsConstants(cb.mCount, cb.mRegisterIndex, 0, D3D12_SHADER_VISIBILITY(cb.mVisibility));
		}
		break;
		case BindingType::eConstantBuffer:
		{
			const auto& cb = param.GetConstantBuffer();
			parameters[i++].InitAsConstantBufferView(
				cb.mRegisterIndex,
				0,
				D3D12_SHADER_VISIBILITY(cb.mVisibility));
		}
		break;
		default:
			CPF_ASSERT_ALWAYS;// Type not implemented.
		}
	}

	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	CD3DX12_ROOT_SIGNATURE_DESC signature;
	signature.Init(UINT(desc.GetParameters().size()), parameters, 0, nullptr, rootSignatureFlags);

	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	if (SUCCEEDED(D3D12SerializeRootSignature(&signature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob)))
	{
		if (errorBlob)
			errorBlob->Release();
		*result = signatureBlob;
		delete[] parameters;
		return true;
	}
	if (signatureBlob)
		signatureBlob->Release();
	*result = errorBlob;
	delete[] parameters;
	return false;
#endif
}
