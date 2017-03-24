//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Pipeline.hpp"
#include "Adapter/D3D12/Shader.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/Descriptors/PipelineStateDesc.hpp"
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;


Pipeline::Pipeline(Device* device, const Graphics::PipelineStateDesc* state, const ResourceBinding* resourceBinding CPF_GFX_DEBUG_PARAM_DEF)
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC stateDesc;
	stateDesc.pRootSignature = nullptr;
	stateDesc.VS = state->GetVertexShader() ? static_cast<Shader*>(state->GetVertexShader())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.PS = state->GetPixelShader() ? static_cast<Shader*>(state->GetPixelShader())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.DS = state->GetDomainShader() ? static_cast<Shader*>(state->GetDomainShader())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.HS = state->GetHullShader() ? static_cast<Shader*>(state->GetHullShader())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.GS = state->GetGeometryShader() ? static_cast<Shader*>(state->GetGeometryShader())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };

	stateDesc.StreamOutput = {nullptr, 0, nullptr, 0, 0};
	stateDesc.BlendState = { state->GetAlphaToCoverage(), state->GetIndependentBlend(), {0} };
	for (int i = 0; i < 8; ++i)
	{
		const auto& target = state->GetBlendState().mRenderTarget[i];
		stateDesc.BlendState.RenderTarget[i].BlendEnable = target.mBlending ? TRUE : FALSE;
		stateDesc.BlendState.RenderTarget[i].LogicOpEnable = target.mLogicOps ? TRUE : FALSE;
		stateDesc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND(target.mSrcBlend);
		stateDesc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND(target.mDstBlend);
		stateDesc.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP(target.mBlendOp);
		stateDesc.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND(target.mSrcBlendAlpha);
		stateDesc.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND(target.mDstBlendAlpha);
		stateDesc.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP(target.mBlendOpAlpha);
		stateDesc.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP(target.mLogicOp);
		stateDesc.BlendState.RenderTarget[i].RenderTargetWriteMask = target.mWriteMask;
	}

	stateDesc.SampleMask = state->GetSampleMask();

	{
		const auto& rasterization = state->GetRasterizationState();
		stateDesc.RasterizerState =
		{
			D3D12_FILL_MODE(rasterization.GetFillMode()),
			D3D12_CULL_MODE(rasterization.GetCullMode()),
			rasterization.GetWindingOrder() == Graphics::WindingOrder::eCounterClockwise ? TRUE : FALSE,
			rasterization.GetDepthBias(),
			rasterization.GetDepthBiasClamp(),
			rasterization.GetSlopedScaledDepthBias(),
			rasterization.GetDepthClipping() ? TRUE : FALSE,
			rasterization.GetMultisampling() ? TRUE : FALSE,
			rasterization.GetAALines() ? TRUE : FALSE,
			UINT(rasterization.GetForcedSampleCount()),
			D3D12_CONSERVATIVE_RASTERIZATION_MODE(rasterization.GetConservativeRasterization())
		};
	}

	{
		const auto& depthStencil = state->GetDepthStencilState();
		stateDesc.DepthStencilState =
		{
			depthStencil.GetDepthTest() ? TRUE : FALSE,
			D3D12_DEPTH_WRITE_MASK(depthStencil.GetDepthWriteMask()),
			D3D12_COMPARISON_FUNC(depthStencil.GetComparison()),
			depthStencil.GetStenciling() ? TRUE : FALSE,
			depthStencil.GetStencilReadMask(),
			depthStencil.GetStencilWriteMask(),
			// TODO: The stencil data is wrong in the pipeline states.
			{
				D3D12_STENCIL_OP_INCR,
				D3D12_STENCIL_OP_INCR,
				D3D12_STENCIL_OP_INCR,
				D3D12_COMPARISON_FUNC_ALWAYS
			},
			{
				D3D12_STENCIL_OP_INCR,
				D3D12_STENCIL_OP_INCR,
				D3D12_STENCIL_OP_INCR,
				D3D12_COMPARISON_FUNC_ALWAYS
			}
		};
	}

	const auto& inputLayout = state->GetInputLayoutState();
	D3D12_INPUT_ELEMENT_DESC* inputDescs = new D3D12_INPUT_ELEMENT_DESC[inputLayout.GetCount()];
	for (int i = 0; i < inputLayout.GetCount(); ++i)
	{
		const auto desc = inputLayout.GetElementDescs()[i];
		auto& out = inputDescs[i];
		out.SemanticName = desc.GetSemantic();
		out.SemanticIndex = desc.GetIndex();
		out.Format = Convert(desc.GetFormat());
		out.InputSlot = desc.GetSlot();
		out.AlignedByteOffset = desc.GetOffset();
		out.InputSlotClass = D3D12_INPUT_CLASSIFICATION(desc.GetClassification());
		out.InstanceDataStepRate = desc.GetStepping();
	}
	stateDesc.InputLayout = D3D12_INPUT_LAYOUT_DESC
	{
		inputDescs,
		UINT(inputLayout.GetCount())
	};

	stateDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE(state->GetIndexStripCut());
	stateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE(state->GetTopology());
	stateDesc.NumRenderTargets = state->GetRenderTargetCount();
	for (int i = 0; i < 8; ++i)
		stateDesc.RTVFormats[i] = Convert(state->GetRenderTargetFormat(i));
	stateDesc.DSVFormat = Convert(state->GetDepthStencilFormat());
	stateDesc.SampleDesc = { UINT(state->GetSampleState().mCount), UINT(state->GetSampleState().mQuality) };
	stateDesc.NodeMask = 1;
	stateDesc.CachedPSO = {nullptr, 0};
	stateDesc.Flags = D3D12_PIPELINE_STATE_FLAGS(0);

	//
	stateDesc.pRootSignature = resourceBinding->GetSignature();

	//////////////////////////////////////////////////////////////////////////
	if (SUCCEEDED(device->GetD3DDevice()->CreateGraphicsPipelineState(&stateDesc, IID_PPV_ARGS(mpPipelineState.AsTypePP()))))
	{
	}

	//////////////////////////////////////////////////////////////////////////
	delete[] inputDescs;

#ifdef CPF_GFX_TRACKING
	std::wstringstream str;
	str << dbgFilename << " : " << dbgLineNumber;
	mpPipelineState->SetName(str.str().c_str());
#endif

	CPF_LOG(D3D12, Info) << "Created pipeline: " << intptr_t(this) << " - " << intptr_t(mpPipelineState.Ptr());
}

Pipeline::~Pipeline()
{
	CPF_LOG(D3D12, Info) << "Destroyed pipeline: " << intptr_t(this) << " - " << intptr_t(mpPipelineState.Ptr());
}
