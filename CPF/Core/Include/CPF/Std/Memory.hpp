//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <memory>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
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
	}
}
