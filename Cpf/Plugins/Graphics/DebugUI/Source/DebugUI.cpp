//////////////////////////////////////////////////////////////////////////
#include "DebugUI.hpp"
#include "Graphics/iBlob.hpp"
#include "Graphics/iDevice.hpp"
#include "Graphics/iSampler.hpp"
#include "Graphics/ImageDesc.hpp"
#include "Graphics/DepthStencilBuilder.hpp"
#include "Graphics/RasterizerStateBuilder.hpp"
#include "Graphics/PipelineStateBuilder.hpp"
#include "Graphics/ResourceBindingDesc.hpp"
#include "Graphics/Viewport.hpp"
#include "Graphics/ImageFlags.hpp"
#include "Graphics/FilterMode.hpp"
#include "Graphics/SamplerDesc.hpp"
#include "Graphics/ShaderType.hpp"
#include "Graphics/WrapMode.hpp"
#include "Graphics/ParamVisibility.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/PrimitiveTopology.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/HeapType.hpp"
#include "Graphics/ResourceType.hpp"
#include "Graphics/ResourceData.hpp"
#include "Graphics/ResourceDesc.hpp"
#include "Graphics/iCommandBuffer.hpp"
#include "Graphics/iFence.hpp"
#include "Graphics/iCommandPool.hpp"
#include "Graphics/iConstantBuffer.hpp"
#include "Graphics/Range.hpp"
#include "Graphics/iVertexBuffer.hpp"
#include "Graphics/iIndexBuffer.hpp"
#include "Graphics/iShader.hpp"
#include "Graphics/iPipeline.hpp"
#include "Graphics/BlendStateBuilder.hpp"
#include "Graphics/InputLayoutBuilder.hpp"

#include "Application/iWindow.hpp"
#include "Application/OSWindowData.hpp"
#include "imgui/imgui.h"
#include "IO/Stream.hpp"
#include "Resources/ID.hpp"
#include "Resources/iLocator.hpp"
#include "Math/Matrix44v.hpp"
#include "Math/Constants.hpp"
#include "Logging/Logging.hpp"

#include "Application/ScanCode.hpp"
#include "Application/KeyModifier.hpp"
#include "Application/MouseButton.hpp"
#include "Application/iMouseDevice.hpp"
#include "Application/iKeyboardDevice.hpp"
#include "Application/iInputManager.hpp"
#include "Application/iClipboard.hpp"
#include "Plugin/iRegistry.hpp"

#include "Std/Memory.hpp"
#include "Plugin/tClassInstance.hpp"

using namespace CPF;
using namespace Graphics;

//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Install(kDebugUICID.GetID(), new Plugin::tClassInstance<DebugUI>());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(kDebugUICID.GetID());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

//////////////////////////////////////////////////////////////////////////

IntrusivePtr<iClipboard> sClipboard;
char sClipboardText[1024];

DebugUI::DebugUI(iUnknown*)
	: mpDevice(nullptr)
	, mpLocator(nullptr)
	, mWidth(0)
	, mHeight(0)
	, mMouseWheel(0.0f)
{
	CPF_INIT_LOG(DebugUI);
	CPF_LOG_LEVEL(DebugUI, Trace);
}

DebugUI::~DebugUI()
{
	CPF_DROP_LOG(DebugUI);
}

bool DebugUI::Initialize(iDevice* device, iInputManager* im, iWindow* window, Resources::iLocator* locator)
{
	CPF_ASSERT(device != nullptr);
	CPF_ASSERT(locator != nullptr);
	mpDevice = device;
	mpLocator = locator;
	im->GetDevice(iMouseDevice::kDefault.GetID(), iMouseDevice::kIID.GetID(), mpMouse.AsVoidPP());
	im->GetDevice(iKeyboardDevice::kDefault.GetID(), iKeyboardDevice::kIID.GetID(), mpKeyboard.AsVoidPP());
	im->GetDevice(iClipboard::kDefault.GetID(), iClipboard::kIID.GetID(), sClipboard.AsVoidPP());

	// Load the shaders.
	// TODO: Consider moving the debug UI out so we don't need a dependency on resources.
	// TODO: The decision will have to wait till later though, have to know how this ends up dealing with cross api shaders first.
	{
		IntrusivePtr<IO::Stream> vertexShaderHlsl(mpLocator->Open(RESOURCE_ID("shaders/", "ui_vs.hlsl")));
		IntrusivePtr<IO::Stream> pixelShaderHlsl(mpLocator->Open(RESOURCE_ID("shaders/", "ui_ps.hlsl")));

		if (vertexShaderHlsl && pixelShaderHlsl)
		{
			IntrusivePtr<iBlob> vertexShaderByteCode;
			{
				auto vertexShaderSrc = ReadText(vertexShaderHlsl);
				mpDevice->CompileToByteCode("main", ShaderType::eVertex, vertexShaderSrc.size(), vertexShaderSrc.data(), vertexShaderByteCode.AsTypePP());
			}
			mpDevice->CreateShader(vertexShaderByteCode, mpVertexShader.AsTypePP());

			IntrusivePtr<iBlob> pixelShaderByteCode;
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
	ResourceDesc cbDesc{ ResourceType::eBuffer, HeapType::eUpload, ResourceState::eGenericRead, sizeof(Math::Matrix44fv), 0 };
	mpDevice->CreateConstantBuffer(&cbDesc, nullptr, mpProjectionMatrix.AsTypePP());

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
		PipelineStateDesc pipelineDesc = Build<PipelineStateDesc>()
			.VertexShader(mpVertexShader)
			.PixelShader(mpPixelShader)
			.Topology(TopologyType::eTriangle)

			.Rasterizer(Build<RasterizerStateDesc>()
				.CullMode(CullMode::eNone)
				.WindingOrder(WindingOrder::eClockwise)
				.DepthClipping(false)
			)
			.DepthStencil(Build<DepthStencilStateDesc>()
				.DepthTest(false)
				.DepthWriteMask(DepthWriteMask::eZero)
			)
			.InputLayout(Build<InputLayoutDesc>()
				.Element("POSITION", 0, Format::eRG32f, 0, 0, InputClassification::ePerVertex, 0)
				.Element("TEXCOORD", 0, Format::eRG32f, 0, 8, InputClassification::ePerVertex, 0)
				.Element("COLOR", 0, Format::eRGBA8un, 0, 16, InputClassification::ePerVertex, 0)
			)
			.TargetBlend(0, Build<RenderTargetBlendStateDesc>()
				.Blending(true)
				.Op(BlendOp::eAdd)
				.OpAlpha(BlendOp::eAdd)
				.Src(BlendFunc::eSrcAlpha)
				.SrcAlpha(BlendFunc::eOne)
				.Dst(BlendFunc::eInvSrcAlpha)
				.DstAlpha(BlendFunc::eInvSrcAlpha)
			)
			.RenderTargets({ Format::eRGBA8un })
			.DepthStencilFormat(Format::eD32f)
			;

		// Create the binding.
		ParamBindingDesc paramBindings[] =
		{
			{ BindingType::eConstantBuffer, 0, 0, ParamFlags::eStatic, ParamVisibility::eVertex },
			{ BindingType::eSampler, 0, 0, ParamFlags::eStatic, ParamVisibility::eVisibilityAll },
			{ BindingType::eTexture, 0, 0, ParamFlags::eStatic, ParamVisibility::eVisibilityAll }
		};
		ResourceBindingDesc bindings =
		{
			3,
			paramBindings
		};
		mpDevice->CreateResourceBinding(&bindings, mpResourceBinding.AsTypePP());

		// Create the actual pipeline object.
		mpDevice->CreatePipeline(&pipelineDesc, mpResourceBinding, mpPipeline.AsTypePP());
	}
	if (!mpResourceBinding || !mpPipeline)
		return false;

	//////////////////////////////////////////////////////////////////////////
	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = int(ScanCode::eTab);
	io.KeyMap[ImGuiKey_LeftArrow] = int(ScanCode::eLeft);
	io.KeyMap[ImGuiKey_RightArrow] = int(ScanCode::eRight);
	io.KeyMap[ImGuiKey_UpArrow] = int(ScanCode::eUp);
	io.KeyMap[ImGuiKey_DownArrow] = int(ScanCode::eDown);
	io.KeyMap[ImGuiKey_PageUp] = int(ScanCode::ePageUp);
	io.KeyMap[ImGuiKey_PageDown] = int(ScanCode::ePageDown);
	io.KeyMap[ImGuiKey_Home] = int(ScanCode::eHome);
	io.KeyMap[ImGuiKey_End] = int(ScanCode::eEnd);
	io.KeyMap[ImGuiKey_Delete] = int(ScanCode::eDelete);
	io.KeyMap[ImGuiKey_Backspace] = int(ScanCode::eBackspace);
	io.KeyMap[ImGuiKey_Enter] = int(ScanCode::eReturn);
	io.KeyMap[ImGuiKey_Escape] = int(ScanCode::eEscape);
	io.KeyMap[ImGuiKey_A] = int(ScanCode::eA);
	io.KeyMap[ImGuiKey_C] = int(ScanCode::eC);
	io.KeyMap[ImGuiKey_V] = int(ScanCode::eV);
	io.KeyMap[ImGuiKey_X] = int(ScanCode::eX);
	io.KeyMap[ImGuiKey_Y] = int(ScanCode::eY);
	io.KeyMap[ImGuiKey_Z] = int(ScanCode::eZ);
	io.RenderDrawListsFn = nullptr;
	io.SetClipboardTextFn = &DebugUI::_SetClipboardText;
	io.GetClipboardTextFn = &DebugUI::_GetClipboardText;

#ifdef _WIN32
	OSWindowData osData;
	window->GetOSData(&osData);
	io.ImeWindowHandle = osData.mHwnd;
#else
	(void)window;
#endif

	// Build the imgui font atlas.
	{
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
		if (pixels == nullptr)
			return false;
		const size_t dataSize = sizeof(uint32_t) * width * height;

		ImageDesc atlasDesc;
		atlasDesc.mFormat = Format::eRGBA8un;
		atlasDesc.mWidth = width;
		atlasDesc.mHeight = height;
		atlasDesc.mDepth = 1;
		atlasDesc.mMipLevels = 1;
		atlasDesc.mSamples = SampleDesc{ 1, 0 };
		atlasDesc.mState = ResourceState::eCopyDest;
		atlasDesc.mFlags = ImageFlags::eNone;

		// Create the target texture.
		mpDevice->CreateImage2D(HeapType::eDefault, &atlasDesc, nullptr, mpUIAtlas.AsTypePP());

		// Create the staging buffer.
		ResourceDesc stagingDesc{ ResourceType::eBuffer, HeapType::eUpload, ResourceState::eGenericRead, int32_t(dataSize), 0 };
		IntrusivePtr<iResource> staging;
		mpDevice->CreateResource(&stagingDesc, staging.AsTypePP());

		// Copy the image to the staging buffer.
		void* buffer;
		staging->Map(&buffer, nullptr);
		Std::MemCpy(buffer, pixels, sizeof(uint32_t) * width * height);
		staging->Unmap(nullptr);

		// Create a temporary command buffer and a fence to issue the copy from staging buffer to the image.
		IntrusivePtr<iCommandPool> tempPool;
		mpDevice->CreateCommandPool(tempPool.AsTypePP());
		IntrusivePtr<iCommandBuffer> tempCommands;
		mpDevice->CreateCommandBuffer(tempPool, CommandBufferType::ePrimary, tempCommands.AsTypePP());
		IntrusivePtr<iFence> tempFence;
		mpDevice->CreateFence(0, tempFence.AsTypePP());

		tempCommands->Reset(tempPool);
		tempCommands->Begin(nullptr);
		Graphics::ResourceData data;
		data.mpData = pixels;
		data.mPitch = width * sizeof(int32_t);
		data.mSlicePitch = data.mPitch * height;
		IntrusivePtr<iResource> targetResource;
		mpUIAtlas->QueryInterface(iResource::kIID.GetID(), targetResource.AsVoidPP());
		tempCommands->UpdateSubResource(staging, targetResource, &data);
		tempCommands->End();
		iCommandBuffer* commandBuffers[] = { tempCommands };
		mpDevice->Submit(1, commandBuffers);
		mpDevice->Signal(tempFence, 1);
		tempFence->WaitFor(1);
	}
	if (!mpUIAtlas)
		return false;

	// Attach window events.
	window->GetEmitter()->On<iWindow::OnMouseWheel>(Bind(&DebugUI::_OnMouseWheel, this, Placeholders::_1, Placeholders::_2));
	window->GetEmitter()->On<iWindow::OnButtonDown>(Bind(&DebugUI::_OnMouseDown, this, Placeholders::_1, Placeholders::_2, Placeholders::_3));
	window->GetEmitter()->On<iWindow::OnKeyDown>(Bind(&DebugUI::_OnKeyDown, this, Placeholders::_1));
	window->GetEmitter()->On<iWindow::OnKeyUp>(Bind(&DebugUI::_OnKeyUp, this, Placeholders::_1));

	// Create large buffers.
	ResourceDesc vbDesc{ ResourceType::eBuffer, HeapType::eUpload, ResourceState::eGenericRead, kVertexBufferSize, 1 };
	mpDevice->CreateVertexBuffer(&vbDesc, sizeof(ImDrawVert), mpVertexBuffer.AsTypePP());

	ResourceDesc ibDesc{ ResourceType::eBuffer, HeapType::eUpload, ResourceState::eGenericRead, kIndexBufferSize, 0 };
	mpDevice->CreateIndexBuffer(&ibDesc, Format::eR32u, mpIndexBuffer.AsTypePP());

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
	sClipboard.Assign(nullptr);
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
	{ -1.0f,						1.0f,						 0.5f,	1.0f }
	);
	mpProjectionMatrix->Update(0, sizeof(Math::Matrix44fv), &projection);

	//
	int32_t mx, my;
	mpMouse->GetPosition(&mx, &my);
	if (mx<0 || mx>mWidth || my<0 || my>mHeight)
		io.MousePos = ImVec2(-1.0f, -1.0f);
	else
		io.MousePos = ImVec2(static_cast<float>(mx), static_cast<float>(my));

	MouseButton button;
	mpMouse->GetButtonState(&button);
	io.MouseDown[0] = mMousePressed[0] || ((button & MouseButton::eLeft) != MouseButton::eNone);
	io.MouseDown[1] = mMousePressed[1] || ((button & MouseButton::eRight) != MouseButton::eNone);
	io.MouseDown[2] = mMousePressed[2] || ((button & MouseButton::eMiddle) != MouseButton::eNone);
	mMousePressed[0] = mMousePressed[1] = mMousePressed[2] = false;

	io.MouseWheel = mMouseWheel;
	mMouseWheel = 0.0f;

	// Start the frame
	ImGui::NewFrame();

	//	ImGui::ShowTestWindow();

	//////////////////////////////////////////////////////////////////////////
	/* Input testing
	Begin("Debug Info");
	ImGui::Text("%d", int32_t(button));
	ImGui::ColorButton(io.MouseDown[0] ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f) : ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::ColorButton(io.MouseDown[1] ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f) : ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::ColorButton(io.MouseDown[2] ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f) : ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	End();
	*/
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
	commands->SetSampler(1, mpSampler);
	commands->SetImage(2, mpUIAtlas);

	{
		Range vertRange{ 0, 0 };
		ImDrawVert* vertices = nullptr;
		reinterpret_cast<ImDrawVert*>(mpVertexBuffer->Map(reinterpret_cast<void**>(&vertices), nullptr));

		Range indexRange{ 0, 0 };
		ImDrawIdx* indices = nullptr;
		reinterpret_cast<ImDrawIdx*>(mpIndexBuffer->Map(reinterpret_cast<void**>(&indices), nullptr));

		for (int n = 0; n < drawData->CmdListsCount; ++n)
		{
			const ImDrawList* cmd_list = drawData->CmdLists[n];

			::memcpy(vertices, &cmd_list->VtxBuffer.front(), cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
			::memcpy(indices, &cmd_list->IdxBuffer.front(), cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));

			vertices += cmd_list->VtxBuffer.Size;
			vertRange.mEnd += cmd_list->VtxBuffer.Size * sizeof(ImDrawVert);
			indices += cmd_list->IdxBuffer.Size;
			indexRange.mEnd += cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx);
		}

		mpVertexBuffer->Unmap(&vertRange);
		mpIndexBuffer->Unmap(&indexRange);
	}

	size_t indexOffset = 0;
	size_t vertexOffset = 0;
	for (int n = 0; n < drawData->CmdListsCount; ++n)
	{
		const ImDrawList* cmd_list = drawData->CmdLists[n];
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
					static_cast<int>(pcmd->ClipRect.x),
					static_cast<int>(pcmd->ClipRect.z),
					static_cast<int>(pcmd->ClipRect.y),
					static_cast<int>(pcmd->ClipRect.w)
				};
				commands->SetScissorRects(1, &scissor);
				commands->DrawIndexedInstanced(pcmd->ElemCount, 1, int32_t(indexOffset), int32_t(vertexOffset), 0);
			}
			indexOffset += pcmd->ElemCount;
		}
		vertexOffset += cmd_list->VtxBuffer.Size;
	}
}

void DebugUI::PushItemWidth(int32_t width)
{
	ImGui::PushItemWidth(float(width));
}

void DebugUI::PopItemWidth()
{
	ImGui::PopItemWidth();
}

void DebugUI::Separator()
{
	ImGui::Separator();
}

void DebugUI::Begin(const char* name, bool* isOpen, uint32_t flags)
{
	ImGui::Begin(name, isOpen, flags);
}

void DebugUI::End()
{
	ImGui::End();
}

void DebugUI::Text(const char* fmt, ...)
{
	va_list vargs;
	va_start(vargs, fmt);
	ImGui::TextV(fmt, vargs);
	va_end(vargs);
}

void DebugUI::TextColored(const Math::Vector4fv& color, const char* fmt, ...)
{
	va_list vargs;
	va_start(vargs, fmt);
	ImVec4 c(color.x, color.y, color.z, color.w);
	ImGui::TextColoredV(c, fmt, vargs);
	va_end(vargs);
}

bool DebugUI::Button(const char* label, const Math::Vector2i size)
{
	ImVec2 imSize(float(size.x), float(size.y));
	return ImGui::Button(label, imSize);
}

bool DebugUI::SmallButton(const char* label)
{
	return ImGui::SmallButton(label);
}

bool DebugUI::CheckBox(const char* label, bool* flag)
{
	return ImGui::Checkbox(label, flag);
}

bool DebugUI::CheckBoxFlags(const char* label, uint32_t* flags, uint32_t flags_value)
{
	return ImGui::CheckboxFlags(label, flags, flags_value);
}

bool DebugUI::Slider(const char* label, int32_t* value, int vmin, int vmax, const char* fmt)
{
	int v = *value;
	bool result = ImGui::SliderInt(label, &v, vmin, vmax, fmt);
	*value = v;
	return result;
}

void DebugUI::Histogram(const char* label, const float* values, int32_t count, int32_t offset, const char* overlay, float scaleMin, float scaleMax, const Math::Vector2i size, int32_t stride)
{
	ImVec2 imSize(float(size.x), float(size.y));
	ImGui::PlotHistogram(label, values, count, offset, overlay, scaleMin, scaleMax, imSize, stride);
}

void DebugUI::ListBox(const char* label, int32_t* selectedItem, const char** items, int32_t itemCount, int32_t itemHeight)
{
	ImGui::ListBox(label, selectedItem, items, itemCount, itemHeight);
}

void DebugUI::SetWindowSize(int32_t width, int32_t height)
{
	mWidth = width;
	mHeight = height;
}

void DebugUI::Add(DebugUICall call, void* context)
{
	mDebugCalls.push_back({ call, context });
}

void DebugUI::Remove(DebugUICall call, void* context)
{
	DebugCallPair testPair{ call, context };
	for (size_t i = 0; i<mDebugCalls.size(); ++i)
	{
		if (testPair == mDebugCalls[i])
		{
			mDebugCalls.erase(mDebugCalls.begin() + i);
			return;
		}
	}
}

void DebugUI::Execute()
{
	for (const auto& it : mDebugCalls)
	{
		(*it.first)(this, it.second);
	}
}

void DebugUI::_OnMouseWheel(int32_t, int32_t y)
{
	if (y > 0)
		mMouseWheel = 1;
	if (y < 0)
		mMouseWheel = -1;

}

void DebugUI::_OnMouseDown(MouseButton button, int32_t, int32_t)
{
	if ((button & MouseButton::eLeft) == MouseButton::eLeft)
		mMousePressed[0] = true;
	if ((button & MouseButton::eRight) == MouseButton::eRight)
		mMousePressed[1] = true;
	if ((button & MouseButton::eMiddle) == MouseButton::eMiddle)
		mMousePressed[2] = true;
}

void DebugUI::_OnKeyDown(ScanCode code)
{
	_HandleKey(true, code);
}

void DebugUI::_OnKeyUp(ScanCode code)
{
	_HandleKey(false, code);
}

void DebugUI::_HandleKey(bool down, ScanCode code)
{
	ImGuiIO& io = ImGui::GetIO();
	int key = int(code);
	KeyModifier mods;
	mpKeyboard->GetModifiers(&mods);
	io.KeysDown[key] = down;
	io.KeyShift = (mods & KeyModifier::eShift) != KeyModifier::eNone;
	io.KeyCtrl = (mods & KeyModifier::eControl) != KeyModifier::eNone;
	io.KeyAlt = (mods & KeyModifier::eAlt) != KeyModifier::eNone;
	io.KeySuper = (mods & KeyModifier::eOS) != KeyModifier::eNone;
}

const char* DebugUI::_GetClipboardText()
{
	int32_t length = 1024;
	sClipboard->GetClipboardText(&length, sClipboardText);
	return sClipboardText;
}

void DebugUI::_SetClipboardText(const char* text)
{
	sClipboard->SetClipboardText(text);
}
