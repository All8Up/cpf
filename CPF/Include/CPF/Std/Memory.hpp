//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <memory>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename TYPE>
	using UniquePtr = std::unique_ptr<TYPE>;

	template<typename TYPE>
	using SharedPtr = std::shared_ptr<TYPE>;

	template<typename TYPE>
	inline SharedPtr<TYPE> MakeShared(TYPE* v) { return std::make_shared<TYPE>(v); }

	template<typename TYPE>
	using EnableSharedFromThis = std::enable_shared_from_this<TYPE>;

	template<typename LHS, typename RHS>
	inline SharedPtr<LHS> StaticPtrCast(const SharedPtr<RHS>& rhs)
	{
		return std::static_pointer_cast<LHS, RHS>(rhs);
	}

	namespace Std
	{
		inline void* MemChr(void* src, int ch, size_t size) { return std::memchr(src, ch, size); }
		inline const void* MemChr(const void* src, int ch, size_t size) { return std::memchr(src, ch, size); }
		inline int MemCmp(const void* lhs, const void* rhs, size_t size) { return std::memcmp(lhs, rhs, size); }
		inline void MemCpy(void* dest, const void* src, size_t size) { std::memcpy(dest, src, size); }
		inline void MemMove(void* dest, const void* src, size_t size) { std::memmove(dest, src, size); }
		inline void MemSet(void* dest, uint8_t c, size_t size) { std::memset(dest, c, size); }
	}
}
