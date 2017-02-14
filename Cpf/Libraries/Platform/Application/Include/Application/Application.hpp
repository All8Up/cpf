//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Application/Arguments.hpp"
#include "Platform/iGLContext.hpp"
#include "Events/Emitter.hpp"
#include "Math/Vector2.hpp"
#include "String.hpp"
#include "RefCounted.hpp"


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

	private:
		bool mRunning;
		CommandLine mCommandLine;
	};


	//////////////////////////////////////////////////////////////////////////
	enum class KeyCode : int32_t
	{
		eUnknown = 0,
		eReturn = '\r',
		eEscape = '\033',
		eBackspace = '\b',
		eTab = '\t',
		eSpace = ' ',
		eExclamation = '!',
		eDoubleQuote = '\"',
		eHash = '#',
		ePercent = '%',
		eDollar = '$',
		eAmpersand = '&',
		eSingleQuote = '\'',
		eLeftParen = '(',
		eRightParen = ')',
		eAsterisk = '*',
		ePlus = '+',
		eComma = ',',
		eMinus = '-',
		ePeriod = '.',
		eSlash = '/',
		eLeftBracket = '[',
		eRightBracket = ']',

		e0 = '0',
		e1 = '1',
		e2 = '2',
		e3 = '3',
		e4 = '4',
		e5 = '5',
		e6 = '6',
		e7 = '7',
		e8 = '8',
		e9 = '9',

		eColor = ':',
		eSemicolon = ';',
		eLess = '<',
		eEquals = '=',
		eGreater = '>',
		eQuestion = '?',
		eAt = '@',

		eBackslash = '\\',
		eCaret = '^',
		eUnderscore = '_',
		eBackQuote = '`',
		eA = 'a',
		eB = 'b',
		eC = 'c',
		eD = 'd',
		eE = 'e',
		eF = 'f',
		eG = 'g',
		eH = 'h',
		eI = 'i',
		eJ = 'j',
		eK = 'k',
		eL = 'l',
		eM = 'm',
		eN = 'n',
		eO = 'o',
		eP = 'p',
		eQ = 'q',
		eR = 'r',
		eS = 's',
		eT = 't',
		eU = 'u',
		eV = 'v',
		eW = 'w',
		eX = 'x',
		eY = 'y',
		eZ = 'z',

		eF1 = (1 << 30) | 58,
		eF2 = (1 << 30) | 59,
		eF3 = (1 << 30) | 60,
		eF4 = (1 << 30) | 61,
		eF5 = (1 << 30) | 62,
		eF6 = (1 << 30) | 63,
		eF7 = (1 << 30) | 64,
		eF8 = (1 << 30) | 65,
		eF9 = (1 << 30) | 66,
		eF10 = (1 << 30) | 67,
		eF11 = (1 << 30) | 68,
		eF12 = (1 << 30) | 69,
	};

	class WindowedApplication;

	struct WindowDesc
	{
		WindowDesc(WindowedApplication* app);

		WindowDesc& Title(const String& title);
		WindowDesc& Position(const Math::Vector2i& pos);
		WindowDesc& Size(const Math::Vector2i& size);
		WindowDesc& Flags(uint32_t flags);

		operator iWindow* () const;

		String mTitle;
		Math::Vector2i mPosition;
		Math::Vector2i mSize;
		uint32_t mFlags;

		WindowedApplication* mpApplication;
	};

	struct OSWindowData
	{
#if CPF_TARGET_WINDOWS
		HWND mHwnd;
		HDC mHDC;
#endif
#if CPF_TARGET_DARWIN
		void* mpView;
#endif
	};

	enum class ButtonID : int32_t
	{
		eLeft,
		eMiddle,
		eRight,
		eX1,
		eX2
	};

	class iWindow : public tRefCounted<iRefCounted>
	{
	public:
		enum
		{
			eFullscreen = 1 << 0,
			eSupportOpenGL = 1 << 1,
			eShown = 1 << 2,
			eHidden = 1 << 3,
			eBorderless = 1 << 4,
			eResizable = 1 << 5,
			eMinimized = 1 << 6,
			eMaximized = 1 << 7,
			eInputGrabbed = 1 << 8,
			eInputFocus = 1 << 9,
			eMouseFocus = 1 << 10,
			eFullscreenDesktop = 1 << 11,
			eAllowHDPI = 1 << 12,
			eMouseCapture = 1 << 13
		};

		static const Math::Vector2i Centered;

		virtual Math::Vector2i GetClientArea() const = 0;
		virtual OSWindowData GetOSWindowData() const = 0;
		virtual Platform::Events::Emitter& GetEmitter() = 0;

		using OnMouseMove = Platform::Events::Event< 1, Function<void(int32_t, int32_t)> >;
		using OnButtonDown = Platform::Events::Event< 2, Function<void(ButtonID, int32_t, int32_t)> >;
		using OnButtonUp = Platform::Events::Event< 3, Function<void(ButtonID, int32_t, int32_t)> >;
		using OnMouseWheel = Platform::Events::Event< 4, Function<void()> >;

		using OnKeyDown = Platform::Events::Event < 5, Function<void(KeyCode)> >;
		using OnResized = Platform::Events::Event < 6, Function<void(int32_t, int32_t)> >;

	protected:
		virtual ~iWindow() = 0;
	};

	Platform::iGLContext* GLCreateContext(iWindow*);
	void GLMakeCurrent(iWindow*, Platform::iGLContext*);
	bool GLInitialize(iWindow*);

	class WindowedApplication : public Application
	{
	public:
		virtual bool Poll() = 0;
		virtual bool Wait() = 0;

		virtual bool Create(const WindowDesc&, iWindow**) = 0;

		using RawInputHook = bool(*)(void* userContext, const void* event);
		virtual void AddRawInputHook(RawInputHook, void* userContext) = 0;
		virtual void RemoveRawInputHook(RawInputHook) = 0;
	};
}


#define CPF_CREATE_APPLICATION(appName)											\
namespace { Cpf::Application* createApplication() { return new appName; } }		\
Cpf::Application::ApplicationCreate gs_ApplicationCreate = createApplication;
