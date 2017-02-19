//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Configuration.hpp>


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_STD
#		define CPF_EXPORT_STD
#	else // CPF_STATIC_STD
#		if CPF_BUILD_STD
#			define CPF_EXPORT_STD CPF_EXPORT
#		else
#			define CPF_EXPORT_STD CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_STD CPF_EXPORT
#	else
#		define CPF_EXPORT_STD
#	endif
#endif // CPF_TARGET_WINDOWS


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct StdInitializer
	{
		CPF_EXPORT_STD static int Install();
		CPF_EXPORT_STD static int Remove();

	private:
		StdInitializer() = delete;
		~StdInitializer() = delete;
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename LHS, typename RHS>
	LHS Min(LHS a, RHS b)
	{
		return LHS((a < b) ? a : b);
	}

	template <typename LHS, typename RHS>
	LHS Max(LHS a, RHS b)
	{
		return LHS((a > b) ? a : b);
	}
}
