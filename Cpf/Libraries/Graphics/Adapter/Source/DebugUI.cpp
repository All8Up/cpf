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
#include "Math/Matrix44v.hpp"
#include "Math/Constants.hpp"

using namespace Cpf;
using namespace Graphics;


DebugUI::DebugUI()
	: mpDevice(nullptr)
	, mpLocator(nullptr)
{

}

DebugUI::~DebugUI()
{
}

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

	// Create the projection matrix constant buffer.
	mpDevice->CreateConstantBuffer(sizeof(Math::Matrix44fv), nullptr, mpProjectionMatrix.AsTypePP());

	// Create the atlas sampler.
	SamplerDesc samplerDesc
	{
		FilterMode::ePoint,
		FilterMode::ePoint,
		FilterMode::ePoint,
		WrapMode::eBorder,
		WrapMode::eBorder,
		WrapMode::eBorder,
		0.0f,
		Math::kFloatMax,
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
				ElementDesc("TEXCOORD", Format::eRG32f),
				ElementDesc("COLOR", Format::eRGBA8un)
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
			.DepthStencilFormat(Format::eD32f)
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
		atlasDesc.mFormat = Format::eRGBA8un;
		atlasDesc.mWidth = width;
		atlasDesc.mHeight = height;
		atlasDesc.mDepth = 1;
		atlasDesc.mMipLevels = 1;
		atlasDesc.mSamples = SampleDesc(1, 0);
		atlasDesc.mFlags = 0;
		mpDevice->CreateImage2D(&atlasDesc, pixels, mpUIAtlas.AsTypePP());
	}
	if (!mpUIAtlas)
		return false;

	// Create large buffers.
	mpDevice->CreateVertexBuffer(BufferUsage::eDynamic, 1024*200, sizeof(ImDrawVert), nullptr, mpVertexBuffer.AsTypePP());
	mpDevice->CreateIndexBuffer(Format::eR32u, BufferUsage::eDynamic, 1024*50, nullptr, mpIndexBuffer.AsTypePP());

	return true;
}

void DebugUI::Shutdown()
{
	mpVertexShader.Assign(nullptr);
	mpPixelShader.Assign(nullptr);
	mpResourceBinding.Assign(nullptr);
	mpPipeline.Assign(nullptr);
	mpUIAtlas.Assign(nullptr);
	mpSampler.Assign(nullptr);
	mpVertexBuffer.Assign(nullptr);
	mpIndexBuffer.Assign(nullptr);
	mpProjectionMatrix.Assign(nullptr);
}

void DebugUI::BeginFrame(iCommandBuffer* commands, float deltaTime)
{
	(void)commands;
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2(float(mWidth), float(mHeight));
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	io.DeltaTime = deltaTime;

	Math::Matrix44fv projection = Math::Matrix44fv(
		{ 2.0f / io.DisplaySize.x,	0.0f,						 0.0f,	0.0f },
		{ 0.0f,						2.0f / -io.DisplaySize.y,	 0.0f,	0.0f },
		{ 0.0f,						0.0f,						 0.5f,	0.0f },
		{-1.0f,						1.0f,						 0.5f,	1.0f }
	);
	mpProjectionMatrix->Update(0, sizeof(Math::Matrix44fv), &projection);

	// Start the frame
	ImGui::NewFrame();

	// TODO: Testing...
	ImGui::ShowTestWindow();
}

void DebugUI::EndFrame(iCommandBuffer* commands)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Render();
	ImDrawData* drawData = ImGui::GetDrawData();

	Viewport viewport{
		0.0f, 0.0f,
		float(mWidth), float(mHeight),
		0.0f, 1.0f
	};
	commands->SetViewports(1, &viewport);

	drawData->ScaleClipRects(io.DisplayFramebufferScale);

	commands->SetResourceBinding(mpResourceBinding);
	commands->SetPipeline(mpPipeline);
	commands->SetVertexBuffers(0, 1, mpVertexBuffer.AsTypePP());
	commands->SetIndexBuffer(mpIndexBuffer);
	commands->SetTopology(PrimitiveTopology::eTriangleList);
	commands->SetConstantBuffer(0, mpProjectionMatrix);
	commands->TempPorting(mpUIAtlas, mpSampler);
//	commands->SetTexture(0, mpUIAtlas);
//	commands->SetSampler(0, mpSampler);

	for (int n = 0; n < drawData->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = drawData->CmdLists[n];
		size_t idx_buffer_offset = 0;

		ImDrawVert* vertices = nullptr;
		reinterpret_cast<ImDrawVert*>(mpVertexBuffer->Map(0, cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), reinterpret_cast<void**>(&vertices)));
		::memcpy(vertices, &cmd_list->VtxBuffer.front(), cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
		mpVertexBuffer->Unmap();

		ImDrawIdx* indices = nullptr;
		reinterpret_cast<ImDrawIdx*>(mpIndexBuffer->Map(0, cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), reinterpret_cast<void**>(&indices)));
		::memcpy(indices, &cmd_list->IdxBuffer.front(), cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
		mpIndexBuffer->Unmap();

		for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
		{
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				Math::Rectanglei scissor
				{
					(int)pcmd->ClipRect.x,
					(int)(pcmd->ClipRect.x + pcmd->ClipRect.z - pcmd->ClipRect.x),
					(int)(io.DisplaySize.y - pcmd->ClipRect.w),
					(int)(io.DisplaySize.y - pcmd->ClipRect.w + pcmd->ClipRect.w - pcmd->ClipRect.y)
				};
				commands->SetScissorRects(1, &scissor);
				commands->DrawIndexedInstanced(pcmd->ElemCount, 1, idx_buffer_offset, 0, 0);
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}
}

void DebugUI::SetWindowSize(int32_t width, int32_t height)
{
	mWidth = width;
	mHeight = height;
}
