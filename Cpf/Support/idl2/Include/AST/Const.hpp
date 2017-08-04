//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>
#include <cassert>

namespace AST
{
	class Const
	{
	public:
		~Const();

		enum class Type : int32_t
		{
			eIntegral,
			eFloat,
			eString,
			eClassID
		};
		static std::shared_ptr<Const> Create(const std::string& name, uint64_t value);
		static std::shared_ptr<Const> Create(const std::string& name, double value);
		static std::shared_ptr<Const> Create(const std::string& name, Type type, const std::string& value);

		uint64_t GetAsInteger() const { assert(mType == Type::eIntegral); return mUInt64; }
		double GetAsDouble() const { assert(mType == Type::eFloat); return mDouble; }
		const char* GetAsString() const { assert(mType == Type::eString || mType == Type::eClassID); return mpString; }

	private:
		Const(const std::string& name, uint64_t value);
		Const(const std::string& name, double value);
		Const(const std::string& name, Type type, const std::string& value);

		const Type mType;
		const std::string mName;
		union
		{
			uint64_t mUInt64;
			double mDouble;
			char* mpString;
		};
	};
}
