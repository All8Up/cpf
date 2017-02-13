//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/unique_ptr.h"
#include "EASTL/shared_ptr.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename TYPE>
	using UniquePtr = eastl::unique_ptr<TYPE>;

	template<typename TYPE>
	using SharedPtr = eastl::shared_ptr<TYPE>;

	template<typename TYPE>
	inline SharedPtr<TYPE> MakeShared(TYPE* v) { return eastl::make_shared<TYPE>(v); }

	template<typename TYPE>
	using EnableSharedFromThis = eastl::enable_shared_from_this<TYPE>;

	template<typename LHS, typename RHS>
	inline SharedPtr<LHS> StaticPtrCast(const SharedPtr<RHS>& rhs)
	{
		return eastl::static_pointer_cast<LHS, RHS>(rhs);
	}
}
