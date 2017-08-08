//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <stdint.h>

namespace AST
{
	enum class AllTypes : uint32_t
	{
		Unknown		= 0,

		StartIntegralTypes,
		U8 = StartIntegralTypes,
		S8,
		U16,
		S16,
		U32,
		S32,
		U64,
		S64,
		EndIntegralTypes = S64,

		StartFloatTypes,
		F32 = StartFloatTypes,
		F64,
		EndFloatTypes = F64,

		StartUtilityTypes,
		Result = StartUtilityTypes,
		Void,
		EndUtilityTypes = Void,

		Identifier
	};

	std::string TypeString(AllTypes type);

	enum class TypeModifier : uint32_t
	{
		None = 0,
		Const = 1<<0
	};
	struct TypeDecl
	{
		TypeDecl() : mModifiers(TypeModifier::None), mType(AllTypes::Unknown) {}
		TypeModifier mModifiers;
		AllTypes mType;
		std::string mIdentifier;
	};
}
