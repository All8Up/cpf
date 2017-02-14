//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "String.hpp"
#include "Map.hpp"
#include "Functional.hpp"


namespace Cpf
{
	class ConsoleCommands
	{
	public:
		ConsoleCommands() {}
		~ConsoleCommands() {}

		class Arguments
		{};

		class Builder
		{
		public:
			Builder(ConsoleCommands* cmds, const String& name)
			: mConsoleCommands(cmds)
			, mName(name) {}
			~Builder()
			{
				mConsoleCommands->Add(mName);
			}

		private:
			ConsoleCommands* mConsoleCommands;
			String mName;
		};

		using CommandFunction = CPF_STL_NAMESPACE::function<void (const Arguments&)>;
		Builder CreateCommand(const String& name, CommandFunction func) {return Builder(this, name);}
		void Add(const String& name)
		{
			mCommands[name] = ArgumentDesc();
		}

		void operator ()(const String& line);

	private:
		struct ArgumentDesc
		{};

		using CommandMap = Cpf::Map<String, ArgumentDesc>;

		CommandMap mCommands;
	};
}
