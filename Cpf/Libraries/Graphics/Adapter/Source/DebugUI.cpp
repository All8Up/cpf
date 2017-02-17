//////////////////////////////////////////////////////////////////////////
#include "Graphics/DebugUI.hpp"
#include "Graphics/BinaryBlob.hpp"
#include "Graphics/Interfaces/iDevice.hpp"
#include "Graphics/Interfaces/iShader.hpp"
#include "Graphics/Interfaces/iSampler.hpp"
#include "Graphics/Interfaces/iPipeline.hpp"
#include "Graphics/Descriptors/PipelineStateDesc.hpp"
#include "Graphics/Descriptors/ResourceBindingDesc.hpp"
#include "imgui/imgui.h"
#include "IO/Stream.hpp"
#include "Resources/ID.hpp"
#include "Resources/Locator.hpp"

using namespace Cpf;
using namespace Graphics;


DebugUI::DebugUI()
	: mpDevice(nullptr)
	, mpLocator(nullptr)
{

}

DebugUI::~DebugUI()
{}

bool DebugUI::Initialize(iDevice* device, Resources::Locator* locator)
{
	CPF_ASSERT(device != nullptr);
	CPF_ASSERT(locator != nullptr);
	mpDevice = device;
	mpLocator = locator;

	// Load the shaders.
	// TODO: Consider moving the debug UI out so we don't need a dependency on resources.
	// TODO: The decision will have to wait till later though, have to know how this ends up dealing with cross api shaders first.
	{
		IntrusivePtr<Platform::IO::Stream> vertexShaderHlsl(mpLocator->Open(RESOURCE_ID("shaders/", "ui_vs.hlsl")));
		IntrusivePtr<Platform::IO::Stream> pixelShaderHlsl(mpLocator->Open(RESOURCE_ID("shaders/", "ui_ps.hlsl")));

		if (vertexShaderHlsl && pixelShaderHlsl)
		{
			IntrusivePtr<BinaryBlob> vertexShaderByteCode;
			{
				auto vertexShaderSrc = ReadText(vertexShaderHlsl);
				mpDevice->CompileToByteCode("main", ShaderType::eVertex, vertexShaderSrc.size(), vertexShaderSrc.data(), vertexShaderByteCode.AsTypePP());
			}
			mpDevice->CreateShader(vertexShaderByteCode, mpVertexShader.AsTypePP());

			IntrusivePtr<BinaryBlob> pixelShaderByteCode;
			{
				auto pixelShaderSrc = ReadText(pixelShaderHlsl);
				mpDevice->CompileToByteCode("main", ShaderType::ePixel, pixelShaderSrc.size(), pixelShaderSrc.data(), pixelShaderByteCode.AsTypePP());
			}
			mpDevice->CreateShader(pixelShaderByteCode, mpPixelShader.AsTypePP());
		}
	}
	if (!mpVertexShader || !mpPixelShader)
		return false;

	// Create the atlas sampler.
	SamplerDesc samplerDesc
	{
		FilterMode::eLinear,
		FilterMode::eLinear,
		FilterMode::eLinear,
		WrapMode::eClamp,
		WrapMode::eClamp,
		WrapMode::eClamp,
		0.0f,
		0.0f,
		0.0f
	};
	mpDevice->CreateSampler(&samplerDesc, mpSampler.AsTypePP());

	// Create the pipeline.
	{
		PipelineStateDesc pipelineDesc = PipelineStateDesc::Build()
			.VertexShader(mpVertexShader)
			.PixelShader(mpPixelShader)
			.Topology(TopologyType::eTriangle)

			.Rasterizer(RasterizerStateDesc::Build()
				.CullMode(CullMode::eNone)
				.WindingOrder(WindingOrder::eClockwise)
				.DepthClipping(false)
			)
			.DepthStencil(DepthStencilStateDesc::Build()
				.DepthTest(false)
				.DepthWriteMask(DepthWriteMask::eZero)
			)
			.InputLayout(
			{
				ElementDesc("POSITION", Format::eRG32f),
				ElementDesc("COLOR", Format::eRGBA8u),
				ElementDesc("TEXCOORD", Format::eRG32f)
			})
			.TargetBlend(0, RenderTargetBlendStateDesc::Build()
				.Blending(true)
				.Op(BlendOp::eAdd)
				.OpAlpha(BlendOp::eAdd)
				.Src(BlendFunc::eSrcAlpha)
				.SrcAlpha(BlendFunc::eInvSrcAlpha)
				.Dst(BlendFunc::eOne)
				.DstAlpha(BlendFunc::eZero)
			)
			.RenderTargets({ Format::eRGBA8un })
			;

		// Create the binding.
		ResourceBindingDesc bindingState({
			ParamConstantBuffer(0, ParamVisibility::eVertex),
			ParamSampler(0),
			ParamTexture(0)
		});
		mpDevice->CreateResourceBinding(&bindingState, mpResourceBinding.AsTypePP());

		// Create the actual pipeline object.
		mpDevice->CreatePipeline(&pipelineDesc, mpResourceBinding, mpPipeline.AsTypePP());
	}
	if (!mpResourceBinding || !mpPipeline)
		return false;

	// Build the imgui font atlas.
	{
		ImGuiIO& io = ImGui::GetIO();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
		if (pixels == nullptr)
			return false;

		ImageDesc atlasDesc;
		atlasDesc.mFormat = Format::eRGBA8u;
		atlasDesc.mWidth = width;
		atlasDesc.mHeight = height;
		atlasDesc.mDepth = 1;
		atlasDesc.mMipLevels = 1;
		atlasDesc.mSamples = SampleDesc(1, 0);
		atlasDesc.mFlags = 0;
		mpDevice->CreateImage2D(&atlasDesc, pixels, mpUIAtlas.AsTypePP());
	}

	return false;
}
