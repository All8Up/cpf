//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include <spdlog/spdlog.h>

namespace Cpf
{
	/** @brief Logging level names. */
	namespace LogLevel
	{
		const int Trace = spdlog::level::trace;
		const int Debug = spdlog::level::debug;
		const int Info = spdlog::level::info;
		const int Notice = spdlog::level::notice;
		const int Warn = spdlog::level::warn;
		const int Error = spdlog::level::err;
		const int Critical = spdlog::level::critical;
		const int Alert = spdlog::level::alert;
		const int Emergency = spdlog::level::emerg;
		const int Off = spdlog::level::off;
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
			OutputDebugString(msg.formatted.str().c_str());
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
#define CPF_LOG_ACCESSOR_Trace trace
#define CPF_LOG_ACCESSOR_Info info
#define CPF_LOG_ACCESSOR_Notice notice
#define CPF_LOG_ACCESSOR_Warn warn
#define CPF_LOG_ACCESSOR_Error error
#define CPF_LOG_ACCESSOR_Critical critical
#define CPF_LOG_ACCESSOR_Alert alert
#define CPF_LOG_ACCESSOR_Emergency emergency

// Look up the appropriate accessor function.
#define CPF_LOG_LEVEL_ACCESSOR_(l)	CPF_LOG_ACCESSOR_##l
#define CPF_LOG_LEVEL_ACCESSOR(l)	CPF_LOG_LEVEL_ACCESSOR_(l)

// Use the logs.
#define CPF_INIT_LOG(name) {Cpf::output_debug(#name);}
#define CPF_DROP_LOG(name) {Cpf::drop_debug(#name);}
#define CPF_LOG(name, level) spdlog::get(#name)->CPF_LOG_LEVEL_ACCESSOR(level)()
#define CPF_LOG_LEVELS(l) spdlog::set_level(spdlog::level::CPF_LOG_LEVEL_ACCESSOR(l))
#define CPF_LOG_LEVEL(name, l) {spdlog::get(#name)->set_level(spdlog::level::CPF_LOG_LEVEL_ACCESSOR(l));}
#define CPF_TRACE_LOG(name) spdlog::get(#name)->trace()
#define CPF_DEBUG_LOG(name) spdlog::get(#name)->debug()
