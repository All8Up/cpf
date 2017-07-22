//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/iRegistry.hpp"

// Name and type of the plugin Install function.
const char kPluginAPIInstall[] = "Install";
using PluginAPIInstall = Cpf::GOM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);

// Name and type of the plugin Remove function.
const char kPluginAPIRemove[] = "Remove";
using PluginAPIRemove = Cpf::GOM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);
