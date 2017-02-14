//////////////////////////////////////////////////////////////////////////
#pragma once
//#include "tclap/CmdLine.h"
#include "Vector.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct CommandLine {};
	/*
	using CommandLine = TCLAP::CmdLine;
	template<typename TYPE>
	using ValueArg = TCLAP::ValueArg<TYPE>;
	template<typename TYPE>
	class ValuesConstraint : public TCLAP::ValuesConstraint<TYPE>
	{
	public:
		ValuesConstraint(Vector<TYPE>& allowed)
			: TCLAP::ValuesConstraint<TYPE>(std::vector<TYPE>(allowed.begin(), allowed.end()))
		{}
	};


	namespace Platform
	{
		class Arguments
		{};
	}
	*/
}
