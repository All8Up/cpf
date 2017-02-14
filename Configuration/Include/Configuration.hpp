//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Configuration/Platform/OSSetup.hpp>
#include <Configuration/Setup.hpp>
#include <Configuration/Assert.hpp>
#include <Configuration/Compiler/ImportExport.hpp>
#include <Configuration/Compiler/Alignment.hpp>
#include <Configuration/Platform/DebugBreak.hpp>
#include <cstdint>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	/** @brief CPF uses WChar_t as 16bit to avoid compiler differences. */
	using WChar_t = char16_t;

	/** @brief Utility to scope initialization of libraries. */
	template<typename TYPE>
	class ScopedInitializer
	{
	public:
		ScopedInitializer() { TYPE::Install(); }
		~ScopedInitializer() { TYPE::Remove(); }
	};
}

//////////////////////////////////////////////////////////////////////////
#define _CPF_STRINGIZE(a) #a
#define CPF_STRINGIZE(a) _CPF_STRINGIZE(a)
#define _CPF_CONCAT(a, b) a##b
#define CPF_CONCAT(a, b) _CPF_CONCAT(a, b)

//////////////////////////////////////////////////////////////////////////
#define CPF_COUNTOF(a) (sizeof(a) / sizeof(decltype(a)))
