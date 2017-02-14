//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Cpf/Platform.hpp"
#include "Logging/Logging.hpp"

TEST(ANSI_C_FileSystem, Init)
{
	CPF_LOG_LEVELS(Trace);
	Cpf::ScopedInitializer<Cpf::PlatformInitializer> platform;
}
