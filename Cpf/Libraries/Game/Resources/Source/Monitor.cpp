//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitor.hpp"

using namespace Cpf;
using namespace Resources;

Monitor::Monitor()
	: mpLocator(nullptr)
{}

Monitor::~Monitor()
{}

void Monitor::SetLocator(Locator* locator)
{
	mpLocator = locator;
}

Locator* Monitor::GetLocator() const
{
	return mpLocator;
}
