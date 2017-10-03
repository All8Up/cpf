//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

#ifdef CPF_HAVE_SPDLOG
#include <spdlog/spdlog.h>

namespace CPF
{
	/** @brief Logging level names. */
	namespace LogLevel
	{
		const int Info = spdlog::level::info;
		const int Warn = spdlog::level::warn;
		const int Error = spdlog::level::err;
		const int Fatal = spdlog::level::critical;
	}

	class outputDebugSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		static std::shared_ptr<outputDebugSink> instance()
		{
			static std::shared_ptr<outputDebugSink> instance = std::make_shared<outputDebugSink>();
			return instance;
		}

	private:
		virtual void _sink_it(const spdlog::details::log_msg& msg) override
		{
#if CPF_TARGET_WINDOWS
			OutputDebugStringA(msg.formatted.str().c_str());
#endif
		}
		virtual void flush() override
		{}
	};

	inline void output_debug(const std::string& logger_name)
	{
		std::vector<spdlog::sink_ptr> sinks;

		std::shared_ptr<outputDebugSink> win = std::make_shared<outputDebugSink>();
		sinks.push_back(win);

		std::shared_ptr<spdlog::sinks::stdout_sink_mt> standard = std::make_shared<spdlog::sinks::stdout_sink_mt>();
		sinks.push_back(standard);

		spdlog::register_logger(std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end()));
	}

	inline void drop_debug(const std::string& logger_name)
	{
		spdlog::drop(logger_name);
	}
}


// Utility macros to integrate spdlog.
#define CPF_LOG_ACCESSOR_Info info
#define CPF_LOG_ACCESSOR_Warn warn
#define CPF_LOG_ACCESSOR_Error error
#define CPF_LOG_ACCESSOR_Fatal critical

// Look up the appropriate accessor function.
#define CPF_LOG_LEVEL_ACCESSOR_(l)	CPF_LOG_ACCESSOR_##l
#define CPF_LOG_LEVEL_ACCESSOR(l)	CPF_LOG_LEVEL_ACCESSOR_(l)

// Use the logs.
#define CPF_INIT_LOGGING(ARGC, ARGV) {}
#define CPF_INIT_LOG(name) {CPF::output_debug(#name);}
#define CPF_DROP_LOG(name) {CPF::drop_debug(#name);}
#define CPF_LOG(name, level) spdlog::get(#name)->CPF_LOG_LEVEL_ACCESSOR(level)()
#define CPF_LOG_LEVELS(l) spdlog::set_level(spdlog::level::CPF_LOG_LEVEL_ACCESSOR(l))
#define CPF_LOG_LEVEL(name, l) {spdlog::get(#name)->set_level(spdlog::level::CPF_LOG_LEVEL_ACCESSOR(l));}
#define CPF_TRACE_LOG(name) spdlog::get(#name)->trace()
#define CPF_DEBUG_LOG(name) spdlog::get(#name)->debug()

#elif defined(CPF_HAVE_GLOG)
#include "glog/logging.h"

// Utility macros to integrate glog.
#define CPF_LOG_ACCESSOR_Info INFO
#define CPF_LOG_ACCESSOR_Warn WARNING
#define CPF_LOG_ACCESSOR_Error ERROR
#define CPF_LOG_ACCESSOR_Fatal FATAL

// Look up the appropriate accessor function.
#define CPF_LOG_LEVEL_ACCESSOR_(l) CPF_LOG_ACCESSOR_##l
#define CPF_LOG_LEVEL_ACCESSOR(l) CPF_LOG_LEVEL_ACCESSOR_(l)
#define CPF_LOG_GLOG(l) LOG(l)

#define CPF_INIT_LOGGING(ARGC, ARGV) {FLAGS_alsologtostderr = 1; google::InitGoogleLogging(ARGV);}
#define CPF_INIT_LOG(name) {}
#define CPF_DROP_LOG(name) {}
#define CPF_LOG(name, level) CPF_LOG_GLOG( CPF_LOG_LEVEL_ACCESSOR(level) ) << "[" << #name << "] "
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
