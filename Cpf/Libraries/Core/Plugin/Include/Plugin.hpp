//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/Library.hpp"
#include "Plugin/iRegistry.hpp"

#include "COM/iUnknown.hpp"

const char kPluginAPIInstall[] = "Install";
using PluginAPIInstall = Cpf::COM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);

const char kPluginAPICanUnload[] = "CanUnload";
using PluginAPICanUnload = Cpf::COM::Result(CPF_STDCALL *)(void);

const char kPluginAPIRemove[] = "Remove";
using PluginAPIRemove = Cpf::COM::Result(CPF_STDCALL *)(Cpf::Plugin::iRegistry*);
