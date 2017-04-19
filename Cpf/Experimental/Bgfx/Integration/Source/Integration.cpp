#include "Integration.hpp"
#include "Logging/Logging.hpp"
#include "IO/IO.hpp"
#include "IO/File.hpp"
#include "IO/Directory.hpp"
#include "Resources/Resources.hpp"
#include "Resources/ResourceConfig.hpp"
#include "MultiCore.hpp"

#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "Application/OSWindowData.hpp"

#include "Math/Algorithm.hpp"
#include "Math/Matrix44v.hpp"
#include "Math/Vector2v.hpp"

#include "SDL2/CIDs.hpp"

#include <bx/bx.h>
#include <bx/fpumath.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>
#include "bgfx/platform.h"
#include "bgfx/embedded_shader.h"

#include "Imgui/imgui.h"
#include "Plugin.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;
using namespace Threading;
using namespace MultiCore;

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[] =
{
	{ -1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{ -1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{ -1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{ -1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint16_t s_cubeTriStrip[] =
{
	0, 1, 2,
	3,
	7,
	1,
	5,
	0,
	4,
	2,
	6,
	7,
	4,
	5,
};


//////////////////////////////////////////////////////////////////////////
inline bool bgfxSetWindow(iWindow* _window)
{
	OSWindowData windowData;
	_window->GetOSData(&windowData);

	bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	pd.ndt = wmi.info.x11.display;
	pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#	elif BX_PLATFORM_OSX
	pd.ndt = NULL;
	pd.nwh = wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
	pd.ndt = NULL;
	pd.nwh = windowData.mHwnd;
#	elif BX_PLATFORM_STEAMLINK
	pd.ndt = wmi.info.vivante.display;
	pd.nwh = wmi.info.vivante.window;
#	endif // BX_PLATFORM_
	pd.context = NULL;
	pd.backBuffer = NULL;
	pd.backBufferDS = NULL;
	bgfx::setPlatformData(pd);

	return true;
}
//////////////////////////////////////////////////////////////////////////

BgfxIntegration::BgfxIntegration()
	: mResetFlags(BGFX_RESET_MSAA_X8)
	, mSelectedRenderDevice(-1)
	, mNvg(nullptr)
	, mpRegistry(nullptr)
	, mpApplication(nullptr)
{
	CPF_INIT_LOG(Integration);
}

BgfxIntegration::~BgfxIntegration()
{
	CPF_DROP_LOG(Integration);
}

bool BgfxIntegration::_CreateWindow()
{
	mWindowSize.x = 1024;
	mWindowSize.y = 768;
	WindowDesc windowDesc;
	windowDesc.mpTitle = "BGFX";
	windowDesc.mX = iWindow::Centered();
	windowDesc.mY = iWindow::Centered();
	windowDesc.mWidth = mWindowSize.x;
	windowDesc.mHeight = mWindowSize.y;
	windowDesc.mFlags = WindowFlags::eResizable | WindowFlags::eShown;
	mpApplication->Create(&windowDesc, mpWindow.AsTypePP());
	mpWindow->GetEmitter()->On<iWindow::OnResize>(Bind(&BgfxIntegration::_Resize, this, Placeholders::_1, Placeholders::_2));

	return bool(mpWindow) && bgfxSetWindow(mpWindow);
}

bool BgfxIntegration::_InitializeResources()
{
	mpLocator.Adopt(Resources::Configuration("./integration_res/resource_config.json").GetLocator());
	return bool(mpLocator);
}

bool BgfxIntegration::_InitializeConcurrency()
{
	int targetThreads = Thread::GetHardwareThreadCount() - 1;
	targetThreads = Min(1, targetThreads);
	if (mScheduler.Initialize(Move(Thread::Group(targetThreads))) &&
		mThreadPool.Initialize(Move(Thread::Group(targetThreads))))
	{
		Concurrency::LoadBalancer::Schedulers schedulers{ &mScheduler, &mThreadPool.GetScheduler() };
		mLoadBalancer.SetSchedulers(&schedulers);
		return true;
	}
	return false;
}

bool BgfxIntegration::_InitializePipeline()
{
	if (COM::Succeeded(GetRegistry()->Create(nullptr, MultiCore::kPipelineCID, MultiCore::iPipeline::kIID, mpPipeline.AsVoidPP())))
	{
		GetRegistry()->Create(nullptr, MultiCore::kTimerCID, MultiCore::iTimer::kIID, mpTimer.AsVoidPP());
		mpTimer->Initialize(GetRegistry(), "Game Time", nullptr);
		return bool(mpTimer);
	}
	return false;
}

bool BgfxIntegration::_SelectRenderDevice()
{
	bgfx::RendererType::Enum types[bgfx::RendererType::Count];
	auto count = bgfx::getSupportedRenderers(bgfx::RendererType::Count, types);

	if (count > 0)
	{
		CPF_LOG(Integration, Info) << "Available render devices:";
		for (int i = 0; i < count; ++i)
		{
			CPF_LOG(Integration, Info) << "   " << bgfx::getRendererName(types[i]);
		}

		//
		mSelectedRenderDevice = types[0];

		for (int i = 0; i < count; ++i)
		{
			// Prefer dx12 over anything else.
			if (types[i] == bgfx::RendererType::Direct3D12)
			{
				mSelectedRenderDevice = types[i];
				continue;
			}
			// Prefer vulkan over anything but dx12.
			if (types[i] == bgfx::RendererType::Vulkan)
			{
				if (mSelectedRenderDevice != bgfx::RendererType::Direct3D12)
				{
					mSelectedRenderDevice = types[i];
					continue;
				}
			}
			// Prefer dx11 over anything but dx12 and vulkan.
			if (types[i] == bgfx::RendererType::Direct3D11)
			{
				if (mSelectedRenderDevice != bgfx::RendererType::Direct3D12 &&
					mSelectedRenderDevice != bgfx::RendererType::Vulkan)
				{
					mSelectedRenderDevice = types[i];
					continue;
				}
			}
			// TODO: Add more tests.
		}

		CPF_LOG(Integration, Info) << "---- Selected: " << bgfx::getRendererName(bgfx::RendererType::Enum(mSelectedRenderDevice));
		return true;
	}

	return false;
}

COM::Result CPF_STDCALL BgfxIntegration::Initialize(Plugin::iRegistry* registry, COM::ClassID* appCid)
{
	mpRegistry = registry;
	*appCid = SDL2::kWindowedApplicationCID;

	// Setup initial working directory.
	auto exePath = IO::File::GetExecutableFilePath();
	exePath += "../resources/";
	IO::Directory::SetWorkingDirectory(exePath);

	GetRegistry()->Load("plugins/Adapter_SDL2.cfp");
	return COM::kOK;
}

void CPF_STDCALL BgfxIntegration::Shutdown()
{}

COM::Result CPF_STDCALL BgfxIntegration::Main(iApplication* application)
{
	application->QueryInterface(iWindowedApplication::kIID, reinterpret_cast<void**>(&mpApplication));

	// Initialize libraries.
	ScopedInitializer<ThreadingInitializer> threadingInit;
	ScopedInitializer<ConcurrencyInitializer> concurrencyInit;
	ScopedInitializer<IOInitializer> ioInit;
	ScopedInitializer<Resources::ResourcesInitializer> resourceInit;

	CPF_INIT_MULTICORE(GetRegistry(), CPF_COMMON_PLUGINS);

	if (_InitializeResources() &&
		_CreateWindow() &&
		_InitializeConcurrency() &&
		_InitializePipeline() &&
		_SelectRenderDevice())
	{
		bgfx::init(bgfx::RendererType::Enum(mSelectedRenderDevice));
		bgfx::reset(mWindowSize.x, mWindowSize.y, mResetFlags);
		bgfx::setDebug(BGFX_DEBUG_NONE);
		bgfx::setViewClear(
			0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);
		mNvg = nvgCreate(1, 255);
		IntrusivePtr<Platform::IO::Stream> roboto_reg_font(mpLocator->Open(RESOURCE_ID("font/", "roboto-regular.ttf")));
		Vector<uint8_t> robotoData(Move(ReadBinary(roboto_reg_font)));
		mFont = nvgCreateFontMem(mNvg, "roboto-regular", robotoData.data(), int(robotoData.size()), 0);

		imguiCreate();

		// Create vertex stream declaration.
		PosColorVertex::init();

		///
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;
		bgfx::ProgramHandle m_program;

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
			, PosColorVertex::ms_decl
		);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip))
		);

		int32_t mScrollArea = 0;

		// Create program from shaders.
		IntrusivePtr<Platform::IO::Stream> vertexShader(mpLocator->Open(RESOURCE_ID("/", "vs_cubes.sc.bin")));
		Vector<uint8_t> vertexShaderData(Move(ReadBinary(vertexShader)));
		bgfx::ShaderHandle vsh = bgfx::createShader(bgfx::makeRef(vertexShaderData.data(), uint32_t(vertexShaderData.size())));

		IntrusivePtr<Platform::IO::Stream> fragmentShader(mpLocator->Open(RESOURCE_ID("/", "fs_cubes.sc.bin")));
		Vector<uint8_t> fragmentShaderData(Move(ReadBinary(fragmentShader)));
		bgfx::ShaderHandle fsh = bgfx::createShader(bgfx::makeRef(fragmentShaderData.data(), uint32_t(fragmentShaderData.size())));
		m_program = createProgram(vsh, fsh, true);

		Concurrency::Scheduler::Semaphore pipelineComplete;
		mpPipeline->Configure();
		int64_t m_timeOffset = bx::getHPCounter();
		while (mpApplication->IsRunning())
		{
			mpApplication->Poll();

			mLoadBalancer.Balance();
			mpPipeline->Submit(&mScheduler);
			mScheduler.Submit(pipelineComplete);
			pipelineComplete.Acquire();

			bgfx::setViewRect(0, 0, 0, uint16_t(mWindowSize.x), uint16_t(mWindowSize.y));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const double toMs = 1000.0 / freq;
			float time = (float)((now - m_timeOffset) / double(bx::getHPFrequency()));

			// Use debug font to print information about this example.
			float at[3] = { 0.0f, 0.0f,   0.0f };
			float eye[3] = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING))
			{
				float view[16];
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

				// Set view 0 default viewport.
				//
				// Use HMD's width/height since HMD's internal frame buffer size
				// might be much larger than window size.
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				Matrix44fv view = Matrix44fv::LookAt(Vector3fv(eye), Vector3fv(at), Vector3fv(0.0f, 1.0f, 0.0f));
				float normalizedNear = bgfx::getCaps()->homogeneousDepth ? -1.0f : 0.0f;
				Matrix44fv proj = Matrix44fv::PerspectiveFovLH(60.0f * kDegToRad, float(mWindowSize.x) / float(mWindowSize.y), 0.1f, 100.0f, normalizedNear, 1.0f);
				bgfx::setViewTransform(0, view.Data(), proj.Data());

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(mWindowSize.x), uint16_t(mWindowSize.y));
			}

			for (uint32_t yy = 0; yy < 11; ++yy)
			{
				for (uint32_t xx = 0; xx < 11; ++xx)
				{
					for (uint32_t zz = 0; zz < 11; ++zz)
					{
						Math::Matrix44fv rotX = Math::Matrix44fv::RotationX(time + xx*0.21f);
						Math::Matrix44fv rotY = Math::Matrix44fv::RotationY(time + yy*0.37f);
						Math::Matrix44fv rotation = rotY * rotX;
						rotation[3] = { -15.0f + float(xx)*3.0f, -15.0f + float(yy)*3.0f, 5.0f + float(zz) * 3.0f, 1.0f };

						// Set model matrix for rendering.
						bgfx::setTransform(rotation.Data());

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(m_vbh);
						bgfx::setIndexBuffer(m_ibh);

						// Set render states.
						bgfx::setState(0
							| BGFX_STATE_DEFAULT
							| BGFX_STATE_PT_TRISTRIP
						);

						// Submit primitive for rendering to view 0.
						bgfx::submit(0, m_program);
					}
				}
			}

			// Simple test of nvg.
			nvgBeginFrame(mNvg, mWindowSize.x, mWindowSize.y, 1.0f);
			{
				nvgBeginPath(mNvg);
				nvgStrokeWidth(mNvg, 5.0f);
				nvgStrokeColor(mNvg, { 1.0f, 1.0f, 1.0f, 0.5f });
				nvgEllipse(mNvg, 50, 50, 40, 30);
				nvgStroke(mNvg);

				nvgBeginPath(mNvg);
				nvgStrokeWidth(mNvg, 2.0f);
				nvgStrokeColor(mNvg, { 0.5f, 0.8f, 1.0f, 0.9f });
				nvgRoundedRect(mNvg, 200.0f, 200.0f, 50.0f, 50.0f, 10.0f);
				nvgFillColor(mNvg, {0.0f, 0.25f, 0.5f, 1.0f});
				nvgFill(mNvg);
				nvgStroke(mNvg);

				nvgSave(mNvg);

				nvgFontSize(mNvg, 8.0f);
				nvgFontFace(mNvg, "roboto-regular");
				nvgTextAlign(mNvg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
				nvgText(mNvg, 100.0f, 100.0f, "Test text", nullptr);

				nvgRestore(mNvg);
			}
			nvgEndFrame(mNvg);

			// Simple test of imgui.
			imguiBeginFrame(0, 0, 0, 0, uint16_t(mWindowSize.x), uint16_t(mWindowSize.y));
			{
				imguiBeginScrollArea("Settings", mWindowSize.x - mWindowSize.x / 5 - 10, 10, mWindowSize.x / 5, mWindowSize.y / 2, &mScrollArea);
				imguiSeparatorLine();
				if (imguiButton("Hello"))
				{
					m_timeOffset = bx::getHPCounter();
				}
				imguiEndScrollArea();
			}
			imguiEndFrame();

			// Render
			bgfx::frame();
		}

		nvgDelete(mNvg);
		imguiDestroy();
		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		bgfx::destroyProgram(m_program);
		bgfx::shutdown();
		mScheduler.Shutdown();
		mpWindow.Adopt(nullptr);
	}
	mpLocator.Adopt(nullptr);
	return COM::kOK;
}

void BgfxIntegration::_Resize(int32_t width, int32_t height)
{
	mWindowSize.x = width;
	mWindowSize.y = height;
	bgfx::reset(mWindowSize.x, mWindowSize.y, mResetFlags);
}


//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPMAIN(Cpf::BgfxIntegration);
