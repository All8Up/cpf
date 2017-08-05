//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>

namespace AST
{
	class Interface
	{
	public:
		static std::shared_ptr<Interface> Create(const std::string& name);

	private:
		Interface(const std::string& name);

		std::string mName;
	};
}
