//////////////////////////////////////////////////////////////////////////
#include "Adapter/Window.hpp"
#include "Adapter/GLContext.hpp"
#include "Application/Application.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace Adapter;
using namespace Platform;

//////////////////////////////////////////////////////////////////////////
GLContext::GLContext(SDL_GLContext context)
	: mContext(context)
{}

GLContext::~GLContext()
{
	SDL_GL_DeleteContext(mContext);
}

SDL_GLContext GLContext::GetSDLGLContext() const
{
	return mContext;
}

void GLContext::Swap(iWindow* window)
{
	Window* win = reinterpret_cast<Window*>(window);
	SDL_GL_SwapWindow(win->GetSDLWindow());
}


//////////////////////////////////////////////////////////////////////////
iGLContext* Cpf::GLCreateContext(iWindow* window)
{
	Window* win = (Window*)window;
	return new GLContext(SDL_GL_CreateContext(win->GetSDLWindow()));
}

void Cpf::GLMakeCurrent(iWindow* window, iGLContext* context)
{
	Window* win = (Window*)window;
	GLContext* ctx = (GLContext*)context;

	SDL_GL_MakeCurrent(win->GetSDLWindow(), ctx->GetSDLGLContext());
}
