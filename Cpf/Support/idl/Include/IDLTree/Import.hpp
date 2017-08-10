//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

namespace IDLTree
{
	class Import
	{
	public:
		Import(const std::string& module);

		const std::string& GetModule() const { return mModule; }

	private:
		std::string mModule;
	};
}
