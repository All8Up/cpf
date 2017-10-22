//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	// Exceptions or not exceptions, that is the question.
	// Is std::exception_ptr safe across dll boundaries?
	// Best guess is that it is unlikely if there are mixed crt's.

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
