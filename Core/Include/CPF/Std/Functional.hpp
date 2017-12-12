//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <functional>

namespace CPF
{
	template<typename Func>
	using Function = std::function<Func>;

	template<typename F, typename... Args>
	auto Bind(F&& f, Args&&... args)
	-> decltype(std::bind<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...))
	{
		return std::bind<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
	};

	template<typename R, typename F, typename... Args>
	auto Bind(F&& f, Args&&... args)
	-> decltype(std::bind<R, F, Args...>(std::forward<F>(f), std::forward<Args>(args)...))
	{
		return std::bind<R, F, Args...>(std::forward<F>(f), std::forward<Args>(args)... );
	};

	namespace Placeholders
	{
		using std::placeholders::_1;
		using std::placeholders::_2;
		using std::placeholders::_3;
		using std::placeholders::_4;
		using std::placeholders::_5;
		using std::placeholders::_6;
		using std::placeholders::_7;
		using std::placeholders::_8;
		using std::placeholders::_9;
	}

	template<typename TYPE>
	using Less = std::less<TYPE>;
	template<typename TYPE>
	using Greater = std::greater<TYPE>;
}
