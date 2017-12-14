//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "glog/logging.h"

#define CPF_ENABLE_LOGGING 1

#if CPF_ENABLE_LOGGING
// Utility macros to integrate glog.
#define CPF_LOG_ACCESSOR_Info INFO
#define CPF_LOG_ACCESSOR_Warn WARNING
#define CPF_LOG_ACCESSOR_Error ERROR
#define CPF_LOG_ACCESSOR_Fatal FATAL

// Look up the appropriate accessor function.
#define CPF_LOG_LEVEL_ACCESSOR_(l) CPF_LOG_ACCESSOR_##l
#define CPF_LOG_LEVEL_ACCESSOR(l) CPF_LOG_LEVEL_ACCESSOR_(l)
#define CPF_LOG_GLOG(l) LOG(l)
#define CPF_LOG_IF_GLOG(l, cond) LOG_IF(l, cond)

#define CPF_INIT_LOGGING(ARGC, ARGV) {FLAGS_alsologtostderr = 1; google::InitGoogleLogging(ARGV);}
#define CPF_INIT_LOG(name) {}
#define CPF_DROP_LOG(name) {}
#define CPF_LOG(name, level) CPF_LOG_GLOG( CPF_LOG_LEVEL_ACCESSOR(level) ) << "[" << #name << "] "
#define CPF_LOG_IF(name, level, cond) CPF_LOG_IF_GLOG( CPF_LOG_LEVEL_ACCESSOR(level), cond ) << "[" << #name << "] "
#define CPF_LOG_LEVELS(l) {}
#define CPF_LOG_LEVEL(name, l) {}
#define CPF_TRACE_LOG(name) {}
#define CPF_DEBUG_LOG(name) {}

#else
#include <iostream>

#define CPF_INIT_LOGGING(ARGC, ARGV) {}
#define CPF_INIT_LOG(name) {}
#define CPF_DROP_LOG(name) {}
#define CPF_LOG(name, level) std::cout
#define CPF_LOG_LEVELS(l) {}
#define CPF_LOG_LEVEL(name, l) {}
#define CPF_TRACE_LOG(name) {}
#define CPF_DEBUG_LOG(name) {}

#endif
