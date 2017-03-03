//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/WindowedApp.hpp"

namespace Cpf
{
	class Networked : public Adapter::WindowedApp
	{
	public:
		Networked();
		~Networked();

		int Start(const CommandLine&) override;
	};
}