//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "IO/Stream.hpp"
#include "Graphics/WindingOrder.hpp"
#include "Graphics/CullMode.hpp"
#include "Graphics/Descriptors/RasterizerStateDesc.hpp"
#include "Graphics/TopologyType.hpp"
#include "Graphics/Descriptors/DepthStencilDesc.hpp"
#include "Graphics/Descriptors/InputLayoutDesc.hpp"
#include "Graphics/Descriptors/PipelineStateDesc.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix44v.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;


bool ExperimentalD3D12::_CreateResources()
{
	// Create shaders.
	{
		IO::Stream* vertexShaderHlsl = mpLocator->Open(RESOURCE_ID("shaders/", "basic_vs.hlsl"));
		IO::Stream* pixelShaderHlsl = mpLocator->Open(RESOURCE_ID("shaders/", "basic_ps.hlsl"));
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

	//////////////////////////////////////////////////////////////////////////
	// Create pipeline.
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
			.DepthTest(true)
			.DepthWriteMask(DepthWriteMask::eAll)
		)
		.InputLayout(
			{
				ElementDesc("POSITION", Format::eRGB32f),
				ElementDesc("COLOR", Format::eRGBA32f),
				ElementDesc("TRANSLATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
				ElementDesc("SCALE", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
				ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
				ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
				ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1)
			})
			.RenderTargets({ Format::eRGBA8un })
			.DepthStencilFormat(Format::eD32f)
			;

	//////////////////////////////////////////////////////////////////////////
	ResourceBindingDesc bindingState({
		ParamConstantBuffer(0, ParamVisibility::eVertex)
	});
	mpDevice->CreateResourceBinding(&bindingState, mpResourceBinding.AsTypePP());
	mpDevice->CreatePipeline(&pipelineDesc, mpResourceBinding, mpPipeline.AsTypePP());

	//////////////////////////////////////////////////////////////////////////
	struct PosColor
	{
		Vector3f mPosition;
		Vector4f mColor;
	};

	// Create the test data.
	const float triSize = 1.0f;
	PosColor vbData[] =
	{
		{ { +0.0f, +triSize, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { +triSize, -triSize, 0.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -triSize, -triSize, 0.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	uint32_t ibData[] =
	{
		0, 1, 2
	};

	// Create a vertex buffer.
	mpDevice->CreateVertexBuffer(BufferUsage::eImmutable, sizeof(vbData), sizeof(PosColor), vbData, mpVertexBuffer.AsTypePP());
	for (int i = 0; i < mBackBufferCount; ++i)
		mpDevice->CreateVertexBuffer(BufferUsage::eDynamic, sizeof(Instance) * kInstanceCount, sizeof(Instance), nullptr, mpInstanceBuffer[i].AsTypePP());

	// Create an index buffer.
	mpDevice->CreateIndexBuffer(Format::eR32u, BufferUsage::eDefault, sizeof(ibData), ibData, mpIndexBuffer.AsTypePP());

	// Create a the view projection constant buffer.
	struct CameraProj
	{
		Matrix44fv mView;
		Matrix44fv mInvView;
		Matrix44fv mProjection;
		float mNear;
		float mFar;
	} initCameraData
	{
		Transpose(Matrix44fv::LookAt(Vector3fv(0.0f, 180.0f, 400.0f), Vector3fv(0.0f), Vector3fv(0.0f, 1.0f, 0.0f))),
		Matrix44fv::Identity(),
		Transpose(Matrix44fv::PerspectiveLH(
			2.0f * mViewportSize * mAspectRatio,
			2.0f * mViewportSize,
			1.0f, 1000.0f,
			0.0f, 1.0f
		)),
		1.0f, 1000.0f
	};
	mpDevice->CreateConstantBuffer(sizeof(CameraProj), &initCameraData, mpViewProj.AsTypePP());

	return false;
}

void ExperimentalD3D12::_DestroyResources()
{
	// Guarantee shutdown order.
	mpVertexShader.Assign(nullptr);
	mpPixelShader.Assign(nullptr);
	mpVertexBuffer.Assign(nullptr);
	for (int i = 0; i < mBackBufferCount; ++i)
	{
		mpInstanceBuffer[i].Assign(nullptr);
		mpPreCommandBuffer[i].Assign(nullptr);
		mpPreCommandPool[i].Assign(nullptr);
		mpPostCommandBuffer[i].Assign(nullptr);
		mpPostCommandPool[i].Assign(nullptr);
	}
	mpIndexBuffer.Assign(nullptr);
	mpViewProj.Assign(nullptr);
	mpPipeline.Assign(nullptr);
	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();
	mpSwapChain.Assign(nullptr);
	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();
	mpFence.Assign(nullptr);
	mpResourceBinding.Assign(nullptr);

	mScheduler.Shutdown();
	for (auto& data : mWorkerData)
	{
		for (int i = 0; i < mBackBufferCount; ++i)
		{
			data.mpCommandPool[i].Assign(nullptr);
			data.mpCommandBuffer[i].Assign(nullptr);
		}
	}
	mpDevice.Assign(nullptr);
}
