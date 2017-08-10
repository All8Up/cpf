//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <cassert>
#include "IDLTree/Symbol.hpp"

namespace IDLTree
{
	class Const final : public Symbol
	{
	public:
		enum class Type : int32_t
		{
			eIntegral,
			eFloat,
			eString,
			eClassID
		};

		Const(const ScopeVector& scope, const std::string& name, uint64_t value);
		Const(const ScopeVector& scope, const std::string& name, double value);
		Const(const ScopeVector& scope, const std::string& name, Type type, const std::string& value);
		virtual ~Const();

		SymbolType GetType() const override
		{
			switch (mType)
			{
			case Type::eIntegral: return SymbolType::eIntegralConst;
			case Type::eFloat: return SymbolType::eFloatConst;
			case Type::eString: return SymbolType::eStringConst;
			case Type::eClassID: return SymbolType::eClassIDConst;
			}
			return SymbolType::eUnknown;
		}
		std::string ToString() const override
		{
			switch (mType)
			{
			case Type::eIntegral: return std::string("Integer const: ");
			case Type::eFloat: return std::string("Float const: ");
			case Type::eString: return std::string("String const: ");
			case Type::eClassID: return std::string("ClassID const: ");
			}
			return std::string();
		}

		uint64_t GetAsInteger() const { assert(mType == Type::eIntegral); return mUInt64; }
		double GetAsDouble() const { assert(mType == Type::eFloat); return mDouble; }
		const char* GetAsString() const { assert(mType == Type::eString || mType == Type::eClassID); return mpString; }

	private:
		const Type mType;
		union
		{
			uint64_t mUInt64;
			double mDouble;
			char* mpString;
		};
	};
}
