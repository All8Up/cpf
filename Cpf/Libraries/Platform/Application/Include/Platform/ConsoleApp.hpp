//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Platform/Platform.hpp"
#include "Platform/Arguments.hpp"


namespace Cpf
{
	namespace Platform
	{
		class Arguments;

		class ConsoleApp
		{
		public:
			virtual ~ConsoleApp();

			virtual int Main(Arguments&&) = 0;
		};
	}
}
