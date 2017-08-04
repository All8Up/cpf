//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>

namespace AST
{
	class Import
	{
	public:
		static std::shared_ptr<Import> Create(const std::string& module);

		const std::string& GetModule() const { return mModule; }

	private:
		Import(const std::string& module);

		std::string mModule;
	};
}
