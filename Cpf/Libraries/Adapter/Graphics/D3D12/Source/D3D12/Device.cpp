//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/Adapter.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Adapter/D3D12/CommandPool.hpp"
#include "Adapter/D3D12/CommandBuffer.hpp"
#include "Adapter/D3D12/Fence.hpp"
#include "Adapter/D3D12/SwapChain.hpp"
#include "Adapter/D3D12/Image.hpp"
#include "Adapter/D3D12/Shader.hpp"
#include "Adapter/D3D12/Pipeline.hpp"
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Adapter/D3D12/Resource.hpp"
#include "Adapter/D3D12/ConstantBuffer.hpp"
#include "Adapter/D3D12/IndexBuffer.hpp"
#include "Adapter/D3D12/VertexBuffer.hpp"
#include "Adapter/D3D12/Sampler.hpp"
#include "Graphics/BinaryBlob.hpp"

#include "Adapter/D3D12/RenderPass.hpp"
#include "Adapter/D3D12/FrameBuffer.hpp"

#include "Adapter/D3D12/Plugin.hpp"
#include "Logging/Logging.hpp"
#include "String.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;


Device::Device()
{
}

Device::~Device()
{
	Shutdown();
	CPF_LOG(D3D12, Info) << "Destroyed device: " << intptr_t(this) << " - " << intptr_t(mpDevice.Ptr()) << " - " << intptr_t(mpQueue.Ptr());
}

COM::Result Device::Initialize(Graphics::iAdapter* adapter)
{
#ifdef CPF_DEBUG
	ID3D12Debug* debugController = nullptr;
	if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		return COM::kError;
	}
	debugController->EnableDebugLayer();
	debugController->Release();
#endif

	Adapter* d3dAdapter = static_cast<Adapter*>(adapter);

	const D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	const int levelCount = sizeof(levels) / sizeof(D3D_FEATURE_LEVEL);
	D3D_FEATURE_LEVEL highestLevel = D3D_FEATURE_LEVEL(0);

	for (int i = 0; i < levelCount; ++i)
	{
		if (SUCCEEDED(D3D12CreateDevice(d3dAdapter->GetD3DAdapter(), levels[i], _uuidof(ID3D12Device), nullptr)))
		{
			highestLevel = levels[i];
			break;
		}
	}

	if (highestLevel != D3D_FEATURE_LEVEL(0))
	{
		ID3D12Device* d3dDevice = nullptr;
		if (SUCCEEDED(D3D12CreateDevice(d3dAdapter->GetD3DAdapter(), highestLevel, IID_PPV_ARGS(&d3dDevice))))
		{
			mpDevice.Adopt(d3dDevice);
		}
	}


	D3D12_COMMAND_QUEUE_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	mpDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(mpQueue.AsTypePP()));

	CPF_LOG(D3D12, Info) << "Created device: " << intptr_t(this) << " - " << intptr_t(mpDevice.Ptr()) << " - " << intptr_t(mpQueue.Ptr());
	return COM::kOK;
}

COM::Result CPF_STDCALL Device::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iDevice::kIID.GetID():
			*outIface = static_cast<iDevice*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Device::Initialize()
{
	if (
		mShaderResourceDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, kShaderResourceDescriptors) &&
		mSamplerDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, kSamplerDescriptors) &&
		mRenderTargetDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, kRenderTargetDescriptors) &&
		mDepthStencilDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, kDepthStencilDescriptors)
		)
		return COM::kOK;
	return COM::kError;
}

COM::Result CPF_STDCALL Device::Shutdown()
{
	if (
		mShaderResourceDescriptors.Shutdown() &&
		mSamplerDescriptors.Shutdown() &&
		mRenderTargetDescriptors.Shutdown() &&
		mDepthStencilDescriptors.Shutdown()
		)
		return COM::kOK;
	return COM::kError;
}

void CPF_STDCALL Device::BeginFrame(Graphics::iCommandBuffer* cmds)
{
	CommandBuffer* commands = static_cast<CommandBuffer*>(cmds);

	for (auto& item : mUploadQueue)
	{
		switch (item.mType)
		{
		case WorkType::eUploadVertexBuffer:
			{
				const auto& work = item.UploadVertexBuffer;
				commands->mpCommandList->CopyResource(work.mpDestination, work.mpSource);
				CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(work.mpDestination, work.mDstStartState, work.mDstEndState);
				commands->mpCommandList->ResourceBarrier(1, &barrier);
				work.mpDestination->Release();
				mReleaseQueue.push_back(work.mpSource);
			}
			break;

		case WorkType::eUpdateSubResource:
			{
				auto& work = item.UpdateSubResource;

				CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(work.mpDestination, work.mDstStartState, work.mDstEndState);
				UpdateSubresources(commands->mpCommandList,
					work.mpDestination, work.mpSource,
					0, 0, 1, &work.mData);
				commands->mpCommandList->ResourceBarrier(1, &barrier);
				// TODO: Have to clean up the buffer and blob.
			}
			break;
		}
	}
	mUploadQueue.clear();
}

void CPF_STDCALL Device::EndFrame(Graphics::iCommandBuffer* cmds)
{
	(void)cmds;
//	CommandBuffer* commands = static_cast<CommandBuffer*>(cmds);
}

void CPF_STDCALL Device::Finalize()
{
	for (auto item : mReleaseQueue)
	{
		item->Release();
	}
	mReleaseQueue.clear();
}

COM::Result CPF_STDCALL Device::CreateSwapChain(Graphics::iInstance* instance, iWindow* window, const Graphics::SwapChainDesc* desc, Graphics::iSwapChain** swapChain)
{
	Graphics::iSwapChain* result = new SwapChain(static_cast<Instance*>(instance), this, window, desc);
	if (result)
	{
		*swapChain = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateCommandPool(Graphics::iCommandPool** pool)
{
	CommandPool* result = new CommandPool(this);
	if (pool)
	{
		*pool = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateCommandBuffer(Graphics::iCommandPool* pool, Graphics::iCommandBuffer** buffer)
{
	CommandBuffer* result = new CommandBuffer(this, pool);
	if (result)
	{
		*buffer = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateFence(int64_t initValue, Graphics::iFence** fence)
{
	Fence* result = new Fence(this, initValue);
	if (result)
	{
		*fence = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateImage2D(const Graphics::ImageDesc* desc, const void* initData, Graphics::iImage** image)
{
	Image* result = new Image(this, initData, desc);
	if (result)
	{
		*image = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateShader(Graphics::BinaryBlob* blob, Graphics::iShader** shader)
{
	IntrusivePtr<Shader> result(new Shader());
	if (result)
	{
		if (result->LoadFrom(this, blob))
		{
			*shader = result;
			result->AddRef();
			return COM::kOK;
		}
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateResourceBinding(const Graphics::ResourceBindingDesc* resourceState, Graphics::iResourceBinding** binding)
{
	IntrusivePtr<ResourceBinding> resourceBinding(new ResourceBinding(this, resourceState));
	if (resourceBinding)
	{
		resourceBinding->AddRef();
		*binding = resourceBinding;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding* rb, Graphics::iPipeline** pipeline)
{
	IntrusivePtr<Pipeline> result(new Pipeline(this, desc, static_cast<const ResourceBinding*>(rb)));
	if (result)
	{
		result->AddRef();
		*pipeline = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource)
{
	IntrusivePtr<Resource> result(new Resource(this, desc));
	if (result)
	{
		result->AddRef();
		*resource = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** sampler)
{
	IntrusivePtr<Sampler> result(new Sampler(this, desc));
	if (result)
	{
		result->AddRef();
		*sampler = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** renderPass)
{
	if (gContext.GetRegistry() == nullptr)
		return COM::kNotInitialized;
	if (desc == nullptr)
		return COM::kInvalidParameter;
	if (renderPass == nullptr)
		return COM::kInvalidParameter;

	if (COM::Succeeded(gContext.GetRegistry()->Create(nullptr, kRenderPassCID, Graphics::iRenderPass::kIID, reinterpret_cast<void**>(renderPass))))
	{
		if (COM::Succeeded(static_cast<RenderPass*>(*renderPass)->Initialize(desc)))
			return COM::kOK;
		(*renderPass)->Release();
		*renderPass = nullptr;
		return COM::kInitializationFailure;
	}

	return COM::kUnknownClass;
}

COM::Result CPF_STDCALL Device::CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer)
{
	if (gContext.GetRegistry() == nullptr)
		return COM::kNotInitialized;
	if (desc == nullptr)
		return COM::kInvalidParameter;
	if (frameBuffer == nullptr)
		return COM::kInvalidParameter;

	if (COM::Succeeded(gContext.GetRegistry()->Create(nullptr, kFrameBufferCID, Graphics::iFrameBuffer::kIID, reinterpret_cast<void**>(frameBuffer))))
	{
		if (COM::Succeeded(static_cast<FrameBuffer*>(*frameBuffer)->Initialize(desc)))
			return COM::kOK;
		(*frameBuffer)->Release();
		*frameBuffer = nullptr;
		return COM::kInitializationFailure;
	}
	return COM::kUnknownClass;
}

COM::Result CPF_STDCALL Device::CreateIndexBuffer(Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData, Graphics::iIndexBuffer** indexBuffer)
{
	IntrusivePtr<IndexBuffer> result(new IndexBuffer(this, format, usage, byteSize, initData));
	if (result)
	{
		*indexBuffer = result;
		result.Abandon();
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateVertexBuffer(Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, Graphics::iVertexBuffer** vertexBuffer)
{
	IntrusivePtr<VertexBuffer> result(new VertexBuffer(this, usage, byteSize, byteStride, initData));
	if (result)
	{
		*vertexBuffer = result;
		result.Abandon();
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateConstantBuffer(size_t bufferSize, const void* initData, Graphics::iConstantBuffer** cbuf)
{
	IntrusivePtr<ConstantBuffer> result(new ConstantBuffer(this, bufferSize, initData));
	if (result)
	{
		*cbuf = result;
		result.Abandon();
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CompileToByteCode(const String& entryPoint, Graphics::ShaderType type, size_t size, char* source, Graphics::BinaryBlob** outBlob)
{
	if (size > 0 && source)
	{
		static const char* shaderTypes[] =
		{
			"vs_5_0",
			"ps_5_0",
			"cs_5_0",
			"ds_5_0",
			"gs_5_0",
			"hs_5_0"
		};

		IntrusivePtr<ID3DBlob> blob;
		IntrusivePtr<ID3DBlob> errorBlob;
#if defined(CPF_DEBUG)
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif
		if (SUCCEEDED(D3DCompile(
			source,
			size,
			nullptr,
			nullptr,
			nullptr,
			entryPoint.c_str(),
			shaderTypes[size_t(type)],
			compileFlags, // Flags1
			0, // Flags2
			blob.AsTypePP(),
			errorBlob.AsTypePP()
		)))
		{
			Graphics::BinaryBlob::Create(blob->GetBufferSize(), blob->GetBufferPointer(), outBlob);
			return COM::kOK;
		}
		if (errorBlob)
		{
			String errors;
			errors.resize(errorBlob->GetBufferSize());
			::memcpy(&errors[0], errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
			CPF_LOG(D3D12, Error) << "Shader compile errors: " << errors;
		}
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::CreateDepthStencilView(Graphics::iImage* image, const Graphics::DepthStencilViewDesc* dsDesc, Graphics::iImageView** imageView)
{
	ImageView* result = new ImageView(this, static_cast<Image*>(image), dsDesc);
	if (result)
	{
		*imageView = result;
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL Device::Signal(Graphics::iFence* fence, int64_t value)
{
	auto d3dFence = static_cast<Fence*>(fence);
	if (SUCCEEDED(mpQueue->Signal(d3dFence->GetD3DFence(), UINT64(value))))
		return COM::kOK;
	return COM::kError;
}

void CPF_STDCALL Device::Submit(int32_t count, Graphics::iCommandBuffer** buffers)
{
	ID3D12CommandList* commands[64];
	for (int i = 0; i < count; ++i)
		commands[i] = static_cast<CommandBuffer*>(buffers[i])->GetCommandList();
	mpQueue->ExecuteCommandLists(count, commands);
}

DescriptorManager& CPF_STDCALL Device::GetShaderResourceDescriptors()
{
	return mShaderResourceDescriptors;
}

DescriptorManager& CPF_STDCALL Device::GetSamplerDescriptors()
{
	return mSamplerDescriptors;
}

DescriptorManager& CPF_STDCALL Device::GetRenderTargetViewDescriptors()
{
	return mRenderTargetDescriptors;
}

DescriptorManager& CPF_STDCALL Device::GetDepthStencilViewDescriptors()
{
	return mDepthStencilDescriptors;
}

void CPF_STDCALL Device::QueueUpload(ID3D12Resource* src, ID3D12Resource* dst, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState)
{
	WorkEntry entry;
	entry.mType = WorkType::eUploadVertexBuffer;
	entry.UploadVertexBuffer.mpSource = src;
	entry.UploadVertexBuffer.mpDestination = dst;
	entry.UploadVertexBuffer.mDstStartState = dstStartState;
	entry.UploadVertexBuffer.mDstEndState = dstEndState;
	mUploadQueue.push_back(entry);
}

void CPF_STDCALL Device::QueueUpdateSubResource(ID3D12Resource* src, ID3D12Resource* dst, D3D12_SUBRESOURCE_DATA& data, Graphics::BinaryBlob* blob, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState)
{
	WorkEntry entry;
	entry.mType = WorkType::eUpdateSubResource;
	entry.UpdateSubResource.mpSource = src;
	entry.UpdateSubResource.mpDestination = dst;
	entry.UpdateSubResource.mpBlob = blob;
	entry.UpdateSubResource.mData = data;
	entry.UpdateSubResource.mDstStartState = dstStartState;
	entry.UpdateSubResource.mDstEndState = dstEndState;
	mUploadQueue.push_back(entry);
}
