//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/Device.hpp"
#include "Driver/D3D12/Adapter.hpp"
#include "Driver/D3D12/Instance.hpp"
#include "Driver/D3D12/CommandPool.hpp"
#include "Driver/D3D12/CommandBuffer.hpp"
#include "Driver/D3D12/Fence.hpp"
#include "Driver/D3D12/SwapChain.hpp"
#include "Driver/D3D12/Image.hpp"
#include "Driver/D3D12/ImageView.hpp"
#include "Driver/D3D12/Shader.hpp"
#include "Driver/D3D12/Pipeline.hpp"
#include "Driver/D3D12/ResourceBinding.hpp"
#include "Driver/D3D12/Resource.hpp"
#include "Driver/D3D12/ConstantBuffer.hpp"
#include "Driver/D3D12/IndexBuffer.hpp"
#include "Driver/D3D12/VertexBuffer.hpp"
#include "Driver/D3D12/Sampler.hpp"
#include "Driver/D3D12/Blob.hpp"
#include "Driver/D3D12/RenderPass.hpp"
#include "Driver/D3D12/FrameBuffer.hpp"
#include "Driver/D3D12/Plugin.hpp"

#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Std/String.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;


Device::Device(Plugin::iRegistry*, GOM::iUnknown*)
{
}

Device::~Device()
{
	Shutdown();
	CPF_LOG(D3D12, Info) << "Destroyed device: " << intptr_t(this) << " - " << intptr_t(mpDevice.Ptr()) << " - " << intptr_t(mpQueue.Ptr());
}

GOM::Result Device::Initialize(Plugin::iRegistry* regy, Graphics::iAdapter* adapter)
{
	mpRegistry = IntrusivePtr<Plugin::iRegistry>(regy);

#ifdef CPF_DEBUG
	ID3D12Debug* debugController = nullptr;
	if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		return GOM::kError;
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
        HRESULT result = D3D12CreateDevice(d3dAdapter->GetD3DAdapter(), highestLevel, IID_PPV_ARGS(&d3dDevice));
        if (SUCCEEDED(result))
        {
            mpDevice.Adopt(d3dDevice);
        }
        else
            return GOM::kError;
	}

	//////////////////////////////////////////////////////////////////////////
	// Consider if this should be moved to another object.
	D3D12_COMMAND_QUEUE_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	mpDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(mpQueue.AsTypePP()));

	CPF_LOG(D3D12, Info) << "Created device: " << intptr_t(this) << " - " << intptr_t(mpDevice.Ptr()) << " - " << intptr_t(mpQueue.Ptr());
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Device::Initialize()
{
	if (
		mShaderResourceDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, kShaderResourceDescriptors) &&
		mSamplerDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, kSamplerDescriptors) &&
		mRenderTargetDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, kRenderTargetDescriptors) &&
		mDepthStencilDescriptors.Initialize(this, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, kDepthStencilDescriptors)
		)
		return GOM::kOK;
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::Shutdown()
{
	if (
		mShaderResourceDescriptors.Shutdown() &&
		mSamplerDescriptors.Shutdown() &&
		mRenderTargetDescriptors.Shutdown() &&
		mDepthStencilDescriptors.Shutdown()
		)
		return GOM::kOK;
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateSwapChain(Graphics::iInstance* instance, const Graphics::WindowData* winData, int32_t w, int32_t h, const Graphics::SwapChainDesc* desc, Graphics::iSwapChain** swapChain)
{
	Graphics::iSwapChain* result = new SwapChain(static_cast<Instance*>(instance), this, winData, w, h, desc);
	if (result)
	{
		*swapChain = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateCommandPool(Graphics::iCommandPool** pool)
{
	CommandPool* result = new CommandPool();
	if (pool)
	{
		if (GOM::Succeeded(result->Initialize(this)))
		{
			*pool = result;
			return GOM::kOK;
		}
		*pool = nullptr;
		return GOM::kInitializationFailure;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateCommandBuffer(Graphics::iCommandPool* pool, Graphics::CommandBufferType type, Graphics::iCommandBuffer** buffer)
{
	CommandBuffer* result = new CommandBuffer(nullptr, nullptr);
	if (result)
	{
		if (GOM::Succeeded(result->Initialize(this, type, pool)))
		{
			*buffer = result;
			return GOM::kOK;
		}
		*buffer = nullptr;
		return GOM::kInitializationFailure;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateFence(bool signaled, Graphics::iFence** fence)
{
	Fence* result = new Fence(this, signaled);
	if (result)
	{
		*fence = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateImage2D(Graphics::HeapType heap, const Graphics::ImageDesc* desc, const Graphics::ClearValue* clearValue, Graphics::iImage** image)
{
	Image* result = new Image(this, heap, clearValue, desc);
	if (result)
	{
		*image = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateShader(Graphics::iBlob* blob, Graphics::iShader** shader)
{
	IntrusivePtr<Shader> result(new Shader());
	if (result)
	{
		if (result->LoadFrom(this, blob))
		{
			*shader = result;
			result->AddRef();
			return GOM::kOK;
		}
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateResourceBinding(const Graphics::ResourceBindingDesc* resourceState, Graphics::iResourceBinding** binding)
{
	IntrusivePtr<ResourceBinding> resourceBinding(new ResourceBinding(this, resourceState));
	if (resourceBinding)
	{
		resourceBinding->AddRef();
		*binding = resourceBinding;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding* rb, Graphics::iPipeline** pipeline)
{
	IntrusivePtr<Pipeline> result(new Pipeline(this, desc, static_cast<const ResourceBinding*>(rb)));
	if (result)
	{
		result->AddRef();
		*pipeline = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource)
{
	IntrusivePtr<Resource> result(new Resource(this, desc));
	if (result)
	{
		result->AddRef();
		*resource = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** sampler)
{
	IntrusivePtr<Sampler> result(new Sampler(this, desc));
	if (result)
	{
		result->AddRef();
		*sampler = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** renderPass)
{
	if (mpRegistry == nullptr)
		return GOM::kNotInitialized;
	if (desc == nullptr)
		return GOM::kInvalidParameter;
	if (renderPass == nullptr)
		return GOM::kInvalidParameter;

	if (GOM::Succeeded(mpRegistry->Create(nullptr, kRenderPassCID, Graphics::iRenderPass::kIID, reinterpret_cast<void**>(renderPass))))
	{
		if (GOM::Succeeded(static_cast<RenderPass*>(*renderPass)->Initialize(desc)))
			return GOM::kOK;
		(*renderPass)->Release();
		*renderPass = nullptr;
		return GOM::kInitializationFailure;
	}

	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Device::CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer)
{
	if (mpRegistry == nullptr)
		return GOM::kNotInitialized;
	if (desc == nullptr)
		return GOM::kInvalidParameter;
	if (frameBuffer == nullptr)
		return GOM::kInvalidParameter;

	if (GOM::Succeeded(mpRegistry->Create(nullptr, kFrameBufferCID, Graphics::iFrameBuffer::kIID, reinterpret_cast<void**>(frameBuffer))))
	{
		if (GOM::Succeeded(static_cast<FrameBuffer*>(*frameBuffer)->Initialize(desc)))
			return GOM::kOK;
		(*frameBuffer)->Release();
		*frameBuffer = nullptr;
		return GOM::kInitializationFailure;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Device::CreateIndexBuffer(const Graphics::ResourceDesc* desc, Graphics::Format format, Graphics::iIndexBuffer** indexBuffer)
{
	IntrusivePtr<IndexBuffer> result(new IndexBuffer(this, desc, format));
	if (result)
	{
		*indexBuffer = result;
		result.Abandon();
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateVertexBuffer(const Graphics::ResourceDesc* desc, int32_t stride, Graphics::iVertexBuffer** vertexBuffer)
{
	IntrusivePtr<VertexBuffer> result(new VertexBuffer(this, desc, stride));
	if (result)
	{
		*vertexBuffer = result;
		result.Abandon();
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateConstantBuffer(const Graphics::ResourceDesc* desc, const void* initData, Graphics::iConstantBuffer** cbuf)
{
	IntrusivePtr<ConstantBuffer> result(new ConstantBuffer(this, desc, initData));
	if (result)
	{
		*cbuf = result;
		result.Abandon();
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateBlob(int64_t size, const void* data, Graphics::iBlob** blob)
{
	IntrusivePtr<Graphics::iBlob> result(new Blob(size, data));
	if (result)
	{
		*blob = result;
		result->AddRef();
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CompileToByteCode(const char* entryPoint, Graphics::ShaderType type, size_t size, const char* source, Graphics::iBlob** outBlob)
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
			entryPoint,
			shaderTypes[size_t(type)],
			compileFlags, // Flags1
			0, // Flags2
			blob.AsTypePP(),
			errorBlob.AsTypePP()
		)))
		{
			CreateBlob(blob->GetBufferSize(), blob->GetBufferPointer(), outBlob);
			return GOM::kOK;
		}
		if (errorBlob)
		{
			STD::String errors;
			errors.resize(errorBlob->GetBufferSize());
			::memcpy(&errors[0], errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
			CPF_LOG(D3D12, Error) << "Shader compile errors: " << errors;
		}
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::CreateDepthStencilView(Graphics::iImage* image, const Graphics::DepthStencilViewDesc* dsDesc, Graphics::iImageView** imageView)
{
	ImageView* result = new ImageView(this, static_cast<Image*>(image), dsDesc);
	if (result)
	{
		*imageView = result;
		return GOM::kOK;
	}
	return GOM::kError;
}

GOM::Result CPF_STDCALL Device::Signal(Graphics::iFence* fence)
{
	auto d3dFence = static_cast<Fence*>(fence);
	if (SUCCEEDED(mpQueue->Signal(d3dFence->GetD3DFence(), d3dFence->GetTarget())))
		return GOM::kOK;
	return GOM::kError;
}

void CPF_STDCALL Device::Submit(int32_t count, Graphics::iCommandBuffer* const * buffers)
{
	for (int i = 0; i < count; ++i)
		static_cast<CommandBuffer*>(buffers[i])->Submit(mpQueue);
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
