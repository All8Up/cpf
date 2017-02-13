//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"

namespace Cpf
{
	namespace Std
	{
		CPF_EXPORT_STD void* MemChr(void* src, int ch, size_t size);
		CPF_EXPORT_STD const void* MemChr(const void* src, int ch, size_t size);
		CPF_EXPORT_STD int MemCmp(const void* lhs, const void* rhs, size_t size);
		CPF_EXPORT_STD void MemCpy(void* dest, const void* src, size_t size);
		CPF_EXPORT_STD void MemMove(void* dest, const void* src, size_t size);
		CPF_EXPORT_STD void MemSet(void* dest, uint8_t c, size_t size);
	}
}
