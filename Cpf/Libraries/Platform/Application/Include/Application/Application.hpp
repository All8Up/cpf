//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Application/Arguments.hpp"
#include "Platform/iGLContext.hpp"
#include "Events/Emitter.hpp"
#include "Math/Vector2v.hpp"
#include "String.hpp"
#include "PluginHost/Registry.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	//////////////////////////////////////////////////////////////////////////
	class Application : public Platform::Events::Emitter
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		using ApplicationCreate = Application* (*)();

		//////////////////////////////////////////////////////////////////////////
		virtual int Start(const CommandLine&) = 0;

		//////////////////////////////////////////////////////////////////////////
		Application();
		virtual ~Application();

		//////////////////////////////////////////////////////////////////////////
		bool IsRunning() const;
		void Quit();

		//////////////////////////////////////////////////////////////////////////
		using OnQuit = Platform::Events::Event< 0, std::function< bool() >, Platform::Events::AnyNotEqual<bool, true, true, false> >;

		//////////////////////////////////////////////////////////////////////////
		CommandLine& GetCommandLine() { return mCommandLine; }

		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<Plugin::iRegistry> GetRegistry() { return mpRegistry; }

	private:
		bool mRunning;
		CommandLine mCommandLine;
		IntrusivePtr<Plugin::iRegistry> mpRegistry;
	};


	Platform::iGLContext* GLCreateContext(iWindow*);
	void GLMakeCurrent(iWindow*, Platform::iGLContext*);
	bool GLInitialize(iWindow*);
}


#define CPF_CREATE_APPLICATION(appName)											\
namespace { Cpf::Application* createApplication() { return new appName; } }		\
Cpf::Application::ApplicationCreate gs_ApplicationCreate = createApplication;
