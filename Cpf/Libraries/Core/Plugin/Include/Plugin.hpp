//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin/iRegistry.hpp"

// Name and type of the plugin Install function.
const char kPluginAPIInstall[] = "Install";
using PluginAPIInstall = CPF::GOM::Result(CPF_STDCALL *)(CPF::Plugin::iRegistry*);

// Name and type of the plugin Remove function.
const char kPluginAPIRemove[] = "Remove";
using PluginAPIRemove = CPF::GOM::Result(CPF_STDCALL *)(CPF::Plugin::iRegistry*);
