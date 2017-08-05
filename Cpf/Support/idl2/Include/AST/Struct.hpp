//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>

namespace AST
{
	class Struct
	{
	public:
		static std::shared_ptr<Struct> Create(const std::string& name);

	private:
		Struct(const std::string& name);

		std::string mName;
	};
}