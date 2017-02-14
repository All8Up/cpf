//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "String.hpp"
#include "Map.hpp"


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

		using CommandFunction = eastl::function<void (const Arguments&)>;
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
