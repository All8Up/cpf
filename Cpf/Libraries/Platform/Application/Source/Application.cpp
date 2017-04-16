//////////////////////////////////////////////////////////////////////////
#include "Application/iApplication.hpp"
#include "Application/iWindowedApplication.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"

//////////////////////////////////////////////////////////////////////////
using namespace Cpf;


//////////////////////////////////////////////////////////////////////////
WindowDesc::WindowDesc(iWindowedApplication* app)
	: mpApplication(app)
	, mTitle("")
	, mPosition(iWindow::Centered(), iWindow::Centered())
	, mSize(Math::Vector2i(200, 200))
	, mFlags(WindowFlags::eNone)
{}

WindowDesc& WindowDesc::Title(const String& title)
{
	mTitle = title;
	return *this;
}

WindowDesc& WindowDesc::Position(const Math::Vector2i& pos)
{
	mPosition = pos;
	return *this;
}

WindowDesc& WindowDesc::Size(const Math::Vector2i& size)
{
	mSize = size;
	return *this;
}

WindowDesc& WindowDesc::Flags(WindowFlags flags)
{
	mFlags = flags;
	return *this;
}

WindowDesc::operator iWindow* () const
{
	iWindow* result = nullptr;
	if (Cpf::COM::Succeeded(mpApplication->Create(*this, &result)))
		return result;
	return nullptr;
}
