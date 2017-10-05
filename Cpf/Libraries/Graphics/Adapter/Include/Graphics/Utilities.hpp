//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		template <typename TYPE>
		TYPE Defaults();

		template <typename TYPE>
		struct BuilderType;

		template <typename TYPE>
		typename BuilderType<TYPE>::Builder Build()
		{
			return typename BuilderType<TYPE>::Builder();
		}
	}
}
