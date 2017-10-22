//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	template <typename TYPE>
	class Future;
	template <typename TYPE>
	class Future<TYPE&>;
	template <>
	class Future<void>;

	template <typename TYPE>
	class Promise;
	template <typename TYPE>
	class Promise<TYPE&>;
	template <>
	class Promise<void>;

}
