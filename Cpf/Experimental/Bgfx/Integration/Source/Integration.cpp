#include "Integration.hpp"
#include "Logging\Logging.hpp"
#include "IO\IO.hpp"
#include "Resources\Resources.hpp"
#include "Resources\ResourceConfig.hpp"

#include "Math/Matrix44v.hpp"
#include "Math/Vector2v.hpp"

#include "SDL.h"
#include "SDL_syswm.h"
#include <bx/bx.h>
#include <bx/fpumath.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>
#include "bgfx/platform.h"
#include "bgfx/embedded_shader.h"

using namespace Cpf;
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
	OSWindowData windowData = _window->GetOSWindowData();

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
{
	CPF_INIT_LOG(Integration);
}

BgfxIntegration::~BgfxIntegration()
{
	CPF_DROP_LOG(Integration);
}

int BgfxIntegration::Start(const CommandLine&)
{
	// Initialize libraries.
	ScopedInitializer<TimeInitializer> timeInit;
	ScopedInitializer<ThreadingInitializer> threadingInit;
	ScopedInitializer<IOInitializer> ioInit;
	ScopedInitializer<Resources::ResourcesInitializer> resourceInit;

	mpLocator.Adopt(Resources::Configuration("./integration_res/resource_config.json").GetLocator());

	mWindowSize.x = 1024;
	mWindowSize.y = 768;
	mpWindow.Adopt(
		WindowDesc(this)
		.Title("BGFX")
		.Position(iWindow::Centered)
		.Size(mWindowSize)
		.Flags(iWindow::eResizable | iWindow::eShown)
	);
	mpWindow->GetEmitter().On<iWindow::OnResized>(Bind(&BgfxIntegration::_Resize, this, Placeholders::_1, Placeholders::_2));

	bgfxSetWindow(mpWindow);
	bgfx::init();
	bgfx::reset(mWindowSize.x, mWindowSize.y, BGFX_RESET_MSAA_X8);
	bgfx::setDebug(BGFX_DEBUG_NONE);
	bgfx::setViewClear(
		0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
	);

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

	// Create program from shaders.
	IntrusivePtr<Platform::IO::Stream> vertexShader(mpLocator->Open(RESOURCE_ID("/", "vs_cubes.sc.bin")));
	Vector<uint8_t> vertexShaderData(Move(ReadBinary(vertexShader)));
	bgfx::ShaderHandle vsh = bgfx::createShader(bgfx::makeRef(vertexShaderData.data(), uint32_t(vertexShaderData.size())));

	IntrusivePtr<Platform::IO::Stream> fragmentShader(mpLocator->Open(RESOURCE_ID("/", "fs_cubes.sc.bin")));
	Vector<uint8_t> fragmentShaderData(Move(ReadBinary(fragmentShader)));
	bgfx::ShaderHandle fsh = bgfx::createShader(bgfx::makeRef(fragmentShaderData.data(), uint32_t(fragmentShaderData.size())));
	m_program = createProgram(vsh, fsh, true);

	int64_t m_timeOffset = bx::getHPCounter();
	while (IsRunning())
	{
		Poll();

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
		/*
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/01-cube");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering simple static mesh.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
		*/

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
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(mWindowSize.x) / float(mWindowSize.y), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(mWindowSize.x), uint16_t(mWindowSize.y));
		}

		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11; ++xx)
			{
				Math::Matrix44fv rotX = Math::Matrix44fv::RotationX(time + xx*0.21f);
				Math::Matrix44fv rotY = Math::Matrix44fv::RotationY(time + yy*0.37f);
				Math::Matrix44fv rotation = rotX * rotY;
				rotation[3] = { -15.0f + float(xx)*3.0f, -15.0f + float(yy)*3.0f, 0.0f, 1.0f };

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

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	bgfx::destroyIndexBuffer(m_ibh);
	bgfx::destroyVertexBuffer(m_vbh);
	bgfx::destroyProgram(m_program);
	bgfx::shutdown();
	mpLocator.Adopt(nullptr);
	mpWindow.Adopt(nullptr);
	return 0;
}

void BgfxIntegration::_Resize(int32_t width, int32_t height)
{
	mWindowSize.x = width;
	mWindowSize.y = height;
	bgfx::reset(mWindowSize.x, mWindowSize.y, BGFX_RESET_MSAA_X8);
}


//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPLICATION(Cpf::BgfxIntegration);
