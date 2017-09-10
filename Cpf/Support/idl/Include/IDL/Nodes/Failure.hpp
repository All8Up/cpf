//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/Nodes/Node.hpp"
#include "String.hpp"


namespace IDL
{
	class Failure : public Node
	{
	public:
		Failure(const Cpf::String& name, const Cpf::String& subSystem, const Cpf::String& description)
			: mName(name)
			, mSubSystem(subSystem)
			, mDescription(description)
		{
		}

		const Cpf::String& GetName() const { return mName; }
		const Cpf::String& GetSubSystem() const { return mSubSystem; }
		const Cpf::String& GetDescription() const { return mDescription; }

	private:
		Cpf::String mName;
		Cpf::String mSubSystem;
		Cpf::String mDescription;
	};
}
