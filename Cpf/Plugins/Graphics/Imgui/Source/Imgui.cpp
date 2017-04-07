//////////////////////////////////////////////////////////////////////////
#include "Imgui.hpp"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Imgui/imgui.h"

using namespace Cpf;

namespace
{
	int32_t s_RefCount = 0;
}

class Imgui : public tRefCounted<Cpf::Game::iImgui>
{
public:
	Imgui()
	{}

	virtual ~Imgui()
	{
		imguiDestroy();
	}

	COM::Result QueryInterface(Cpf::COM::InterfaceID id, void** outIface)
	{
		if (outIface)
		{
			switch (id.GetID())
			{
			case Cpf::COM::iUnknown::kIID.GetID():
				*outIface = static_cast<Cpf::COM::iUnknown*>(this);
				break;
			case Cpf::Game::iImgui::kIID.GetID():
				*outIface = static_cast<Cpf::Game::iImgui*>(this);
				break;
			default:
				return COM::kUnknownInterface;
			}
			AddRef();
			return COM::kOK;
		}
		return COM::kInvalidParameter;
	}

	COM::Result CPF_STDCALL Initialize() override
	{
		imguiCreate();
		return COM::kOK;
	}

	void CPF_STDCALL BeginFrame(int32_t width, int32_t height) override
	{
		imguiBeginFrame(0, 0, 0, 0, uint16_t(width), uint16_t(height));
	}

	void CPF_STDCALL EndFrame() override
	{
		imguiEndFrame();
	}

	bool CPF_STDCALL BeginScrollArea(const char* name, int32_t x, int32_t y, int32_t w, int32_t h, int* scroll) override
	{
		return imguiBeginScrollArea(name, x, y, w, h, scroll);
	}

	void CPF_STDCALL EndScrollArea() override
	{
		imguiEndScrollArea();
	}

	void CPF_STDCALL SeparatorLine() override
	{
		imguiSeparatorLine();
	}

	bool CPF_STDCALL Button(const char* text) override
	{
		return imguiButton(text);
	}
};

class ImguiClass : public tRefCounted<Cpf::Plugin::iClassInstance>
{
public:
	COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
	COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
	{
		if (outIface)
		{
			*outIface = new Imgui();
			return *outIface ? COM::kOK : COM::kOutOfMemory;
		}
		return COM::kInvalidParameter;
	}
};

extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Install(Cpf::Game::kBGFX_ImguiCID, new ImguiClass());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return s_RefCount == 0;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(Cpf::Game::kBGFX_ImguiCID);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
