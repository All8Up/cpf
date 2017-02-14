//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/unique_ptr.h"
#	include "EASTL/shared_ptr.h"
#else
#	include <memory>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename TYPE>
	using UniquePtr = CPF_STL_NAMESPACE::unique_ptr<TYPE>;

	template<typename TYPE>
	using SharedPtr = CPF_STL_NAMESPACE::shared_ptr<TYPE>;

	template<typename TYPE>
	inline SharedPtr<TYPE> MakeShared(TYPE* v) { return CPF_STL_NAMESPACE::make_shared<TYPE>(v); }

	template<typename TYPE>
	using EnableSharedFromThis = CPF_STL_NAMESPACE::enable_shared_from_this<TYPE>;

	template<typename LHS, typename RHS>
	inline SharedPtr<LHS> StaticPtrCast(const SharedPtr<RHS>& rhs)
	{
		return CPF_STL_NAMESPACE::static_pointer_cast<LHS, RHS>(rhs);
	}
}
