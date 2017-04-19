//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/Library.hpp"
#include "Plugin/iRegistry.hpp"

// Name and type of the plugin Install function.
const char kPluginAPIInstall[] = "Install";
using PluginAPIInstall = Cpf::COM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);

// Name and type of the plugin CanUnload function.
const char kPluginAPICanUnload[] = "CanUnload";
using PluginAPICanUnload = Cpf::COM::Result(CPF_STDCALL *)(void);

// Name and type of the plugin Remove function.
const char kPluginAPIRemove[] = "Remove";
using PluginAPIRemove = Cpf::COM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);
