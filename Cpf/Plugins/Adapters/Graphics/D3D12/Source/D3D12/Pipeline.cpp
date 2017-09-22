//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Pipeline.hpp"
#include "Adapter/D3D12/Shader.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/PipelineStateDesc.hpp"
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Adapter;
using namespace D3D12;


Pipeline::Pipeline(Device* device, const Graphics::PipelineStateDesc* state, const ResourceBinding* resourceBinding)
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC stateDesc;
	stateDesc.pRootSignature = nullptr;
	stateDesc.VS = state->mpVertex ? static_cast<Shader*>(state->mpVertex.Ptr())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.PS = state->mpPixel ? static_cast<Shader*>(state->mpPixel.Ptr())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.DS = state->mpDomain ? static_cast<Shader*>(state->mpDomain.Ptr())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.HS = state->mpHull ? static_cast<Shader*>(state->mpHull.Ptr())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };
	stateDesc.GS = state->mpGeometry ? static_cast<Shader*>(state->mpGeometry.Ptr())->GetByteCode() : D3D12_SHADER_BYTECODE{ nullptr, 0 };

	stateDesc.StreamOutput = {nullptr, 0, nullptr, 0, 0};
	stateDesc.BlendState = { state->mBlendState.mAlphaToCoverage, state->mBlendState.mIndependentBlend, {0} };
	for (int i = 0; i < 8; ++i)
	{
		const auto& target = state->mBlendState.mRenderTarget[i];
		stateDesc.BlendState.RenderTarget[i].BlendEnable = target.mBlending ? TRUE : FALSE;
		stateDesc.BlendState.RenderTarget[i].LogicOpEnable = target.mLogicOps ? TRUE : FALSE;
		stateDesc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND(target.mSrcBlend);
		stateDesc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND(target.mDstBlend);
		stateDesc.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP(target.mBlendOp);
		stateDesc.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND(target.mSrcBlendAlpha);
		stateDesc.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND(target.mDstBlendAlpha);
		stateDesc.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP(target.mBlendOpAlpha);
		stateDesc.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP(target.mLogicOp);
		stateDesc.BlendState.RenderTarget[i].RenderTargetWriteMask = UINT8(target.mWriteMask);
	}

	stateDesc.SampleMask = state->mSampleMask;

	{
		const auto& rasterization = state->mRasterizerState;
		stateDesc.RasterizerState =
		{
			D3D12_FILL_MODE(rasterization.mFillMode),
			D3D12_CULL_MODE(rasterization.mCullMode),
			rasterization.mWindingOrder == Graphics::WindingOrder::eCounterClockwise ? TRUE : FALSE,
			rasterization.mDepthBias,
			rasterization.mDepthBiasClamp,
			rasterization.mSlopeScaledDepthBias,
			rasterization.mDepthClipping ? TRUE : FALSE,
			rasterization.mMultisampling ? TRUE : FALSE,
			rasterization.mAALines ? TRUE : FALSE,
			UINT(rasterization.mForcedSampleCount),
			D3D12_CONSERVATIVE_RASTERIZATION_MODE(rasterization.mConservativeRasterization)
		};
	}

	{
		const auto& depthStencil = state->mDepthStencil;
		stateDesc.DepthStencilState =
		{
			depthStencil.mDepthTest ? TRUE : FALSE,
			D3D12_DEPTH_WRITE_MASK(depthStencil.mDepthWriteMask),
			D3D12_COMPARISON_FUNC(depthStencil.mComparisonFunc),
			depthStencil.mStencilEnable ? TRUE : FALSE,
			depthStencil.mStencilReadMask,
			depthStencil.mStencilWriteMask,
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

	const auto& inputLayout = state->mInputLayout;
	D3D12_INPUT_ELEMENT_DESC* inputDescs = new D3D12_INPUT_ELEMENT_DESC[inputLayout.mCount];
	for (int i = 0; i < inputLayout.mCount; ++i)
	{
		const auto desc = inputLayout.mpElements[i];
		auto& out = inputDescs[i];
		out.SemanticName = desc.mpSemantic;
		out.SemanticIndex = desc.mIndex;
		out.Format = Convert(desc.mFormat);
		out.InputSlot = desc.mSlot;
		out.AlignedByteOffset = desc.mOffset;
		out.InputSlotClass = D3D12_INPUT_CLASSIFICATION(desc.mClass);
		out.InstanceDataStepRate = desc.mInstanceStepping;
	}
	stateDesc.InputLayout = D3D12_INPUT_LAYOUT_DESC
	{
		inputDescs,
		UINT(inputLayout.mCount)
	};

	stateDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE(state->mIndexStripCut);
	stateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE(state->mTopology);
	stateDesc.NumRenderTargets = state->mRenderTargetCount;
	for (int i = 0; i < 8; ++i)
		stateDesc.RTVFormats[i] = Convert(state->mRenderTargetFormats[i]);
	stateDesc.DSVFormat = Convert(state->mDepthStencilFormat);
	stateDesc.SampleDesc = { UINT(state->mSampleState.mCount), UINT(state->mSampleState.mQuality) };
	stateDesc.NodeMask = 1;
	stateDesc.CachedPSO = {nullptr, 0};
	stateDesc.Flags = D3D12_PIPELINE_STATE_FLAGS(0);

	//
	stateDesc.pRootSignature = resourceBinding->GetSignature();

	//////////////////////////////////////////////////////////////////////////
	if (FAILED(device->GetD3DDevice()->CreateGraphicsPipelineState(&stateDesc, IID_PPV_ARGS(mpPipelineState.AsTypePP()))))
	{
		delete[] inputDescs;
		CPF_LOG(D3D12, Info) << "Create pipeline failure!";
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	delete[] inputDescs;

	CPF_LOG(D3D12, Info) << "Created pipeline: " << intptr_t(this) << " - " << intptr_t(mpPipelineState.Ptr());
}

Pipeline::~Pipeline()
{
	CPF_LOG(D3D12, Info) << "Destroyed pipeline: " << intptr_t(this) << " - " << intptr_t(mpPipelineState.Ptr());
}

GOM::Result CPF_STDCALL Pipeline::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iPipeline::kIID.GetID():
			*outIface = static_cast<iPipeline*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
