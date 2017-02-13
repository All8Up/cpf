//////////////////////////////////////////////////////////////////////////
#include "Std/Memory.hpp"
#include <cstring>

using namespace Cpf;

CPF_EXPORT_STD void* Std::MemChr(void* src, int ch, size_t size)
{
	return std::memchr(src, ch, size);
}

CPF_EXPORT_STD const void* Std::MemChr(const void* src, int ch, size_t size)
{
	return std::memchr(src, ch, size);
}

CPF_EXPORT_STD int Std::MemCmp(const void* lhs, const void* rhs, size_t size)
{
	return std::memcmp(lhs, rhs, size);
}

CPF_EXPORT_STD void Std::MemCpy(void* dest, const void* src, size_t size)
{
	std::memcpy(dest, src, size);
}

CPF_EXPORT_STD void Std::MemMove(void* dest, const void* src, size_t size)
{
	std::memmove(dest, src, size);
}

CPF_EXPORT_STD void Std::MemSet(void* dest, uint8_t c, size_t size)
{
	std::memset(dest, c, size);
}
