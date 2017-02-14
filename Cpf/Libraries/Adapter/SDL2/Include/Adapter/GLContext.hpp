//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Platform/iGLContext.hpp"
#include <sdl2/SDL.h>


namespace Cpf
{
	class iWindow;

	namespace Adapters
	{
		class GLContext : public Platform::iGLContext
		{
		public:
			GLContext(SDL_GLContext context);
			virtual ~GLContext();

			SDL_GLContext GetSDLGLContext() const;
			void Swap(iWindow*);

		private:
			SDL_GLContext mContext;
		};
	}
}
