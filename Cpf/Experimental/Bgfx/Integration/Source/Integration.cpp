#include "Integration.hpp"
#include "Logging\Logging.hpp"
#include "IO\IO.hpp"
#include "Resources\Resources.hpp"
#include "Resources\ResourceConfig.hpp"

#include "SDL.h"
#include "SDL_syswm.h"
#include <bx/bx.h>
#include <bx/uint32_t.h>
#include "bgfx/platform.h"

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

	// Create vertex stream declaration.
	PosColorVertex::init();

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;

	// Create static vertex buffer.
	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
		, PosColorVertex::ms_decl
	);

	// Create static index buffer.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip))
	);

	// Create program from shaders.
//	m_program = loadProgram("vs_cubes", "fs_cubes");

	///
	bgfx::reset(mWindowSize.x, mWindowSize.y, BGFX_RESET_MSAA_X8);
	bgfx::setDebug(BGFX_DEBUG_STATS);
	bgfx::setViewClear(
		0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
	);


	bool running = true;
	SDL_Event sdlEvent;
	while (running)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				running = false;
			}
		}

		bgfx::setViewRect(0, 0, 0, uint16_t(mWindowSize.x), uint16_t(mWindowSize.y));

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/00-helloworld");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");

		bgfx::dbgTextPrintf(0, 4, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

		const bgfx::Stats* stats = bgfx::getStats();
		bgfx::dbgTextPrintf(0, 6, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
			, stats->width
			, stats->height
			, stats->textWidth
			, stats->textHeight
		);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	bgfx::destroyIndexBuffer(m_ibh);
	bgfx::destroyVertexBuffer(m_vbh);
//	bgfx::destroyProgram(m_program);
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
